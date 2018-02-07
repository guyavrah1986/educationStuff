#include "filesystemSQSConnector.h"
#include "memory/dataBuffer.h"

#include <mutex>
#include <unordered_set>
#include <log4cplus/loggingmacros.h>

namespace cloud
{
	using namespace hx;
	using namespace std;

	const log4cplus::Logger FilesystemSQSConnector::logger = log4cplus::Logger::getInstance(LOG4CPLUS_TEXT("cloud.FilesystemSQSConnector"));

	FilesystemSQSConnector::FilesystemSQSConnector(const std::string& queueUrl,
												   const std::shared_ptr<hx::ITime>& time,
                                                   const std::shared_ptr<IFileAccess>& fileAccess,
												   const std::chrono::seconds& visibilityTimeout)
		: m_queueUrl(queueUrl)
		, m_time(time)
		, m_fileAccess(fileAccess)
		, m_visibilityTimeout(visibilityTimeout)
		, m_messageId(0)
	{
        LOG4CPLUS_DEBUG(logger, "FilesystemSQSConnector::FilesystemSQSConnector - creating queue with URL: " << m_queueUrl);
    }

    struct FilesystemSQSConnector::LoadMessageSequence
    {
	    LoadMessageSequence(const std::string& fileName,
							FilesystemSQSConnector& parent,
                            const std::function<void(FilesystemSQSConnector::QueueMessageInfo&)>& callback)
            : m_fileName(fileName)
            , m_parent(parent)
            , m_callback(callback)
            , m_handle(nullptr)
            , m_readMsgBuff(nullptr)
			, m_attachmentOffset(0)
			, m_messageId(0)
            , m_lastRead(0)
        {
	        LOG4CPLUS_DEBUG(logger, "LoadMessageSequence::LoadMessageSequence - about to start read sequence for file " << m_fileName);
        }

        void start()
        {
            if (!m_parent.m_fileAccess->syncExists(m_fileName)) {
                LOG4CPLUS_DEBUG(logger, "LoadMessageSequence::start, file " << m_fileName << " does not exist");
                complete(nullptr, 0);
				return;
            }

            m_parent.m_fileAccess->open(m_fileName, OpenMode::Open, OpenPermissions::Read,
				[this](const Result& res, Handle* handle)
				{
					onOpen(res, handle);
				});
        }

        void onOpen(const Result& res, Handle* handle)
        {
            if (!res.isSuccess()) {
				LOG4CPLUS_ERROR(logger, "LoadMessageSequence::onOpen, was unable to open file path:" << m_fileName << ", " << res);
                complete(nullptr, 0);
				return;
            }

			m_handle = handle;

			// get the body length , message ID and last read time by parsing the file name.
			uint64_t outMessageId;
			uint32_t outAttachmentOffset;
	        uint64_t outLastRead;
			bool parsedOk = m_parent.parseFileName(m_fileName, outMessageId, outAttachmentOffset, outLastRead);
			if (!parsedOk) {
				LOG4CPLUS_ERROR(logger, "LoadMessageSequence::onOpen, was unable to parse file name of file:" << m_fileName);
				complete(nullptr, 0);
				return;
			}

			m_attachmentOffset = outAttachmentOffset;
			m_messageId = outMessageId;
	        m_lastRead = std::chrono::milliseconds(outLastRead);

            m_parent.m_fileAccess->getFileSize(m_handle,[this](const Result& res, uint64_t size)
            {
                if (!res.isSuccess()) {
					LOG4CPLUS_ERROR(logger, "LoadMessageSequence::onOpen, was unable to get file size !!");
					complete(nullptr, 0);
					return;
				}

				readMessage(size);
			});

        }

        void readMessage(uint64_t fileSize)
        {
			m_readMsgBuff = new Byte[fileSize];
			m_parent.m_fileAccess->read(m_handle, 0, fileSize, m_readMsgBuff, [this](const Result& res, uint32_t bytesRead)
			{
				if (!res.isSuccess()) {
					LOG4CPLUS_ERROR(logger, "LoadMessageSequence::readMessage, was unable to read message , res:" << res);
					complete(nullptr, 0);
				}
				else {
					complete(m_readMsgBuff, bytesRead);
				}
			});
        }

        void complete(const Byte* buff, uint32_t numBytesRead)
        {
			FilesystemSQSConnector::QueueMessageInfo msgInfo;
			if (buff == nullptr) {
				LOG4CPLUS_ERROR(logger, "LoadMessageSequence::complete, did not read message successfully !!");
			}
			else {
				msgInfo.id = m_messageId;
				msgInfo.lastRead = m_lastRead;

				msgInfo.data.body = string(reinterpret_cast<const char*>(buff), m_attachmentOffset);
				msgInfo.data.attachment = memory::DataBuffer(buff + m_attachmentOffset, numBytesRead - m_attachmentOffset);

				LOG4CPLUS_DEBUG(logger, "LoadMessageSequence::complete, message body is:" << msgInfo.data.body);
			}

            unique_ptr<LoadMessageSequence> kill(this);

            if (m_handle != nullptr) {
                m_parent.m_fileAccess->close(m_handle, [](const Result&){});
            }
	        delete [] m_readMsgBuff;
            m_callback(msgInfo);
        }

    private:
        std::string m_fileName;
        FilesystemSQSConnector& m_parent;
        std::function<void(FilesystemSQSConnector::QueueMessageInfo&)> m_callback;
        Handle* m_handle;
        Byte* m_readMsgBuff;
		uint32_t m_attachmentOffset;
		uint64_t m_messageId;
	    std::chrono::milliseconds m_lastRead;
    };

	struct FilesystemSQSConnector::InitMessagesSequence
	{
		InitMessagesSequence(FilesystemSQSConnector& parent, const function<void(const hx::Result&)>& callback)
			: m_parent(parent)
			, m_callback(callback)
			, m_listHandle(nullptr)
			, m_result(ErrorCode::Success)
			, m_leftToLoad(0)
		{
		}

		void start()
		{
			m_listHandle = m_parent.m_fileAccess->syncList(m_parent.m_queueUrl);
			if (m_listHandle == nullptr) {
				LOG4CPLUS_WARN(logger, "InitMessagesSequence::start, was unable to list folder:" <<  m_parent.m_queueUrl);
				m_result = ErrorCode::IoError;
				complete();
				return;
			}

			countFilesToLoad();
		}

		void countFilesToLoad()
		{
			ListEntry outEntry;

			for (Result res = m_parent.m_fileAccess->syncNextListItem(m_listHandle, outEntry, true); res.isSuccess(); res = m_parent.m_fileAccess->syncNextListItem(m_listHandle, outEntry, true)) {
				if (!res.isSuccess()) {
					LOG4CPLUS_ERROR(logger, "InitMessagesSequence::countFilesToLoad, encountered error loading file:" << outEntry.name);
					m_result = ErrorCode::IoError;
					complete();
					return;
				}
				m_filesToLoad.emplace_back(outEntry.name);
			}

			m_leftToLoad = m_filesToLoad.size();
			if (m_leftToLoad == 0) {
				LOG4CPLUS_DEBUG(logger, "InitMessagesSequence::countFilesToLoad, no files to load , finishing InitMessagesSequence");
				complete();
				return;
			}

            LOG4CPLUS_DEBUG(logger, "InitMessagesSequence::countFilesToLoad, about to load " << m_leftToLoad << " files");
            loadFiles();
		}

		void loadFiles()
		{
			for(auto& fileName : m_filesToLoad) {
				load(fileName);
			}
		}

		void load(const string& fileName)
		{
			string fileNameFullPath = m_parent.m_queueUrl + "/" + fileName;
			LoadMessageSequence *seq = new LoadMessageSequence(fileNameFullPath, m_parent, [this, fileName](QueueMessageInfo& msgInfo)
			{
				unique_lock<mutex> guard(m_lock);
				if (msgInfo.data.body.empty()) {
					LOG4CPLUS_ERROR(logger, "InitMessagesSequence::load, encountered error reading file: " << fileName);
					m_result = ErrorCode::IoError;
				}
				else {
					LOG4CPLUS_DEBUG(logger, "InitMessagesSequence::load, got back from LoadMessageSequence after reading file: " << fileName << " its message body is: " << msgInfo.data.body);
					m_msgInfoMap.emplace(msgInfo.id, msgInfo);
				}

				auto left = --m_leftToLoad;
				guard.unlock();

				if (left == 0) {
					complete();
				}
			});

			seq->start();
		}

		void complete()
		{
            unique_ptr<InitMessagesSequence> kill(this);

			for (auto iter = m_msgInfoMap.begin(); iter != m_msgInfoMap.end(); ++iter) {
				m_parent.m_messages.emplace_back(iter->second);
				LOG4CPLUS_DEBUG(logger, "<msg_id:" << iter->second.id << " ,last_read_time:" << iter->second.lastRead.count() << " ,msg_body:" << iter->second.data.body << ">");
			}

			LOG4CPLUS_DEBUG(logger, "InitMessagesSequence::complete, after re-ordering the m_messages vector has the following messages:");
			m_callback(m_result);
		}

	private:
		FilesystemSQSConnector& m_parent;
		function<void(const hx::Result&)> m_callback;
		ListHandle* m_listHandle;
		Result m_result;
		size_t m_leftToLoad;

		vector<string> m_filesToLoad;
		map<uint64_t, QueueMessageInfo> m_msgInfoMap;
		mutex m_lock;
	};

    void FilesystemSQSConnector::init(const std::function<void(const hx::Result&)>& callback)
    {
        LOG4CPLUS_DEBUG(logger, "init - about to initiate the InitMessagesSequence, loading files from folder:" << m_queueUrl);

        InitMessagesSequence* seq = new InitMessagesSequence(*this, [this, callback](const Result& result)
			{
				m_messageId = 0;

				// in the case of a restart, if after loading the files we have at least one message, than
				// the m_messageId should be incremented to be one after the "highest" messageID among
				// the files that were loaded - otherwise, the next message that will be sent, will have
				// the same message ID as the last message that was loaded
				if (!m_messages.empty()) {
					m_messageId = m_messages.back().id + 1;
				}

				LOG4CPLUS_DEBUG(logger, "init - Done the InitMessagesSequence, setting the current message ID to: " << m_messageId);
				callback(result);
			});
        seq->start();
    }

	struct FilesystemSQSConnector::SendMessageSequence
	{
		SendMessageSequence(FilesystemSQSConnector& parent, MessageData&& message, const std::function<void(const hx::Result&)>& callback)
			: m_parent(parent)
			, m_message(0, std::move(message))
			, m_callback(callback)
			, m_handle(nullptr)
		{}

		void start()
		{
			// Allocate new message id
			{
				LOG4CPLUS_DEBUG(m_parent.logger, "SendMessageSequence::start - allocating message ID:" << m_parent.m_messageId << " for the new message to add");
				lock_guard<mutex> guard(m_parent.m_lock);
				m_message.id = (m_parent.m_messageId)++;
			}

			createFile();
		}

		void createFile()
		{
			// upon send we set the lastReadTime to zero
			auto currentTime = static_cast<std::chrono::milliseconds>(0);
			string path = m_parent.buildFileName(m_message, currentTime);
			m_parent.m_fileAccess->open(path, OpenMode::Create, OpenPermissions::Write, [this, path](const Result& result, Handle *handle)
			{
				if (!result.isSuccess()) {
					LOG4CPLUS_ERROR(m_parent.logger, "SendMessageSequence::createFile - Failed creating new file for queue: " << m_parent.m_queueUrl << ", " << result);
					complete(result);
				}
				else {
					m_handle = handle;
					writeBody(path);
				}
			});
		}

		void writeBody(const string& path)
		{
			auto length = m_message.data.body.length();
			auto buffer = reinterpret_cast<const Byte*>(m_message.data.body.c_str());

			m_parent.m_fileAccess->write(m_handle, 0, length, buffer, [this, path, buffer](const Result& result)
			{
				if (!result.isSuccess()) {
					LOG4CPLUS_ERROR(m_parent.logger, "SendMessageSequence::writeBody - Failed writing body to file: " << path << ", " << result);
					complete(result);
				}
				else {
					LOG4CPLUS_DEBUG(m_parent.logger, "SendMessageSequence::writeBody - wrote body:" << buffer << " to file name:" << path);
					writeAttachment(path);
				}
			});
		}

		void writeAttachment(const string& path)
		{
			// In case message doesn't have attachment, don't need to write it
			if (!m_message.data.attachment.hasData()) {
				LOG4CPLUS_DEBUG(m_parent.logger, "SendMessageSequence::writeAttachment - no attachment going to updateQueue");
				updateQueue();
			}
			else {
				auto offset = m_message.data.body.length();
				auto length = m_message.data.attachment.length();
				auto buffer = m_message.data.attachment.data();

				m_parent.m_fileAccess->write(m_handle, offset, length, buffer, [this, path, buffer](const Result& result)
				{
					if (!result.isSuccess()) {
						LOG4CPLUS_ERROR(m_parent.logger, "SendMessageSequence::writeAttachment - Failed writing attachment to file: " << path << ", " << result);
						complete(result);
					}
					else {
						updateQueue();
					}
				});
			}
		}

		void updateQueue()
		{
			unique_lock<mutex> guard(m_parent.m_lock);
			m_parent.m_messages.emplace_back(std::move(m_message));
			guard.unlock();
			complete(Result::Success());
		}

		void complete(const Result& result)
		{
			unique_ptr<SendMessageSequence> kill(this);
			if (m_handle != nullptr) {
				m_parent.m_fileAccess->close(m_handle, [](const Result&){});
			}
			m_callback(result);
		}

	private:
		FilesystemSQSConnector& m_parent;
		FilesystemSQSConnector::QueueMessageInfo m_message;
		std::function<void(const hx::Result&)> m_callback;
		Handle* m_handle;
	};

	void FilesystemSQSConnector::sendMessage(MessageData&& message, const std::function<void(const hx::Result&)>& callback)
	{
		LOG4CPLUS_DEBUG(logger, "FilesystemSQSConnector::sendMessage - got message with body: " << message.body);

		SendMessageSequence *seq = new SendMessageSequence(*this, std::move(message), callback);
		seq->start();
	}

	void FilesystemSQSConnector::sendMessages(const vector<MessageData>& messages, const function<void(const unordered_map<string, Result>&)>& callback)
	{
		if (messages.empty()) {
			callback(unordered_map<string, Result>());
			return;
		}

		struct SendMessagesResult
		{
			unordered_map<string, Result> response;
			uint32_t left;
		};

		SendMessagesResult *request = new SendMessagesResult();
		request->left = static_cast<uint32_t>(messages.size());

		for(auto& message : messages) {
			string body = message.body;
			MessageData data = message;
			sendMessage(move(data), [this, body, request, callback](const Result& result)
				{
					unique_lock<mutex> guard(m_lock);
					request->response.emplace(body, result);
					uint32_t left = --(request->left);
					guard.unlock();

					if (left == 0) {
						unique_ptr<SendMessagesResult> kill(request);
						callback(request->response);
					}
				});
		}
	}

	void FilesystemSQSConnector::readMessage(const std::function<void(const Result&, const shared_ptr<ReceivedMessageInfo>&)>& callback)
	{
		readMessages(1, [callback](const Result& result, vector<shared_ptr<ReceivedMessageInfo>>&& messages)
		{
			if (!result.isSuccess()) {
				callback(result, make_shared<FsReceivedMessageInfo>(FsReceivedMessageInfo::createEmpty()));
			}
			else {
				callback(result, std::move(*messages.begin()));
			}
		});
	}

    struct FilesystemSQSConnector::ReadMessageSequence
    {
	    ReadMessageSequence(FilesystemSQSConnector& parent,
                                     std::function<void(const Result&, vector<shared_ptr<ReceivedMessageInfo>>&&)> callback,
                                     uint32_t numOfMessages)
			: m_parent(parent)
			, m_callback(callback)
			, m_numOfMessagesToRename(numOfMessages)
            , m_currentTime(m_parent.m_time->currentTime())
        {
	        LOG4CPLUS_DEBUG(logger, "ReadMessageSequence::ReadMessageSequence - setting m_numOfMessages to " << m_numOfMessagesToRename);
        }

        void start()
        {
            uint32_t numOfMessages = m_numOfMessagesToRename;
            {
                lock_guard<mutex> guard(m_lock);
                for(QueueMessageInfo& message : m_parent.m_messages) {
                    auto timeSinceLastRead = m_currentTime - message.lastRead;
                    if (timeSinceLastRead <= m_parent.m_visibilityTimeout) {
                        LOG4CPLUS_DEBUG(logger, "ReadMessageSequence::start - Skipping message id: " << message.id << ", still invisible (passed: " << timeSinceLastRead.count() << " sec, expected: " << m_parent.m_visibilityTimeout.count() << " sec)");
                        continue;
                    }

                    LOG4CPLUS_DEBUG(logger, "ReadMessageSequence::start - Reading message with body: " << message.data.body << " (id: " << message.id << ")");
                    m_messagesToRename.emplace_back(&message);
                    if (--numOfMessages == 0) {
                        break;
                    }
                }
            }
	        renameMessages();
        }

        void renameMessages()
        {
	        LOG4CPLUS_DEBUG(logger, "ReadMessageSequence::renameMessages - about to rename " << m_messagesToRename.size() << " files");

	        // for cases where the original number of messages to read was greater than  the
	        // actual number of files we wish to rename
	        m_numOfMessagesToRename = m_messagesToRename.size();

	        if (m_numOfMessagesToRename == 0) {
		        LOG4CPLUS_DEBUG(logger, "ReadMessageSequence::renameMessages - moving to complete, no need to actually rename files");
				complete();
				return;
	        }

	        for (QueueMessageInfo* message : m_messagesToRename) {
                auto lastReadTime = message->lastRead;

                string from = m_parent.buildFileName(*message, lastReadTime);
		        string to = m_parent.buildFileName(*message, m_currentTime);
		        m_parent.m_fileAccess->rename(from, to, [this, message](const Result& result)
                {
                    if (result.isSuccess()) {
	                    LOG4CPLUS_DEBUG(logger, "ReadMessageSequence::renameMessages - successfully renamed message id " << message->id << " set its current last read time"
			                    " to: " << m_currentTime.count() << "(previous last read time:" << message->lastRead.count() << ")");
	                    message->lastRead = m_currentTime;
                    }
	                else {
	                    LOG4CPLUS_WARN(logger, "ReadMessageSequence::renameMessages - was unable to rename message id " << message->id << " res " << result);
                    }

	                unique_lock<mutex> guard(m_lock);
					uint32_t left = --m_numOfMessagesToRename;
					guard.unlock();

					if (left == 0) {
                        complete();
                    }
                });
            }
        }

        void complete()
        {
            unique_ptr<ReadMessageSequence> kill(this);
            Result result = m_messagesToRename.empty() ? Result(ErrorCode::EntryNotFound) : Result::Success();

            vector<shared_ptr<ReceivedMessageInfo>> resultVec;
	        LOG4CPLUS_DEBUG(logger, "ReadMessageSequence::complete - going over the " << m_messagesToRename.size() << " messages to return");
	        for(QueueMessageInfo* message : m_messagesToRename) {
		        string fileName = m_parent.buildFileName(*message, message->lastRead);
		        LOG4CPLUS_DEBUG(logger, " message " << fileName);
		        resultVec.emplace_back(make_shared<FsReceivedMessageInfo>(message->data, fileName));
	        }

	        LOG4CPLUS_DEBUG(logger, "ReadMessageSequence::complete - finishing");
	        m_callback(result, move(resultVec));
        }

    private:
        FilesystemSQSConnector& m_parent;
        std::function<void(const Result&, vector<shared_ptr<ReceivedMessageInfo>>&&)> m_callback;
        uint32_t m_numOfMessagesToRename;
	    std::chrono::milliseconds m_currentTime;

        mutex m_lock;
        vector<QueueMessageInfo*> m_messagesToRename;
    };

	void FilesystemSQSConnector::readMessages(uint32_t numOfMessages, const std::function<void(const Result&, vector<shared_ptr<ReceivedMessageInfo>>&&)>& callback)
	{
        LOG4CPLUS_DEBUG(logger, "FilesystemSQSConnector::readMessages - about to initiate ReadMessageSequence");

		bool empty = false;
		{
			lock_guard<mutex> guard(m_lock);
			empty = m_messages.empty();
		}

		if (empty) {
			LOG4CPLUS_DEBUG(logger, "FilesystemSQSConnector::readMessages - the queue is empty - terminating...");
			callback(Result(ErrorCode::EntryNotFound), vector<shared_ptr<ReceivedMessageInfo>>());
			return;
		}

		ReadMessageSequence* seq = new ReadMessageSequence(*this, callback, numOfMessages);
        seq->start();
	}

	void FilesystemSQSConnector::deleteMessage(const shared_ptr<ReceivedMessageInfo>& message, const function<void(const Result&)>& callback)
	{
		deleteMessages({ message }, [message, callback](const unordered_map<string, Result>& result)
		{
			callback(result.begin()->second);
		});
	}

	struct FilesystemSQSConnector::DeleteFilesSequence
	{
		DeleteFilesSequence(FilesystemSQSConnector& parent, const vector<string>& handlers, const function<void(const unordered_map<string, pair<uint64_t, Result>>&)>& callback)
			: m_parent(parent)
			, m_handlers(handlers)
			, m_callback(callback)
			, m_left(handlers.size())
		{}

		void start()
		{
			for(auto& handler : m_handlers) {
				LOG4CPLUS_DEBUG(m_parent.logger, "DeleteFilesSequence::start - Trying to delete file: " << handler);
				remove(handler);
			}
		}

		void remove(const string& handler)
		{
			uint64_t messageId;
			if (!m_parent.parseDeletionHandler(handler, messageId)) {
				LOG4CPLUS_WARN(m_parent.logger, "DeleteFilesSequence::remove - Was unable to parse file:" << handler << " terminating delete sequence");
				onRemoveCompleted(Result(ErrorCode::InvalidParameter), handler);
				return;
			}

			m_parent.m_fileAccess->remove(handler, [this, handler, messageId](const Result& result)
			{
				onRemoveCompleted(result, handler, messageId);
			});
		}

		void onRemoveCompleted(const Result& result, const string& handler, uint64_t messageId = 0)
		{
			auto fixedResult = (result.getErrorCode() == ErrorCode::EntryNotFound) ? Result::Success() : result;
			if (!fixedResult.isSuccess()) {
				LOG4CPLUS_WARN(m_parent.logger, "DeleteFilesSequence::onRemoveCompleted - Failed deleting file: " << handler << ", " << fixedResult);
			}

			unique_lock<mutex> guard(m_lock);
			m_result.emplace(handler, make_pair(messageId, fixedResult));
			auto left = --m_left;
			guard.unlock();

			if (left == 0) {
				complete();
			}
		}

		void complete()
		{
			unique_ptr<DeleteFilesSequence> kill(this);
			m_callback(m_result);
		}

	private:
		FilesystemSQSConnector& m_parent;
		vector<string> m_handlers;
		function<void(const unordered_map<string, pair<uint64_t, Result>>&)> m_callback;
		size_t m_left;

		mutex m_lock;
		unordered_map<string, pair<uint64_t, Result>> m_result;
	};

	void FilesystemSQSConnector::deleteMessages(const vector<shared_ptr<ReceivedMessageInfo>>& messages, const function<void(const unordered_map<string, Result>&)>& callback)
	{
		vector<string> handlers;
		for(const auto& message : messages) {
			handlers.emplace_back(static_cast<FsReceivedMessageInfo*>(message.get())->handler);
		}

		DeleteFilesSequence *seq = new DeleteFilesSequence(*this, handlers, [this, callback](const unordered_map<string, pair<uint64_t, Result>>& result)
		{
			unique_lock<mutex> guard(m_lock);

			// Build callback response to the user and select which messages we need to delete from the vector
			unordered_set<uint64_t> toDelete;
			unordered_map<string, Result> outcome;
			for (auto& pair : result) {
				outcome.emplace(pair.first, pair.second.second);
				if (pair.second.second.isSuccess()) {
					toDelete.emplace(pair.second.first);
				}
			}

			// Delete messages from memory
			size_t left = toDelete.size();
			if (left > 0) {
				auto iter = m_messages.begin();
				while (iter != m_messages.end()) {
					if (toDelete.find(iter->id) != toDelete.end()) {
						iter = m_messages.erase(iter);
						if (--left == 0) {
							break;
						}
					}
					else {
						++iter;
					}
				}
			}

			guard.unlock();
			callback(outcome);
		});
		seq->start();
	}

	void FilesystemSQSConnector::purge(const std::function<void(const hx::Result&)>& callback)
	{
		LOG4CPLUS_DEBUG(logger, "FilesystemSQSConnector::purge - Purging " << m_messages.size() << " messages in queue: " << m_queueUrl);

		auto result = m_fileAccess->syncRemoveFolder(m_queueUrl);
		if (!result.isSuccess()) {
			LOG4CPLUS_ERROR(logger, "FilesystemSQSConnector::purge - Failed deleting folder: " << m_queueUrl << ", " << result);
			callback(result);
			return;
		}

		result = m_fileAccess->syncMkdir(m_queueUrl);
		if (!result.isSuccess()) {
			LOG4CPLUS_ERROR(logger, "FilesystemSQSConnector::purge - Failed creating folder: " << m_queueUrl << ", " << result);
			callback(result);
			return;
		}

		{
			lock_guard<mutex> guard(m_lock);
			m_messages.clear();
		}

		callback(Result::Success());
	}

	std::string FilesystemSQSConnector::buildDeletionHandler(const QueueMessageInfo& message)
	{
		return buildFileName(message);
	}

	bool FilesystemSQSConnector::parseDeletionHandler(const string& handler, uint64_t& outMessageId)
	{
		uint32_t dummy1;
		uint64_t dummy2;
		return parseFileName(handler, outMessageId, dummy1, dummy2);
	}

	std::string FilesystemSQSConnector::buildFileName(const QueueMessageInfo& message)
	{
		return buildFileName(message, message.lastRead);
	}

    std::string FilesystemSQSConnector::buildFileName(const QueueMessageInfo& message, const std::chrono::milliseconds& lastRead)
    {
        string path = XSTR(m_queueUrl << "/" << std::setfill('0') << std::setw(6) << message.id);
        string lastReadTimeStr = to_string(lastRead.count());
        string fileName = XSTR(path << "_" << message.data.body.length() << "#" << lastReadTimeStr);
        LOG4CPLUS_DEBUG(logger, "FilesystemSQSConnector::buildFileName - built file: " << fileName);
        return fileName;
    }

	bool FilesystemSQSConnector::parseFileName(const std::string& name,
	                                           uint64_t& outMessageId,
	                                           uint32_t& outAttachmentOffset,
	                                           uint64_t& outLastRead)
	{
		size_t start = name.find_last_of('/');
		if (start == string::npos) {
			start = 0;
		}
		else {
			++start;
		}

		size_t pos1 = name.find_last_of('_');
		size_t pos2 = name.find_last_of('#');
		if (pos1 == string::npos || pos2 == string::npos) {
			return false;
		}

		string messageId = name.substr(start, pos1);
		string attachmentOffset = name.substr(pos1 + 1, pos2);
		string lastRead = name.substr(pos2 + 1);

		try {
			outMessageId = static_cast<uint64_t>(stol(messageId));
			outAttachmentOffset = static_cast<uint32_t>(stoi(attachmentOffset));
			outLastRead = static_cast<uint64_t>(stol(lastRead));
			LOG4CPLUS_DEBUG(logger, "parseFileName - successfully parsed message ID: " << outMessageId <<
			" Attachment Offset:" << outAttachmentOffset << " LastRead time:" << outLastRead);
			return true;
		}
		catch(...) {
			LOG4CPLUS_WARN(logger, "Failed parsing file name: " << name << " for queue: " << m_queueUrl);
			return false;
		}
	}
}