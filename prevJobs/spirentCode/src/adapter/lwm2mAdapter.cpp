#include <iostream>
	
#include "lwm2mAdapter.h"

using namespace std;

CAdapterLwm2m::CAdapterLwm2m()
{
	cout << "CAdapterLwm2m::CAdapterLwm2m" << endl;	
}

CAdapterLwm2m::~CAdapterLwm2m()
{
	cout << "CAdapterLwm2m::~CAdapterLwm2m" << endl;	
}

Result CAdapterLwm2m::Step(size_t timeOut)
{
	cout << "CAdapterLwm2m::Step" << endl;
	return Result(ErrorCode::SP_M2M_ERROR_CODE_SUCCESS);
}

Result CAdapterLwm2m::HandlePacket(const SdkConnection* connection, const char* buff, size_t numOfBytes, size_t& numBytesHandled)
{
	cout << "CAdapterLwm2m::HandlePacket" << endl;
	return Result(ErrorCode::SP_M2M_ERROR_CODE_SUCCESS);
}

Result CAdapterLwm2m::NewAppRsrc(const char* uri, SpEnRsrcType rsrcType)
{
	cout << "CAdapterLwm2m::NewAppRsrc" << endl;
	return Result(ErrorCode::SP_M2M_ERROR_CODE_SUCCESS);
}
	
Result CAdapterLwm2m::NotifyAppRsrcValue(const char* uri)
{
	cout << "CAdapterLwm2m::NotifyAppRsrcValue" << endl;
	return Result(ErrorCode::SP_M2M_ERROR_CODE_SUCCESS);
}

Result CAdapterLwm2m::DeleteAppRsrc(const char* uri)
{
	cout << "CAdapterLwm2m::DeleteAppRsrc" << endl;
	return Result(ErrorCode::SP_M2M_ERROR_CODE_SUCCESS);
}
