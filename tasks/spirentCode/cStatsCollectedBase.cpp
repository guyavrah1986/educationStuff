#include <iostream>


#include "cStatsCollectedBase.h"

using namespace std;

CStatsCollectedBase::CStatsCollectedBase(const char* pName, bool bIsEnabled, bool isOutputEnabled)
	: m_pObjectName(pName)
	, m_bIsEnabled(bIsEnabled)
	, m_bIsOutputEnabled(isOutputEnabled)
{
	cout << "CStatsCollectedBase::CStatsCollectedBase - created stats collected base object with name:" <<  m_pObjectName << endl;
}

CStatsCollectedBase::~CStatsCollectedBase()
{
	cout << "CStatsCollectedBase::~CStatsCollectedBase" << endl; 
}
