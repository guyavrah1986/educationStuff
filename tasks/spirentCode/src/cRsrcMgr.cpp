#include <iostream>

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

Result CRsrcMgr::CreateRsrc(IN const char* strUri, IN EnRsrcType eType, IN bool bInternalCreated, INOUT CRsrcBase*& pRsrc)
{
	cout << "CRsrcMgr::CreateRsrc" << endl;
	return Result(ErrorCode::SP_M2M_ERROR_CODE_SUCCESS);
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
