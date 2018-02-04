#include <iostream>

#include "coreClient.h"

using namespace std;

CCoreClient::CCoreClient(const list<EnProtocolType>& protocolsList)
	: m_adapMgr(protocolsList)
{
	cout << "CCoreClient::CCoreClient - about to create client which support " << protocolsList.size() << " IoT protocols" << endl;
}

CCoreClient::~CCoreClient()
{
	cout << "CCoreClient::~CCoreClient" << endl;
}

const CAdapterMgr& CCoreClient::GetAdapMgr() const
{
	return m_adapMgr;
}
