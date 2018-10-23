#include <iostream>

#include "adapterMgr.h"
#include "mqttAdapter.h"
#include "lwm2mAdapter.h"

using namespace std;

CAdapterMgr::CAdapterMgr()
{
	cout << "CAdapterMgr::CAdapterMgr" << endl;
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

SpStatus CAdapterMgr::AddProtocolAdapter(IN const EnProtocolType protocolType)
{
	BaseAdapProtocol* protoclAdapter = BaseAdapProtocol::Create(protocolType);
	if (protoclAdapter == NULL)
	{
		cout << "CAdapterMgr::AddProtocolAdapter - was unable to create a proper BaseAdapProtocol object" << endl;
		return SP_M2M_STATUS_GENERAL_FAUILRE;
	}

	return addProtocolAdapterToMap(protocolType, protoclAdapter);
}

BaseAdapProtocol* CAdapterMgr::GetAdapByProtocolType(EnProtocolType protocolType) const
{
	return nullptr;
}

SdkConnection* CAdapterMgr::GetConnectionByProtocolType(EnProtocolType protocolType) const
{
	return nullptr;
}

SpStatus CAdapterMgr::addProtocolAdapterToMap(IN const EnProtocolType protocolType, IN BaseAdapProtocol* protoclAdapter)
{
	auto res = m_protocolAdaptersMap.insert(pair<EnProtocolType, BaseAdapProtocol*>(protocolType, protoclAdapter));
	// From the cpp reference: The return value (of map.insert) is a pair consisting of
	// an iterator to the inserted element (or to the element that prevented the
	// insertion) and a bool denoting whether the insertion took place.
	if (res.second == false)
	{
		cout << "CAdapterMgr::addProtocolAdapterToMap - adapter for protocol type:" << static_cast<int>(protocolType) << " was already present"
				" in the map, we need to delete it before adding the new one" << endl;

		m_protocolAdaptersMap.erase(res.first);
		delete res.first->second;
		// now, insert again (this time it should work)
		res = m_protocolAdaptersMap.insert(pair<EnProtocolType, BaseAdapProtocol*>(protocolType, protoclAdapter));
		if (res.second == false)
		{
			cout << "CAdapterMgr::addProtocolAdapterToMap - had an error trying to add adapter for protocol type:"
					<< static_cast<int>(protocolType) << " after deleting the old one" << endl;
			return SP_M2M_STATUS_GENERAL_FAUILRE;
		}
	}

	return SP_M2M_STATUS_SUCCESS;
}

