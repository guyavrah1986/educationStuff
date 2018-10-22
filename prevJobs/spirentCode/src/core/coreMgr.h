#pragma once

#include <list>

#include "coreClient.h"
#include "../globalHeader.h"

class CCoreMgr
{
	public:
	static CCoreMgr* GetInstance();
	void DestroyInstance();
	~CCoreMgr();

	CCoreClient* CreateClient(const std::list<EnProtocolType>& protocolsList);

	private:
	CCoreMgr();

	static CCoreMgr* m_instance;
	unsigned int m_numOfClients;
};
