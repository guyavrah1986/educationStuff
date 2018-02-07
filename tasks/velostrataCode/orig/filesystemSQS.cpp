#include "filesystemSQS.h"
#include "hx/time.h"
#include "cloud/filesystemSQSConnector.h"

namespace cloud
{
	using namespace hx;
	using namespace std;

	const log4cplus::Logger FilesystemSQS::logger = log4cplus::Logger::getInstance(LOG4CPLUS_TEXT("cloud.FilesystemSQS"));

	FilesystemSQS::FilesystemSQS(const std::string& path,
                                 const std::shared_ptr<IFileAccess>& fileAccess,
                                 const std::chrono::seconds& visibilityTimeout)
		: m_path(path)
		, m_fileAccess(fileAccess)
		, m_visibilityTimeout(visibilityTimeout)
	{
        LOG4CPLUS_INFO(logger, "Creating FilesystemSQS with path: " << m_path << " visibility timeout: " << m_visibilityTimeout.count() << " sec");
    }

	std::string FilesystemSQS::buildQueueUrl(const std::string& name)
	{
		return XSTR(m_path << "/" << name);
	}

	void FilesystemSQS::createQueue(const std::string& name, const std::function<void(const hx::Result&, const std::string&)>& callback)
	{
		string url = buildQueueUrl(name);

		bool found = m_fileAccess->syncExists(url);
		if (found) {
			LOG4CPLUS_WARN(logger, "Queue with name: " << name << " already exists!");
			callback(Result(ErrorCode::AlreadyExists), url);
		}
		else {
			LOG4CPLUS_INFO(logger, "Creating queue: " << name << " in path: " << url);

			auto result = FileAccessUtils::syncMkdirRecursive(url, *m_fileAccess);
			if (!result.isSuccess()) {
				LOG4CPLUS_ERROR(logger, "Failed creating queue: " << name << ", " << result);
				url = string();
			}
			callback(result, url);
		}
	}

	void FilesystemSQS::deleteQueue(const std::string& queueUrl, const std::function<void(const hx::Result&)>& callback)
	{
		bool found = m_fileAccess->syncExists(queueUrl);

		Result result = Result(ErrorCode::EntryNotFound);
		if (found) {
			LOG4CPLUS_INFO(logger, "Deleting queue: " << queueUrl);
			result = m_fileAccess->syncRemoveFolder(queueUrl);
			if (!result.isSuccess()) {
				LOG4CPLUS_ERROR(logger, "Failed deleting queue: " << queueUrl << ", " << result);
			}
		}
		else {
			LOG4CPLUS_WARN(logger, "Cannot find queue to delete, url: " << queueUrl);
		}

		callback(result);
	}

	void FilesystemSQS::connectByQueueName(const std::string& name, const std::function<void(const hx::Result&, std::unique_ptr<ISQSConnector>&&)>& callback)
	{
		connectByQueueUrl(buildQueueUrl(name), callback);
	}

	void FilesystemSQS::connectByQueueUrl(const std::string& queueUrl, const std::function<void(const hx::Result&, std::unique_ptr<ISQSConnector>&&)>& callback)
	{
		LOG4CPLUS_DEBUG(logger, "connectByQueueUrl - calling syncExists with queueUrl: " << queueUrl);

		bool found = m_fileAccess->syncExists(queueUrl);
		if (found) {
			FilesystemSQSConnector *connector = new FilesystemSQSConnector(queueUrl, make_shared<Time>(), m_fileAccess, m_visibilityTimeout);
			connector->init([connector, callback](const Result& result){ callback(result, unique_ptr<FilesystemSQSConnector>(connector)); });
		}
		else {
			callback(Result(ErrorCode::EntryNotFound), nullptr);
		}
	}
}
