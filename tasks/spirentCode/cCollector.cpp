#include "cCollector.h"

#include <iostream>

using namespace std;

CCollector::CCollector()
{
	cout << "CCollector::CCollector" << endl;
}

CCollector::~CCollector()
{
	cout << "CCollector::~CCollector" << endl;
}

bool CCollector::Register(CStatsCollectedBase* observer)
{
	cout << "CCollector::Register" << endl;
	return true;
}

bool CCollector::UnRegister(CStatsCollectedBase* observer)
{
	cout << "CCollector::UnRegister" << endl;
	return true;
}


