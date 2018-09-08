#pragma once

#include <map>
#include <list>

#include "adapterProtocol.h"

class CAdapterMgr
{
	public:
	CAdapterMgr(const std::list<EnProtocolType>& protocolsList);
	virtual ~CAdapterMgr();

	// class specific "interface"
	virtual IAdapProtocol* GetAdapByProtocolType(EnProtocolType protocolType) const;
	virtual SdkConnection* GetConnectionByProtocolType(EnProtocolType protocolType) const;

	private:
	std::map<EnProtocolType, IAdapProtocol*> m_protocolAdaptersMap;
};
