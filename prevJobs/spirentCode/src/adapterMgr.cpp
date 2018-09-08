#include <iostream>

#include "adapterMgr.h"
#include "mqttAdapter.h"
#include "lwm2mAdapter.h"

using namespace std;

CAdapterMgr::CAdapterMgr(const list<EnProtocolType>& protocolsList)
{
	cout << "CAdapterMgr::CAdapterMgr - about to create CAdapterMgr for " << protocolsList.size() << " type of IoT protocols" << endl;
	for (list<EnProtocolType>::const_iterator it = protocolsList.begin(); it != protocolsList.end(); ++it)
	{
		switch (*it)
		{
			case SP_M2M_PROTOCOL_TYPE_LWM2M: m_protocolAdaptersMap.insert(pair < EnProtocolType, IAdapProtocol* > (*it, new CAdapterLwm2m()));
							 cout << "CAdapterMgr::CAdapterMgr - adding LWM2M protocol adapter" << endl;
							 break;

			case SP_M2M_PROTOCOL_TYPE_MQTT:  m_protocolAdaptersMap.insert(pair<EnProtocolType, IAdapProtocol*>(*it, new CAdapterMqtt()));
							 cout << "CAdapterMgr::CAdapterMgr - adding MQTT protocol adapter" << endl;
							 break;
			default:  cout << "CAdapterMgr::CAdapterMgr - unsupported protocol adapter" << endl;
				  break;
		}
	}

	cout << "CAdapterMgr::CAdapterMgr - done initialize protocol adapters, with total of " << m_protocolAdaptersMap.size() << " protocols added" << endl;
}

CAdapterMgr::~CAdapterMgr()
{
	cout << "CAdapterMgr::~CAdapterMgr" << endl;
	for (auto current = m_protocolAdaptersMap.begin(); current != m_protocolAdaptersMap.end(); ++current)
	{
    		delete current->second;
	}

	m_protocolAdaptersMap.clear();
}


IAdapProtocol* CAdapterMgr::GetAdapByProtocolType(EnProtocolType protocolType) const
{
	return nullptr;
}

SdkConnection* CAdapterMgr::GetConnectionByProtocolType(EnProtocolType protocolType) const
{
	return nullptr;
}
