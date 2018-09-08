#pragma once

#include <list>

#include "adapterMgr.h"

class CCoreClient
{
	public:
	CCoreClient(const std::list<EnProtocolType>& protocolsList);
	~CCoreClient();

	const CAdapterMgr& GetAdapMgr() const;

	
	private:
	CAdapterMgr m_adapMgr;
	/* CRsrcMgr* m_rsrcMgr;*/
};
