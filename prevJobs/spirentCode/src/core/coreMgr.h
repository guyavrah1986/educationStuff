#pragma once

#include "coreClient.h"
#include "../globalHeader.h"

class CCoreMgr
{
	public:
	static CCoreMgr* GetInstance();
	CCoreClient* CreateClient();
	void DestroyInstance();

	~CCoreMgr();


	private:
	CCoreMgr();
	CCoreMgr(const CCoreMgr& other);
	CCoreMgr& operator=(const CCoreMgr& rhs);

	// members:
	// -------
	static CCoreMgr* m_instance;
	unsigned int m_numOfClients;
};
