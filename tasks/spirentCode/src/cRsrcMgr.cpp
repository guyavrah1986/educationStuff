#include <iostream>
#include <cstring>

#include "cRsrcMgr.h"

using namespace std;

CRsrcMgr::CRsrcMgr()
	: m_rsrcNameToCollectedObjMap()
{
	cout << "CRsrcMgr::CRsrcMgr" << endl;
}

CRsrcMgr::~CRsrcMgr()
{
	cout << "CRsrcMgr::~CRsrcMgr" << endl;
}

Result CRsrcMgr::CreateRsrc(IN const char* strUri, IN EnRsrcType rsrcType, IN EnProtocolType protocolType, IN bool bInternalCreated, INOUT CRsrcBase*& pRsrc)
{
	cout << "CRsrcMgr::CreateRsrc" << endl;
	if (strUri == nullptr)
	{
		cout << "CRsrcMgr::CreateRsrc - got a NULL URI" << endl;
		return Result(ErrorCode::SP_M2M_ERROR_CODE_GENERAL_FAUILRE);
	}

	switch (protocolType)
	{
	case SP_M2M_PROTOCOL_TYPE_LWM2M: return createLwm2mRsrc(strUri);

	case SP_M2M_PROTOCOL_TYPE_MQTT: // TODO: add it !!

	default: cout << "CRsrcMgr::CreateRsrc - got unsupported protocol type..." << endl;
			 return Result(ErrorCode::SP_M2M_ERROR_CODE_GENERAL_FAUILRE);
	}
}

Result CRsrcMgr::RemoveRsrc(IN CRsrcBase* pRsrc)
{
	cout << "CRsrcMgr::RemoveRsrc" << endl;
	return Result(ErrorCode::SP_M2M_ERROR_CODE_SUCCESS);
}

Result CRsrcMgr::GetRsrcById(IN const char* strUri, OUT CRsrcBase** ppRsrc)
{
	cout << "CRsrcMgr::GetRsrcById" << endl;
	return Result(ErrorCode::SP_M2M_ERROR_CODE_SUCCESS);
}

Result CRsrcMgr::NewAppRsrcCreated(IN const char* uri, IN SpM2mRsrcValue* pValue)
{
	cout << "CRsrcMgr::NewAppRsrcCreated" << endl;
	return Result(ErrorCode::SP_M2M_ERROR_CODE_SUCCESS);
}

Result CRsrcMgr::createLwm2mRsrc(IN const char* uri)
{
	cout << "CRsrcMgr::createLwm2mRsrc - got uri:" << uri << endl;
	const size_t numOfLevelsLwm2m = 3;
	const char* arr [numOfLevelsLwm2m] = {'\0'};

	// remove the constness of uri
	arr[0] = strtok(const_cast<char*>(uri),"/");
	if (arr[0] == NULL)
	{
		cerr << "CRsrcMgr::createLwm2mRsrc - 1st level resource URI is invalid" << endl;
		return Result(ErrorCode::SP_M2M_ERROR_CODE_GENERAL_FAUILRE);
	}

	arr[1] = strtok (NULL, "/");
	if (arr[1] == NULL)
	{
		cerr << "CRsrcMgr::createLwm2mRsrc - 2nd level resource URI is invalid" << endl;
		return Result(ErrorCode::SP_M2M_ERROR_CODE_GENERAL_FAUILRE);
	}

	arr[2] = strtok(NULL, "/");
	if (arr[2] == NULL)
	{
		cerr << "CRsrcMgr::createLwm2mRsrc - 3rd level resource URI is invalid" << endl;
		return Result(ErrorCode::SP_M2M_ERROR_CODE_GENERAL_FAUILRE);
	}

	// there are 3 valid "levels" of resource URI - add them
	return addLwm2mRsrsc(arr);
}

Result CRsrcMgr::addLwm2mRsrsc(IN const char* arr[])
{
	cout << "CRsrcMgr::addLwm2mRsrsc - about to create Lwm2m resources" << endl;
	const size_t numOfLevelsLwm2m = 3;

	cout << "1st level resource uri is:" << arr[0] << endl;
	cout << "2nd level resource uri is:" << arr[1] << endl;
	cout << "3rd level resource uri is:" << arr[2] << endl;

	return Result(ErrorCode::SP_M2M_ERROR_CODE_SUCCESS);
}


