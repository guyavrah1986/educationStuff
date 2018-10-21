#include <iostream>
	
#include "mqttAdapter.h"

using namespace std;

CAdapterMqtt::CAdapterMqtt()
{
	cout << "CAdapterMqtt::CAdapterMqtt" << endl;	
}

CAdapterMqtt::~CAdapterMqtt()
{
	cout << "CAdapterMqtt::~CAdapterMqtt" << endl;	
}

Result CAdapterMqtt::Step(size_t timeOut)
{
	cout << "CAdapterMqtt::Step" << endl;
	return Result(ErrorCode::SP_M2M_ERROR_CODE_SUCCESS);
}

Result CAdapterMqtt::HandlePacket(const SdkConnection* connection, const char* buff, size_t numOfBytes, size_t& numBytesHandled)
{
	cout << "CAdapterMqtt::HandlePacket" << endl;
	return Result(ErrorCode::SP_M2M_ERROR_CODE_SUCCESS);
}

Result CAdapterMqtt::NewAppRsrc(const char* uri, EnRsrcType rsrcType)
{
	cout << "CAdapterMqtt::NewAppRsrc" << endl;
	return Result(ErrorCode::SP_M2M_ERROR_CODE_SUCCESS);
}
	
Result CAdapterMqtt::NotifyAppRsrcValue(const char* uri)
{
	cout << "CAdapterMqtt::NotifyAppRsrcValue" << endl;
	return Result(ErrorCode::SP_M2M_ERROR_CODE_SUCCESS);
}

Result CAdapterMqtt::DeleteAppRsrc(const char* uri)
{
	cout << "CAdapterMqtt::DeleteAppRsrc" << endl;
	return Result(ErrorCode::SP_M2M_ERROR_CODE_SUCCESS);
}
