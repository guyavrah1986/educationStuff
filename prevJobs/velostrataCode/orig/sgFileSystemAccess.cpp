#include "sgFileSystemAccess.h"

#include <log4cplus/loggingmacros.h>

#include "hx/config.h"
#include "datapath/fileAccess.h"

namespace storageGrid
{
	using namespace std;
	using namespace hx;

	struct SgFileSystemAccess::StartElement
	{
		NO_COPY_TYPE(StartElement);

		StartElement(const std::string& path, const std::string& prefix)
		: parentPath(path)
		, prefix(prefix)
		{

		}

		explicit StartElement(const std::string& parentPath)
		: StartElement(parentPath, "")
		{

		}

		StartElement()
		: parentPath("")
		, prefix("")
		{

		}

		bool isValid() const
		{
			return (!parentPath.empty() || !prefix.empty());
		}

		std::string parentPath;
		std::string prefix;
	};

	SgFileSystemAccess::SgFileSystemAccess(const shared_ptr<IFileAccess>& fileAccess,
											const string& rootPath,
											const shared_ptr<stats::IDiagnostics>& diagnostics,
											boost::asio::io_service& io_service)

		: m_fileAccess(fileAccess)
		, m_rootPath(rootPath)
		, m_diagnostics(diagnostics)
		, m_ioService(io_service)
	{
		if (m_rootPath.back() != '/') {
			m_rootPath.push_back('/');
		}
		LOG4CPLUS_TRACE(SgFileSystemAccess::logger, "SgFileSystemAccess::SgFileSystemAccess - setting rootPath to:" + m_rootPath);
	}

	// deprecated method
	void SgFileSystemAccess::writePage(const string& key,
									   const char* buffer,
									   uint32_t length,
									   SgLimitGroup priority,
									   const function<void(const Result&) >& callback)
	{

		struct WritePage
		{
			NO_COPY_TYPE(WritePage);

			string key;
			uint32_t length;
			char* writeBuffer;
			shared_ptr<SgFileSystemAccess> parent;
			function<void(const Result&) > callback;
			Handle* handle;
			string tmpPostfix;

			WritePage(const string& key, uint32_t length, const char* writeBuff, const string& tmpPostfix, const shared_ptr<SgFileSystemAccess>& parent, const function<void(const Result&)>& callback)
					: key(key)
					, length(length)
					, writeBuffer(nullptr)
					, parent(parent)
					, callback(callback)
					, handle(nullptr)
					, tmpPostfix(tmpPostfix)
			{
					if (length > 0 && writeBuff != nullptr) {
						writeBuffer = new char [length];
						memcpy(writeBuffer, writeBuff, length);
					}
			}

			~WritePage()
			{
				delete [] writeBuffer;
			}

			void start()
			{
				if (writeBuffer == nullptr && length != 0) {
					LOG4CPLUS_ERROR(SgFileSystemAccess::logger, "SgFileSystemAccess::writePage - Got NULL buffer to write and (non zero) length:" << length);
					Result res(ErrorCode::InvalidParameter);
					finish(res);
					return;
				}
				size_t position = key.find_last_of("/");

				if (position != string::npos) {
					string parentPath = key.substr(0, position);
					Result res = FileAccessUtils::syncMkdirRecursive(parentPath,*(parent->m_fileAccess));

					if (!res.isSuccess()) {
						LOG4CPLUS_ERROR(SgFileSystemAccess::logger, "SgFileSystemAccess::writePage - Was unable to create the necessary folders for:" + key);
						Result res(ErrorCode::CannotCompleteRequest);
						finish(res);
						return;
					}
					LOG4CPLUS_TRACE(SgFileSystemAccess::logger, "SgFileSystemAccess::writePage - Create the following path:" + parentPath);
					parent->m_fileAccess->open(key + tmpPostfix, OpenMode::Create, OpenPermissions::Write, [this](const Result& result, Handle* handle)
					{
						onOpen(result, handle);
					});
				}
			}

			void onOpen(const Result& result, Handle* handle)
			{
				if (!result.isSuccess()) {
						LOG4CPLUS_ERROR(logger, "SgFileSystemAccess::writePage - Failed opening:" << key << " " << result);
						finish(result);
						return;
				}
				this->handle = handle;
				if (length == 0) {
					LOG4CPLUS_TRACE(SgFileSystemAccess::logger, "SgFileSystemAccess::writePage - length is zero - returning");
					finish(result);
					return;
				}

				parent->m_fileAccess->write(this->handle, 0, length, reinterpret_cast<const Byte*>(writeBuffer), [this](const Result& result)
				{
					if (result.isSuccess()) {
						parent->m_fileAccess->rename(key + tmpPostfix, key, [this](const Result& result)
						{
							finish(result);
							return;
						});
					}
					else {
						finish(result);
						return;
					}
				});
			}

			void finish(const Result& result)
			{
				unique_ptr<WritePage> kill(this);

				if (handle != nullptr) {
					parent->m_fileAccess->close(handle, [](const Result&) {});
				}

				callback(result);
			}

		};

		LOG4CPLUS_TRACE(SgFileSystemAccess::logger, "SgFileSystemAccess::writePage - got write request of " << length << " bytes to path:" << key);

		if (sgfsDisabled) {
			m_ioService.post([callback] { callback(Result(ErrorCode::IoError)); });
			return;
		}

		if (key.empty()) {
			LOG4CPLUS_ERROR(SgFileSystemAccess::logger, "SgFileSystemAccess::writePage - Got an empty file path");
			Result res(ErrorCode::InvalidParameter);
			callback(res);
			return;
		}

		const string fullPath = resolveFullPath(key);
		WritePage* writer = new WritePage(fullPath, length, buffer, m_tmpPostfix, shared_from_this(), callback);
		writer->start();
	}

	void SgFileSystemAccess::writePage(const string& key, shared_ptr<asio::streambuf> data, SgLimitGroup priority, const function<void(const Result&)>& callback)
	{
		if (sgfsDisabled) {
			m_ioService.post([callback] { callback(Result(ErrorCode::IoError)); });
			return;
		}

		uint32_t dataSize = static_cast<uint32_t>(data->size());
		char* buff = new char [dataSize];
		data->sgetn(buff, dataSize);
		LOG4CPLUS_TRACE(SgFileSystemAccess::logger, "SgFileSystemAccess::writePage(asio::streambuf) - Got buffer with size:" <<  dataSize);
		writePage(key, buff, dataSize, priority, callback);
		delete [] buff;
	}

	void SgFileSystemAccess::readPage(const string& key,
									  size_t offset,
									  size_t length,
									  SgLimitGroup priority,
									  const function<void(const ReadPageResponse&)>& callback)
	{
		struct ReadPage
		{
			NO_COPY_TYPE(ReadPage);

			string key;
			size_t offset;
			size_t length;
			shared_ptr<SgFileSystemAccess> parent;
			function<void(const ReadPageResponse&)> callback;
			size_t toCopy;
			Byte* readBuff;
			Handle* handle;

			ReadPage(const string& key, size_t offset, size_t length,const shared_ptr<SgFileSystemAccess>& parent, const function<void(const ReadPageResponse&)>& callback)
				: key(key)
				, offset(offset)
				, length(length)
				, parent(parent)
				, callback(callback)
				, toCopy(0)
				, readBuff(nullptr)
				, handle(nullptr)
			{
			}

			~ReadPage()
			{
				delete [] readBuff;
			}

			void start()
			{
				if (!parent->m_fileAccess->syncExists(key)) {
					LOG4CPLUS_TRACE(SgFileSystemAccess::logger, "SgFileSystemAccess::readPage - start: file path: " + key + " does not exist");
					ReadPageResponse response(Result(ErrorCode::EntryNotFound), nullptr, 0);
					finish(response);
					return;
				}

				parent->m_fileAccess->open(key, OpenMode::Open, OpenPermissions::Read, [this](const Result& res, Handle* handle)
				{
					this->handle = handle;
					onOpen(res,this->handle);
				});
			}

			void onOpen(const Result& res, Handle* handle)
			{
				if (res.getErrorCode() != ErrorCode::Success || handle == nullptr) {
					LOG4CPLUS_ERROR(SgFileSystemAccess::logger, "SgFileSystemAccess::readPage - onOpen Was unable to open file path:" + key);
					ReadPageResponse response(Result(ErrorCode::IoError), nullptr, 0);
					finish(response);
					return;
				}
				parent->m_fileAccess->getFileSize(this->handle,[this](const Result& res, uint64_t size)
				{
						onGetFileSize(res, size);
				});
			}

			void onGetFileSize(const Result& res, uint64_t fileSize)
			{
				if (res.getErrorCode() != ErrorCode::Success) {
					LOG4CPLUS_ERROR(SgFileSystemAccess::logger, "SgFileSystemAccess::readPage - getFileSize terminated unsuccessfully, returned size:" << fileSize);
					ReadPageResponse response(Result(ErrorCode::IoError), nullptr, 0);
					finish(response);
					return;
				}

				// According to SG java implementation:
				//  long toCopy = length > 0 ? Math.min(length, file.length()) : Math.max(0, file.length() - (int)srcOffset);
				if (length == 0) {
					toCopy = fileSize - static_cast<uint64_t>(offset);
				}
				else {
					toCopy =  min(length, fileSize);
				}

				if (fileSize == 0 && offset <= fileSize && length + offset <= fileSize) {
					LOG4CPLUS_TRACE(SgFileSystemAccess::logger, "SgFileSystemAccess::readPage - onGetFileSize:file:" << key << " has size 0");
					ReadPageResponse response(Result(ErrorCode::Success), nullptr, 0);
					finish(response);
					return;
				}

				if (offset >= fileSize) {
					LOG4CPLUS_ERROR(SgFileSystemAccess::logger, "SgFileSystemAccess::readPage - onGetFileSize:trying to read from offset:"
									<< offset << " which is greater (equal) than file size:" << fileSize);
					ReadPageResponse response(Result(ErrorCode::IoError), nullptr, 0);
					finish(response);
					return;
				}

				if (length + offset > fileSize) {
					LOG4CPLUS_ERROR(SgFileSystemAccess::logger, "SgFileSystemAccess::readPage - trying to read " << length << " bytes starting from an invalid offset");
					ReadPageResponse response(Result(ErrorCode::IoError), nullptr, 0);
					finish(response);
					return;
				}

				if (toCopy == 0) {
					LOG4CPLUS_ERROR(SgFileSystemAccess::logger, "SgFileSystemAccess::readPage - trying to read zero byte - terminating");
					ReadPageResponse response(Result(ErrorCode::IoError), nullptr, 0);
					finish(response);
					return;
				}

				readBuff = new Byte [toCopy];
				parent->m_fileAccess->read(handle, offset, toCopy, readBuff, [this](const Result& res, uint32_t bytesRead)
				{
					onRead(res, readBuff, bytesRead);
				});
			}

			void onRead(const Result& res, const Byte* readBuff, uint32_t bytesRead)
			{
				if (!res.isSuccess()) {
					LOG4CPLUS_ERROR(SgFileSystemAccess::logger, "SgFileSystemAccess::readPage - onRead:Was unable to read file path:" + key);
					ReadPageResponse response(Result(ErrorCode::IoError), nullptr, 0);
					finish(response);
					return;
				}

				ReadPageResponse response(Result(ErrorCode::Success), readBuff, bytesRead);
				LOG4CPLUS_TRACE(SgFileSystemAccess::logger, "SgFileSystemAccess::readPage - onRead: Successfully read:" << bytesRead << " bytes" << " from file: " << key);
				finish(response);
				return;
			}

			void finish(const ReadPageResponse& readPageResponse)
			{
				unique_ptr<ReadPage> kill(this);

				if (handle != nullptr) {
					parent->m_fileAccess->close(handle, [](const Result&) {});
				}
				callback(readPageResponse);
			}

		};

		LOG4CPLUS_TRACE(SgFileSystemAccess::logger, "SgFileSystemAccess::readPage - Got read request key:" << key << " length:" << length);

		if (sgfsDisabled) {
			m_ioService.post([callback] { callback(ReadPageResponse(Result(ErrorCode::IoError), nullptr, 0)); });
			return;
		}

		if (key.empty()) {
			LOG4CPLUS_ERROR(SgFileSystemAccess::logger, "SgFileSystemAccess::readPage - Got an empty path");
			ReadPageResponse response(Result(ErrorCode::InvalidParameter), nullptr, 0);
			callback(response);
			return;
		}

		const string fullPath = resolveFullPath(key);
		ReadPage* reader = new ReadPage(fullPath, offset, length, shared_from_this(), callback);
		reader->start();
	}

	void SgFileSystemAccess::listPages(const string& keyPrefix,
									   uint32_t max_objects,
									   const string& delimiter,
									   const string& marker,
									   ListPageResponse& listPageResponse,
									   const function<void()>& callback)
	{
		LOG4CPLUS_TRACE(SgFileSystemAccess::logger, "SgFileSystemAccess::listPages - with keyPrefix:" << keyPrefix << " marker:" << marker
						<< " Delimiter: " << delimiter << " and maxObjects:" << max_objects);

		if (sgfsDisabled) {
			clearListPageResponse(listPageResponse, ErrorCode::IoError);
			m_ioService.post([callback] { callback(); });
			return;
		}

		if (listPageResponse.pageSummary.size() > 0) {
			LOG4CPLUS_ERROR(logger, "SgFileSystemAccess::listPages - Got a non empty pageSummary vector (has " << listPageResponse.pageSummary.size() << " entries).");
			clearListPageResponse(listPageResponse, ErrorCode::InvalidParameter);
			callback();
			return;
		}

		const string fullPath = resolveFullPath(keyPrefix);
		StartElement startElement;
		getDir(fullPath, startElement);
		if (!startElement.isValid()) {
			LOG4CPLUS_TRACE(SgFileSystemAccess::logger, "SgFileSystemAccess::listPages - Trying to list non existing prefix");
			clearListPageResponse(listPageResponse, ErrorCode::Success);
			callback();
			return;
		}

		getMatchedPrefixes(max_objects, startElement, listPageResponse, marker);
		callback();
	}

	void SgFileSystemAccess::exists(const string& key, const function<void(const Result&)>& callback)
	{
		LOG4CPLUS_TRACE(SgFileSystemAccess::logger, "SgFileSystemAccess::exists - with key:" << key);
		if (sgfsDisabled) {
			m_ioService.post([callback] { callback(Result(ErrorCode::IoError)); });
			return;
		}

		if (key.empty()) {
			LOG4CPLUS_ERROR(SgFileSystemAccess::logger, "SgFileSystemAccess::exists - Got an empty path (key)");
			callback(Result(ErrorCode::InvalidParameter));
			return;
		}

		const string fullPath = resolveFullPath(key);
		if (m_fileAccess->syncExists(fullPath)) {
			callback(Result(ErrorCode::Success));
			return;
		}

		callback(Result(ErrorCode::EntryNotFound));
	}

	void SgFileSystemAccess::deletePage(const string& key, const function<void(const Result&) >& callback)
	{
		LOG4CPLUS_TRACE(SgFileSystemAccess::logger, "SgFileSystemAccess::deletePage - with key:" << key);

		if (sgfsDisabled) {
			m_ioService.post([callback] { callback(Result(ErrorCode::IoError)); });
			return;
		}

		if (key.empty()){
			LOG4CPLUS_ERROR(SgFileSystemAccess::logger, "SgFileSystemAccess::deletePage - Got an empty path (key)");
			Result res(ErrorCode::InvalidParameter);
			callback(res);
			return;
		}

		const string fullPath = resolveFullPath(key);

		if (!m_fileAccess->syncExists(fullPath)) {
			LOG4CPLUS_ERROR(SgFileSystemAccess::logger,"SgFileSystemAccess::deletePage - did not find " << fullPath);
			Result res(ErrorCode::EntryNotFound);
			callback(res);
			return;
		}

		LOG4CPLUS_TRACE(SgFileSystemAccess::logger,"SgFileSystemAccess::deletePage - removed:" << fullPath);
		m_fileAccess->remove(fullPath, callback);
	}

	std::future<bool> SgFileSystemAccess::start()
	{
		std::promise<bool> result;
		result.set_value(true);
		return result.get_future();
	}

	void SgFileSystemAccess::abortStartProcess()
	{

	}

	void SgFileSystemAccess::tearDown()
	{

	}

	// ================================================
	// Utilities functions:
	// ================================================

	void SgFileSystemAccess::clearListPageResponse(ListPageResponse& listPageResponse, ErrorCode errorCode)
	{
		listPageResponse.res = Result(errorCode);
		listPageResponse.commonPrefixes.clear();
		listPageResponse.nextMarker = "";
		listPageResponse.pageSummary.clear();
	}

	void SgFileSystemAccess::getDir(const string& prefix, StartElement& startElement)
	{
		// the prefix is a path of a directory - verify it exists
		if (prefix.back() == '/') {
			if (!m_fileAccess->syncExists(prefix)) {
				return;
			}
			startElement.parentPath = prefix;
			return;
		}
		else { // get the parent directory - verify it exists

			size_t position = prefix.find_last_of("/");
			string parentPath = prefix.substr(0, position + 1);
			string keyPrefix = prefix.substr(position + 1);

			if (!m_fileAccess->syncExists(parentPath)) {
				return;
			}
			startElement.parentPath = parentPath;
			startElement.prefix = keyPrefix;
			return;
		}
	}

	void SgFileSystemAccess::getMatchedPrefixes(size_t maxObjects, const StartElement& startElement, ListPageResponse& listPageResponse, const string& marker)
	{
		LOG4CPLUS_TRACE(SgFileSystemAccess::logger, "SgFileSystemAccess::getMatchedPrefixes - startElement.prefix:" << startElement.prefix <<
						" startElement.parentPath:" << startElement.parentPath << " and marker:" << marker);

		if (maxObjects == 0) {
			LOG4CPLUS_TRACE(SgFileSystemAccess::logger, "SgFileSystemAccess::getMatchedPrefixes - Got zero as maxObjects - returning empty matches list");
			clearListPageResponse(listPageResponse, ErrorCode::InvalidParameter);
			return;
		}

		ListHandle* listHandle;
		listHandle = m_fileAccess->syncList(startElement.parentPath);
		if (listHandle == nullptr) {
			LOG4CPLUS_ERROR(SgFileSystemAccess::logger, "SgFileSystemAccess::getMatchedPrefixes - Was unable to open path:" + startElement.parentPath);
			clearListPageResponse(listPageResponse, ErrorCode::InvalidParameter);
			listPageResponse.res = ErrorCode::InvalidParameter;
			return;
		}

		vector<PageSummary> pageSummary;
		pageSummary.reserve(maxObjects);
		bool doesMarkerExist = true;

		// According to the File system SG Java implementation:
		// !StringUtils.isBlank(marker) from the documentations:
		// Checks if a String is whitespace, empty ("") or null.
		if (marker.empty() || (find_if(marker.begin(), marker.end(), ::isspace) != marker.end())) {
			doesMarkerExist = false;
		}

		ListEntry outEntry;
		Result res;
		string startElementWithoutRootFolderPrefix = startElement.parentPath.substr(m_rootPath.length());
		LOG4CPLUS_TRACE(SgFileSystemAccess::logger, "SgFileSystemAccess::getMatchedPrefixes - before adding prefixes loop, setting  "
				"startElementWithoutRootFolderPrefix to:" << startElementWithoutRootFolderPrefix);

		for (res = m_fileAccess->syncNextListItem(listHandle, outEntry, true); res.isSuccess(); res = m_fileAccess->syncNextListItem(listHandle, outEntry, true)) {
			if ((outEntry.name.find(startElement.prefix) == 0) && (!doesMarkerExist || (startElementWithoutRootFolderPrefix + outEntry.name).compare(marker) > 0)) {
				// Don't add temporary files (ends with .tmp postfix)
				if ((outEntry.name.length() >= m_tmpPostfix.length()) && (0 == outEntry.name.compare(outEntry.name.length() - m_tmpPostfix.length(), m_tmpPostfix.length(), m_tmpPostfix))) {
					continue;
				}
				string matchedStr = startElementWithoutRootFolderPrefix + outEntry.name;
				PageSummary newPageSummary(matchedStr, static_cast<unsigned int>(outEntry.fileSize), outEntry.lastModified);
				pageSummary.push_back(newPageSummary);
				LOG4CPLUS_TRACE(SgFileSystemAccess::logger, "SgFileSystemAccess::getMatchedPrefixes - Adding prefix:"
								<< newPageSummary.keyName << " with size:" << newPageSummary.dataLength
								<< " and lastModifiedTimeGmtSinceEpochMs:" << newPageSummary.lastModifiedTimeGmtSinceEpochMs);
			}
		}

		m_fileAccess->syncClose(listHandle);

		// sort pageSummary (lexicographic manner)
		sort(pageSummary.begin(),pageSummary.end(),
			[](const PageSummary &page1, const PageSummary &page2)
			{
				return (page1.keyName.compare(page2.keyName) < 0);
			});

		listPageResponse.pageSummary = pageSummary;

		// remove the unnecessary entries
		if (listPageResponse.pageSummary.size() > maxObjects) {
			LOG4CPLUS_TRACE(SgFileSystemAccess::logger, "SgFileSystemAccess::getMatchedPrefixes - removing " << listPageResponse.pageSummary.size() - maxObjects << " extra matched page Summary matches");
			listPageResponse.pageSummary.resize(maxObjects);
			listPageResponse.nextMarker = listPageResponse.pageSummary[listPageResponse.pageSummary.size() - 1].keyName;
		}
		else {
			listPageResponse.nextMarker = "";
		}

	listPageResponse.res = Result::Success();
	}

	string SgFileSystemAccess::resolveFullPath(const string& path)
	{
		string res = m_rootPath + path;
		return res;
	}

	shared_ptr<ISgAccess> FileSystemStorageGridFactory::create(const string& rootPath,
															   const std::shared_ptr<IFileAccess>& fileAccess,
															   const std::shared_ptr<stats::IDiagnostics>& diagnostics,
															   asio::io_service& io_service)
	{
		shared_ptr<SgFileSystemAccess> sgFileSystemAccess(make_shared<SgFileSystemAccess>(fileAccess, rootPath, diagnostics, io_service));
		return sgFileSystemAccess;
	}

	const log4cplus::Logger SgFileSystemAccess::logger = log4cplus::Logger::getInstance(LOG4CPLUS_TEXT("hx.SgFileSystemAccess"));
	bool SgFileSystemAccess::sgfsDisabled = false;
}
