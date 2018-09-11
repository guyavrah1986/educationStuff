#include "../include/basicStatsRequestResolver.h"
#include "../../samples/server/serverUtilities.h"

#include <iostream>
#include <vector>

using namespace std;

atomic<uint64_t> g_numOfTotalRequestsRecived{0};

BasicStatsRequestResolver::BasicStatsRequestResolver(IN size_t totalNumOfWordsInDB)
	: m_totalNumOfWordsInDB(totalNumOfWordsInDB)
	, m_avgReqDurationNanoSec(0)
{
	cout << "BasicStatsRequestResolver::BasicStatsRequestResolver" << endl;
}

BasicStatsRequestResolver::~BasicStatsRequestResolver()
{
	cout << "BasicStatsRequestResolver::~BasicStatsRequestResolver" << endl;
}

void BasicStatsRequestResolver::Init(IN const size_t totalNumOfWordsInDB)
{
	m_totalNumOfWordsInDB = totalNumOfWordsInDB;
	cout << "BasicStatsRequestResolver::Init - setting m_totalNumOfWordsInDB to:" << m_totalNumOfWordsInDB << endl;
}

Result BasicStatsRequestResolver::GetStatsInfo(INOUT vector<uint64_t>& statsInfo)
{
	// insert the counters in their correct order
	m_mutex.lock();
	statsInfo.emplace_back(m_totalNumOfWordsInDB);
	statsInfo.emplace_back(g_numOfTotalRequestsRecived);
	statsInfo.emplace_back(m_avgReqDurationNanoSec);
	m_mutex.unlock();

	return (Result(ErrorCode::TS_SUCCESS));
}

void BasicStatsRequestResolver::UpdateStatsUponServingRequest(IN uint64_t reqDurationNanoSec)
{
	m_mutex.lock();
	m_avgReqDurationNanoSec += reqDurationNanoSec;
	if (g_numOfTotalRequestsRecived != 0)
	{
		m_avgReqDurationNanoSec = m_avgReqDurationNanoSec / g_numOfTotalRequestsRecived;
	}
	m_mutex.unlock();
}

uint64_t BasicStatsRequestResolver::GetAvgRequestDurationNanoSeconds() const
{
	return m_avgReqDurationNanoSec;
}

uint64_t BasicStatsRequestResolver::GetTotalNumOfRequests() const
{
	return g_numOfTotalRequestsRecived;
}
