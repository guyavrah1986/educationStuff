#pragma once

#include <list>

#include "../adapter/adapterMgr.h"

class CCoreClient
{
	public:
	CCoreClient();
	~CCoreClient();

	CAdapterMgr& GetAdapMgr();

	
	private:
	CAdapterMgr m_adapMgr;
	/* CRsrcMgr* m_rsrcMgr;*/
};
