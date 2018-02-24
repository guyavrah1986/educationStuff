#pragma once

#include <string>
#include <unordered_map>

#include "cStatsCollectedBase.h"

class CRsrcMgr
{
public:
	CRsrcMgr();
	~CRsrcMgr();

private:
	std::unordered_map<std::string, CStatsCollectedBase*> m_rsrcNameToCollectedObjMap;

};
