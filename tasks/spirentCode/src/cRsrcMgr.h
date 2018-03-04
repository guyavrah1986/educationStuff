#pragma once

#include <string>
#include <unordered_map>

#include "rsrcMgr.h"
#include "cStatsCollectedBase.h"

class CRsrcMgr : public IRsrcMgr
{
public:
	CRsrcMgr();
	virtual ~CRsrcMgr();

	// IRsrcMgr interface implementation
	virtual Result CreateRsrc(IN const char* strUri, IN EnRsrcType rsrcType, IN EnProtocolType protocolType, IN bool bInternalCreated, INOUT CRsrcBase*& pRsrc);
	virtual Result RemoveRsrc(IN CRsrcBase* pRsrc);
	virtual Result GetRsrcById(IN const char* strUri, OUT CRsrcBase** ppRsrc);
	virtual Result NewAppRsrcCreated(IN const char* uri, IN SpM2mRsrcValue* pValue);

private:
	Result createLwm2mRsrc(IN const char* uri);
	Result addLwm2mRsrsc(IN const char* arr[]);

private:
	std::unordered_map<std::string, CStatsCollectedBase*> m_rsrcNameToCollectedObjMap;
	std::unordered_map<const char*, CRsrcBase*> m_rsrcMap;
};
