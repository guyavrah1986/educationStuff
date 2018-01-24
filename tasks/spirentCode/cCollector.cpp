#include "cCollector.h"

#include <algorithm>
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
	if (observer == nullptr)
	{
		cout << "CCollector::Register - trying to add a NULL observer, aborting" << endl;
		return false;
	}

	cout << "CCollector::Register - adding observer:" << observer->GetName() << endl;
	m_observers.emplace_back(observer);
	return true;
}

bool CCollector::UnRegister(CStatsCollectedBase* observer)
{

	if (observer == nullptr)
	{
		cout << "CCollector::UnRegister - trying to remove a NULL observer, aborting" << endl;
		return false;
	}

	cout << "CCollector::UnRegister - removeing observer" << observer->GetName() << endl;
	
	vector<CStatsCollectedBase*>::iterator position = std::find(myVector.begin(), myVector.end(), 8);
	if (position != myVector.end()) // == myVector.end() means the element was not found
    	myVector.erase(position);
	return true;
}


