#pragma once

#include "globalHeader.h"
#include "cRsrcBase.h"

class IRsrcMgr
{
public:
	virtual Result CreateRsrc(IN const char* strUri, IN EnRsrcType eType, IN EnProtocolType protocolType, IN bool bInternalCreated, INOUT CRsrcBase*& pRsrc) = 0;
	virtual Result RemoveRsrc(IN CRsrcBase* pRsrc) = 0;
	virtual Result GetRsrcById(IN const char* strUri, OUT CRsrcBase** ppRsrc) = 0;
	virtual Result NewAppRsrcCreated(IN const char* uri, IN SpM2mRsrcValue* pValue) = 0;
	virtual ~IRsrcMgr() {}
};


