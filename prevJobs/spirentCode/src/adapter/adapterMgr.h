#pragma once

#include <map>
#include <list>

#include "baseAdapterProtocol.h"

class CAdapterMgr
{
	public:
	CAdapterMgr(const std::list<EnProtocolType>& protocolsList);
	virtual ~CAdapterMgr();

	// class specific "interface"
	virtual BaseAdapProtocol* GetAdapByProtocolType(EnProtocolType protocolType) const;
	virtual SdkConnection* GetConnectionByProtocolType(EnProtocolType protocolType) const;

	private:
	std::map<EnProtocolType, BaseAdapProtocol*> m_protocolAdaptersMap;
};
