#pragma once

#include "adapterProtocol.h"

class CAdapterLwm2m : public IAdapProtocol
{
	public:
	CAdapterLwm2m();
	virtual ~CAdapterLwm2m();

	virtual Result Step(size_t timeOut);
	virtual Result HandlePacket(const SdkConnection* connection, const char* buff, size_t numOfBytes, size_t& numBytesHandled);
	virtual Result NewAppRsrc(const char* uri, EnRsrcType rsrcType);
	virtual Result NotifyAppRsrcValue(const char* uri);
	virtual Result DeleteAppRsrc(const char* uri);

};