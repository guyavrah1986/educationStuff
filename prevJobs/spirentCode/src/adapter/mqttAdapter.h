#pragma once

#include "adapterProtocol.h"

class CAdapterMqtt : public IAdapProtocol
{
	public:
	CAdapterMqtt();
	virtual ~CAdapterMqtt();

	virtual Result Step(size_t timeOut);
	virtual Result HandlePacket(const SdkConnection* connection, const char* buff, size_t numOfBytes, size_t& numBytesHandled);
	virtual Result NewAppRsrc(const char* uri, SpEnRsrcType rsrcType);
	virtual Result NotifyAppRsrcValue(const char* uri);
	virtual Result DeleteAppRsrc(const char* uri);

};
