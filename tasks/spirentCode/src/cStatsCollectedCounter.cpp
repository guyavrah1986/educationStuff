#include "cStatsCollectedCounter.h"

#include <iostream>

using namespace std;

CStatsCollectedCounter::CStatsCollectedCounter(const char* pName, bool bIsEnabled, bool isOutputEnabled)
	: CStatsCollectedBase(pName, bIsEnabled, isOutputEnabled)
{
	cout << "CStatsCollectedCounter::CStatsCollectedCounter" << endl;
}

CStatsCollectedCounter::~CStatsCollectedCounter()
{
	cout << "CStatsCollectedCounter::~CStatsCollectedCounter" << endl;
}

bool CStatsCollectedCounter::Update()
{
	cout << "CStatsCollectedCounter::Update" << endl;
	if (m_bIsEnabled != true)
	{
		cout << "CStatsCollectedCounter::Update - collectedCounter:" << m_pObjectName << " is not enabled" << endl;
		return false;
	}

	++m_counter;
	return true;
}

bool CStatsCollectedCounter::output()
{
	cout << "CStatsCollectedCounter::output" << endl;
	return true;
}




