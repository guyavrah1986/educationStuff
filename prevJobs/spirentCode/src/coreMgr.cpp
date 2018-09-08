#include <iostream>

#include "coreMgr.h"

using namespace std;

CCoreMgr* CCoreMgr::m_instance = nullptr;

CCoreMgr::CCoreMgr() : m_numOfClients(0)
{
	cout << "CCoreMgr::CCoreMgr" << endl;
}

CCoreMgr::~CCoreMgr()
{
	cout << "CCoreMgr::~CCoreMgr" << endl;
	if (m_instance != nullptr)
	{
		delete m_instance;
	}
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

CCoreClient* CCoreMgr::CreateClient(const list<EnProtocolType>& protocolsList)
{
	++m_numOfClients;
	CCoreClient* client = new CCoreClient(protocolsList);
	cout << "CCoreMgr::CreateClient - creating client number " << m_numOfClients << " with " <<  protocolsList.size() << " types of protocols" << endl;
	return client;
}
