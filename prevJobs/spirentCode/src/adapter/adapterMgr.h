#pragma once

#include <map>
#include <list>

#include "baseAdapterProtocol.h"

class CAdapterMgr
{
	public:
	CAdapterMgr();
	virtual ~CAdapterMgr();

	// public interface
	SpStatus AddProtocolAdapter(IN const EnProtocolType protocolType);
	BaseAdapProtocol* GetAdapByProtocolType(IN EnProtocolType protocolType) const;
	virtual SdkConnection* GetConnectionByProtocolType(EnProtocolType protocolType) const;

	private:
	SpStatus addProtocolAdapterToMap(IN const EnProtocolType protocolType, IN BaseAdapProtocol* protoclAdapter);

// members:
// --------

	private:
	std::map<EnProtocolType, BaseAdapProtocol*> m_protocolAdaptersMap;
};
