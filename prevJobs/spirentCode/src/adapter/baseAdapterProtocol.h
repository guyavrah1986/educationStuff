#pragma once

#include "../globalHeader.h"

class BaseAdapProtocol
{
	public:
	BaseAdapProtocol();
	virtual ~BaseAdapProtocol();

	// The actual protocol adapter interface
	virtual Result Step(size_t timeOut) = 0;
	virtual Result HandlePacket(const SdkConnection* connection, const char* buff, size_t numOfBytes, size_t& numBytesHandled) = 0;
	virtual Result NewAppRsrc(const char* uri, SpEnRsrcType rsrcType) = 0;
	virtual Result NotifyAppRsrcValue(const char* uri) = 0;
	virtual Result DeleteAppRsrc(const char* uri) = 0;

	// The factory method to create all sort of different adapters
	static BaseAdapProtocol* Create(IN enum EnProtocolType protocolType);
};
