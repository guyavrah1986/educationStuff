#pragma once

#include "cStatsCollectedBase.h"

#include <vector>

class CCollector
{
	public:
	CCollector();
	virtual ~CCollector();

	bool Register(CStatsCollectedBase* observer);
	bool UnRegister(CStatsCollectedBase* observer);

	// Info API
	void NotifyObservers(CStatsCollectedBase* observer);

	// Control API
	bool StartCollecting(CStatsCollectedBase* observer);
	bool StopCollecting(CStatsCollectedBase* observer);


	private:
	std::vector<CStatsCollectedBase*> m_observers;	
	static const size_t m_maxNumOfObservers = 10;
};
