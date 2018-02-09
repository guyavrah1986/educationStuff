#pragma once

#include <functional>
#include <string>

#include "globalHeader.h"

struct MessageInfo
{
	MessageInfo(uint64_t id, const char* d);
	~MessageInfo();


	uint64_t msgId;
	char* data;
};

class ISqsService 
{
	virtual void SendMessage(const MessageInfo& msgInfo, const std::function<void(const Result&)>& callback) = 0;

	virtual ~ISqsService() {}

	private:
	std::string m_queueUrl;
	uint64_t m_msgId;
	
};
