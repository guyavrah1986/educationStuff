#pragma once

#include <log4cplus/logger.h>

#include "storageGrid/storageGridProxy.h"
#include "datapath/fileAccess.h"

namespace storageGrid
{
	class SgFileSystemAccess : public ISgAccess , public std::enable_shared_from_this<SgFileSystemAccess>
	{
		NO_COPY_TYPE(SgFileSystemAccess);

		struct StartElement;

	public:
		SgFileSystemAccess(const std::shared_ptr<IFileAccess>& fileAccess,
							const std::string& rootPath,
							const std::shared_ptr<stats::IDiagnostics>& diagnostics,
							boost::asio::io_service& io_service);

		// deprecated method
		virtual void writePage(const std::string& key,
							   const char* buffer,
							   uint32_t length,
							   SgLimitGroup priority,
							   const std::function<void(const hx::Result&) >& callback) override;

		virtual void writePage(const std::string& key,
							   std::shared_ptr<asio::streambuf> data,
							   SgLimitGroup priority,
							   const std::function<void(const hx::Result&) >& callback) override;

		virtual void readPage(const std::string& key,
							  size_t offset,
							  size_t length,
							  SgLimitGroup priority,
							  const std::function<void(const ReadPageResponse&) >& callback) override;

		virtual void listPages(const std::string& keyPrefix,
							   uint32_t max_objects,
							   const std::string& delimiter,
							   const std::string& marker,
							   ListPageResponse& listPageResponse,
							   const std::function<void() >& callback) override;

		virtual void exists(const std::string& key, const std::function<void(const hx::Result&) >& callback) override;
		virtual void deletePage(const std::string& key, const std::function<void(const hx::Result&) >& callback) override;

		// these functions are only here because they are part of the ISgAccess interface,
		// we don't really need them as part of this object's capabilities.
		virtual std::future<bool> start() override;
		virtual void abortStartProcess() override;
		virtual void tearDown() override;

		// UiCmd interface related methods
		static void setDisableMode(bool disable);

	private:
		// utilities functions:
		void clearListPageResponse(ListPageResponse& listPageResponse, hx::ErrorCode errorCode);
		void getDir(const std::string& prefix, StartElement& startElement);
		void getMatchedPrefixes(size_t maxObjects, const StartElement& startElement, ListPageResponse& listPageResponse, const std::string& marker);
		std::string resolveFullPath(const std::string& path);

	public:
		static bool sgfsDisabled;

	private:
		std::shared_ptr<IFileAccess> m_fileAccess;
		std::string m_rootPath;
		std::shared_ptr<stats::IDiagnostics> m_diagnostics;
		boost::asio::io_service& m_ioService;
		const std::string m_tmpPostfix = ".tmp";
		static const log4cplus::Logger logger;
	};
}
