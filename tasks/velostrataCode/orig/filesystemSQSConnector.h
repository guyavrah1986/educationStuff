#pragma once

#include "hx/time.h"
#include "cloud/ISQSConnector.h"
#include "datapath/fileAccess.h"


#include <mutex>
#include <chrono>
#include <vector>
#include <log4cplus/logger.h>

namespace cloud
{
	struct FsReceivedMessageInfo : public ReceivedMessageInfo
	{
		FsReceivedMessageInfo(const MessageData& message, const std::string& handler)
			: ReceivedMessageInfo(message)
			, handler(handler)
		{}

		static FsReceivedMessageInfo createEmpty() { return FsReceivedMessageInfo(MessageData::createEmpty(), std::string()); }

		std::string handler;
	};

	class FilesystemSQSConnector : public ISQSConnector
	{
	public:
		FilesystemSQSConnector(const std::string& queueUrl,
							   const std::shared_ptr<hx::ITime>& time,
                               const std::shared_ptr<IFileAccess>& fileAccess,
							   const std::chrono::seconds& visibilityTimeout);

		virtual void purge(const std::function<void(const hx::Result&)>& callback) override;

		virtual void sendMessage(MessageData&& message, const std::function<void(const hx::Result&)>& callback) override;
		virtual void sendMessages(const std::vector<MessageData>& messages, const std::function<void(const std::unordered_map<std::string, hx::Result>&)>& callback) override;

		virtual void readMessage(const std::function<void(const hx::Result&, const std::shared_ptr<ReceivedMessageInfo>&)>& callback) override;
		virtual void readMessages(uint32_t numOfMessages, const std::function<void(const hx::Result&, std::vector<std::shared_ptr<ReceivedMessageInfo>>&&)>& callback) override;

		virtual void deleteMessage(const std::shared_ptr<ReceivedMessageInfo>& message, const std::function<void(const hx::Result&)>& callback) override;
		virtual void deleteMessages(const std::vector<std::shared_ptr<ReceivedMessageInfo>>& messages, const std::function<void(const std::unordered_map<std::string, hx::Result>&)>& callback) override;

        void init(const std::function<void(const hx::Result&)>& callback);

		// Unit tests usage
        size_t numOfMessages() const { return m_messages.size(); }
        uint64_t getMessageId() const { return m_messageId; }
		void setVisibilityTimeout(const std::chrono::seconds& timeout) { m_visibilityTimeout = timeout; }
		std::chrono::seconds getVisibilityTimeout() const { return m_visibilityTimeout; }

	private:
        struct LoadMessageSequence;
        struct InitMessagesSequence;
        struct SendMessageSequence;
		struct DeleteFilesSequence;
        struct ReadMessageSequence;

		struct QueueMessageInfo
		{
			QueueMessageInfo(uint64_t id, MessageData&& data)
				: id(id)
				, data(data)
				, lastRead(std::chrono::milliseconds(0))
			{}

            QueueMessageInfo()
                : id(0)
                , data(MessageData::createEmpty())
                , lastRead(std::chrono::milliseconds(0))
            {}

			uint64_t id;
			MessageData data;
			std::chrono::milliseconds lastRead;
		};

		std::string buildDeletionHandler(const QueueMessageInfo& message);
		std::string buildFileName(const QueueMessageInfo& message);
        std::string buildFileName(const QueueMessageInfo& message, const std::chrono::milliseconds& lastRead);

		bool parseDeletionHandler(const std::string& handler, uint64_t& outMessageId);
		bool parseFileName(const std::string& name, uint64_t& outMessageId, uint32_t& outAttachmentOffset, uint64_t& outLastRead);

        std::string m_queueUrl;
		std::shared_ptr<hx::ITime> m_time;
        std::shared_ptr<IFileAccess> m_fileAccess;
        std::chrono::seconds m_visibilityTimeout;

		std::mutex m_lock;
		uint64_t m_messageId;
		std::vector<QueueMessageInfo> m_messages;

		static const log4cplus::Logger logger;
	};
}
