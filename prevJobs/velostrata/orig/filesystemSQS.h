#pragma once

#include "cloud/ISimpleQueueService.h"
#include "datapath/fileAccess.h"
#include <log4cplus/logger.h>

namespace cloud
{
	class FilesystemSQS : public ISimpleQueueService
	{
	public:
		FilesystemSQS(const std::string& path, const std::shared_ptr<IFileAccess>& fileAccess, const std::chrono::seconds& visibilityTimeout);

		virtual void createQueue(const std::string& name, const std::function<void(const hx::Result&, const std::string&)>& callback) override;
		virtual void deleteQueue(const std::string& queueUrl, const std::function<void(const hx::Result&)>& callback) override;

		virtual void connectByQueueName(const std::string& name, const std::function<void(const hx::Result&, std::unique_ptr<ISQSConnector>&&)>& callback) override;
		virtual void connectByQueueUrl(const std::string& queueUrl, const std::function<void(const hx::Result&, std::unique_ptr<ISQSConnector>&&)>& callback) override;

	private:
		std::string buildQueueUrl(const std::string& name);

		std::string m_path;
        	std::shared_ptr<IFileAccess> m_fileAccess;
		std::chrono::seconds m_visibilityTimeout;

		static const log4cplus::Logger logger;
	};
}
