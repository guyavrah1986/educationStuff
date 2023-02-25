#pragma once

#include <cstring>
#include <functional>
#include <string>

#include "globalHeader.h"

struct MessageInfo
{
	MessageInfo(uint64_t id, const char* d, size_t numBytes)
		: msgId(id)
		, data(nullptr)
	{
		if (d != nullptr)
		{
			data = new char [numBytes];
			memcpy(data, d, numBytes);
			std::cout << "MessageInfo::MessageInfo - setting msgId:" << msgId << " and buff with size of:" << numBytes << std::endl;
		}
	}
	
	~MessageInfo()
	{
		std::cout << "MessageInfo::~MessageInfo" << std::endl;
		if (data != nullptr)
		{
			delete [] data;
		}
	}


	uint64_t msgId;
	char* data;
};

class ISqsService 
{
public:
	virtual void SendMessage(const MessageInfo& msgInfo, const std::function<void(const Result&)>& callback) = 0;
	virtual ~ISqsService() {}

private:
	std::string m_queueUrl;
	uint64_t m_msgId;
};
