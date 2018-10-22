#include <iostream>

#include "baseAdapterProtocol.h"
#include "lwm2mAdapter.h"
#include "mqttAdapter.h"

using namespace std;

BaseAdapProtocol::BaseAdapProtocol()
{
	cout << "BaseAdapProtocol::BaseAdapProtocol" << endl;
}

BaseAdapProtocol::~BaseAdapProtocol()
{
	cout << "BaseAdapProtocol::~BaseAdapProtocol" << endl;
}

BaseAdapProtocol* BaseAdapProtocol::Create(IN enum EnProtocolType protocolType)
{

	switch(protocolType)
	{
	case SP_M2M_PROTOCOL_TYPE_LWM2M:cout << "BaseAdapProtocol::Create - creating LwM2M protocol adapter" << endl;
									return new CAdapterLwm2m();

	case SP_M2M_PROTOCOL_TYPE_MQTT:cout << "BaseAdapProtocol::Create - creating MQTT protocol adapter" << endl;
								   return new CAdapterMqtt();

	default: cout << "BaseAdapProtocol::Create - got an invalid protocol type, returning NULL" << endl;
			 return NULL;
	}
}
