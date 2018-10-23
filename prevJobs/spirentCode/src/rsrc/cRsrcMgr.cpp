#include <iostream>
#include <cstring>

#include "cRsrcMgr.h"
#include "floatRsrc.h"

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

Result CRsrcMgr::CreateRsrc(IN const char* strUri, IN SpEnRsrcType rsrcType, IN EnProtocolType protocolType, IN bool bInternalCreated, INOUT CRsrcBase* pRsrc)
{
	cout << "CRsrcMgr::CreateRsrc" << endl;
	if (strUri == nullptr)
	{
		cout << "CRsrcMgr::CreateRsrc - got a NULL URI" << endl;
		return Result(ErrorCode::SP_M2M_ERROR_CODE_GENERAL_FAUILRE);
	}

	switch (protocolType)
	{
	case SP_M2M_PROTOCOL_TYPE_LWM2M: return createLwm2mRsrc(strUri, bInternalCreated, rsrcType);

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

Result CRsrcMgr::createLwm2mRsrc(IN const char* uri, IN bool bInternalCreated, IN SpEnRsrcType rsrcType)
{
	if (uri == nullptr)
	{
		cerr << "CRsrcMgr::createLwm2mRsrc - got an invalid URI" << endl;
		return Result(ErrorCode::SP_M2M_ERROR_CODE_GENERAL_FAUILRE);
	}

	cout << "CRsrcMgr::createLwm2mRsrc - got uri:" << uri << endl;
	const size_t numOfLevelsLwm2m = 3;
	//const char* arr [numOfLevelsLwm2m] = {'\0'};

	// remove the constness of uri
	const string origUri(uri);

	/*
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
	return addLwm2mRsrsc(origUri, arr, bInternalCreated, rsrcType);
	*/

	return Result(ErrorCode::SP_M2M_ERROR_CODE_SUCCESS);
}

Result CRsrcMgr::addLwm2mRsrsc(IN const string& uri, IN const char* arr[], IN bool bInternalCreated, IN SpEnRsrcType rsrcType)
{
	cout << "CRsrcMgr::addLwm2mRsrsc - about to create Lwm2m resources for resource:" << uri << endl;
	const size_t numOfLevelsLwm2m = 3;

	cout << "1st level resource uri is:" << arr[0] << endl;
	cout << "2nd level resource uri is:" << arr[1] << endl;
	cout << "3rd level resource uri is:" << arr[2] << endl;

	// 1st level resource is a "grandfather" resource
	//CRsrcBase* firstLevelRsrc = new CRsrcBase(arr[0], SP_M2M_RSRC_TYPE_PARENT_RSRC, true);
	//m_rsrcMap.insert(pair<string, CRsrcBase*>(arr[0], firstLevelRsrc));

	// 2nd level resource is a "father" resource
	//CRsrcBase* secondLevelRsrc = new CRsrcBase(arr[1], SP_M2M_RSRC_TYPE_PARENT_RSRC, true);
	//m_rsrcMap.insert(pair<string, CRsrcBase*>(arr[1], secondLevelRsrc));

	// 3rd level resource is a concrete resource
	switch (rsrcType)
	{
	case SP_M2M_RSRC_TYPE_FLOAT:
								{
									cout << "CRsrcMgr::addLwm2mRsrsc - adding float resource" << endl;
									CRsrcBase* thirdLevelRsrc = new CFloatRsrc(uri.c_str(), false);
									m_rsrcMap.insert(pair<string, CRsrcBase*>(uri.c_str(), thirdLevelRsrc));
									break;
								}

	case SP_M2M_RSRC_TYPE_INT: cout << "CRsrcMgr::addLwm2mRsrsc - adding int resource" << endl;
								// TODO !!
								break;

	case SP_M2M_RSRC_TYPE_STRING: cout << "CRsrcMgr::addLwm2mRsrsc - adding string resource" << endl;
									// TODO !!
									break;

	case SP_M2M_RSRC_TYPE_PARENT_RSRC:
	default: cerr << "CRsrcMgr::addLwm2mRsrsc - got unsupported resource type" << endl;
			 break;
	}


	return Result(ErrorCode::SP_M2M_ERROR_CODE_SUCCESS);
}

vector<string> CRsrcMgr::splitRsrcAccordingToDelimiterLwm2m(const string& str, const string& delim)
{
    vector<string> tokens;
    size_t prev = 0, pos = 0;
    do
    {
        pos = str.find(delim, prev);
        if (pos == string::npos) pos = str.length();
        string token = str.substr(prev, pos-prev);
        if (!token.empty()) tokens.push_back(token);
        prev = pos + delim.length();
    }
    while (pos < str.length() && prev < str.length());
    return tokens;
}

const unordered_map<string, CRsrcBase*>& CRsrcMgr::GetRsrcMap() const
{
	return m_rsrcMap;
}


