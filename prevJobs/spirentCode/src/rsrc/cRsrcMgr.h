#pragma once

#include <string>
#include <unordered_map>

#include "rsrcMgr.h"
#include "../statsModule/cStatsCollectedBase.h"

class CRsrcMgr : public IRsrcMgr
{
public:
	CRsrcMgr();
	virtual ~CRsrcMgr();

	// IRsrcMgr interface implementation
	virtual Result CreateRsrc(IN const char* strUri, IN SpEnRsrcType rsrcType, IN EnProtocolType protocolType, IN bool bInternalCreated, INOUT CRsrcBase*& pRsrc);
	virtual Result RemoveRsrc(IN CRsrcBase* pRsrc);
	virtual Result GetRsrcById(IN const char* strUri, OUT CRsrcBase** ppRsrc);
	virtual Result NewAppRsrcCreated(IN const char* uri, IN SpM2mRsrcValue* pValue);

	// for unit testing and debug
	const std::unordered_map<std::string, CRsrcBase*>& GetRsrcMap() const;

private:
	Result createLwm2mRsrc(IN const char* uri, IN bool bInternalCreated, IN SpEnRsrcType rsrcType);
	Result addLwm2mRsrsc(IN const std::string& uri, IN const char* arr[], IN bool bInternalCreated, IN SpEnRsrcType rsrcType);

private:
	std::unordered_map<std::string, CStatsCollectedBase*> m_rsrcNameToCollectedObjMap;
	std::unordered_map<std::string, CRsrcBase*> m_rsrcMap;
};
