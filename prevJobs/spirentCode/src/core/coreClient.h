#pragma once

#include <list>

#include "../adapter/adapterMgr.h"
#include "../rsrc/cRsrcMgr.h"

class CCoreClient
{
	public:
	CCoreClient();
	~CCoreClient();

	CAdapterMgr& GetAdapMgr();

	
	private:
	CAdapterMgr m_adapMgr;
	CRsrcMgr m_rsrcMgr;
};
