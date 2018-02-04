#include <iostream>

#include "adapterMgr.h"

using namespace std;

CAdapterMgr::CAdapterMgr(const list<EnProtocolType>& protocolsList)
{
	cout << "CAdapterMgr::CAdapterMgr - about to create CAdapterMgr for " << protocolsList.size() << " type of IoT protocols" << endl;
}

CAdapterMgr::~CAdapterMgr()
{
	cout << "CAdapterMgr::~CAdapterMgr" << endl;
}


IAdapProtocol* CAdapterMgr::GetAdapByProtocolType(EnProtocolType protocolType) const
{
	return nullptr;
}

SdkConnection* CAdapterMgr::GetConnectionByProtocolType(EnProtocolType protocolType) const
{
	return nullptr;
}
