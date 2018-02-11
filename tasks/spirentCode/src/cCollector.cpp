#include "cCollector.h"

#include <algorithm>
#include <iostream>

using namespace std;

CCollector::CCollector()
{
	cout << "CCollector::CCollector" << endl;
	m_observers.reserve(m_maxNumOfObservers);
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
	for (vector<CStatsCollectedBase*>::iterator it = m_observers.begin(); it != m_observers.end(); )
	{
		if (*it == observer)
		{
      			it = m_observers.erase(it);
			cout << "CCollector::UnRegister - found observer with address:" << observer << endl;
			return true;		
		}
		else
		{
			++it;
		}
	}

	cout << "CCollector::UnRegister - DID not find observer with address:" << observer << endl;
	return false;
}

void CCollector::NotifyObservers(CStatsCollectedBase* observer)
{
	cout << "CCollector::NotifyObservers" << endl;
	
	/*
	// if the argument is NULL - call notify ALL the observers
	if (observer == nullptr)
	{
		for (vector<CStatsCollectedBase*>::iterator it = m_observers.begin(); it != m_observers.end(); ++it)
		{
			if (it != nullptr)
			{
				(*it)->Update();
			}
		}	
	}
	else
	{
		for (vector<CStatsCollectedBase*>::iterator it = m_observers.begin(); it != m_observers.end(); ++it)
		{
			if (it != nullptr)
			{
				(*it)->Update();
			}
		}	
	}
	*/
}

