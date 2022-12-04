#pragma once

class IHttpGetRequestSender
{
public:
	virtual void SendHttpGetRequest() = 0;
	virtual ~IHttpGetRequestSender() {}
};
