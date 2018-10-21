#pragma once

#include "../globalHeader.h"

class IAdapProtocol
{
	public:
	virtual Result Step(size_t timeOut) = 0;
	virtual Result HandlePacket(const SdkConnection* connection, const char* buff, size_t numOfBytes, size_t& numBytesHandled) = 0;
	virtual Result NewAppRsrc(const char* uri, EnRsrcType rsrcType) = 0;
	virtual Result NotifyAppRsrcValue(const char* uri) = 0;
	virtual Result DeleteAppRsrc(const char* uri) = 0;

	virtual ~IAdapProtocol() {}
};
