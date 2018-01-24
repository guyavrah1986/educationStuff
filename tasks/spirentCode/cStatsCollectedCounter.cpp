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
	return true;
}

bool CStatsCollectedCounter::output()
{
	cout << "CStatsCollectedCounter::ostream" << endl;
	return true;
}




