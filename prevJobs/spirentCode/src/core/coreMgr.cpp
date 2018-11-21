#include <iostream>

#include "coreMgr.h"

using namespace std;

CCoreMgr* CCoreMgr::m_instance = nullptr;

CCoreMgr::CCoreMgr()
	: m_numOfClients(0)
{
	cout << "CCoreMgr::CCoreMgr" << endl;
}

CCoreMgr::~CCoreMgr()
{
	cout << "CCoreMgr::~CCoreMgr" << endl;
}

CCoreMgr* CCoreMgr::GetInstance()
{
	cout << "CCoreMgr::GetInstance" << endl;
	if (m_instance == nullptr)
	{
		// lock nutex - in case of multi-threaded
		if (m_instance == nullptr)
		{
			m_instance = new CCoreMgr();
		}
		// unlock mutex - in case of multi-threaded
	}

	return m_instance;
}

void CCoreMgr::DestroyInstance()
{
    delete m_instance;
    m_instance = 0;
}

CCoreClient* CCoreMgr::CreateClient()
{
	++m_numOfClients;
	CCoreClient* client = new CCoreClient();
	cout << "CCoreMgr::CreateClient - creating client number " << m_numOfClients << endl;
	return client;
}

