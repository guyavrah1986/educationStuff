#include <iostream>

#include "coreClient.h"

using namespace std;

CCoreClient::CCoreClient()
{
	cout << "CCoreClient::CCoreClient" << endl;
}

CCoreClient::~CCoreClient()
{
	cout << "CCoreClient::~CCoreClient" << endl;
}

CAdapterMgr& CCoreClient::GetAdapMgr()
{
	return m_adapMgr;
}

