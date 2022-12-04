#pragma once

#include "statsRequestResolver.h"

#include <string>
#include <mutex>
#include <atomic>

extern std::atomic<uint64_t> g_numOfTotalRequestsRecived;

class BasicStatsRequestResolver : public IStatsRequestResolver
{
	NO_COPY(BasicStatsRequestResolver);

// methods
public:
	explicit BasicStatsRequestResolver(IN size_t totalNumOfWordsInDB);
	virtual ~BasicStatsRequestResolver();
	void Init(IN const size_t totalNumOfWordsInDB);
	virtual Result GetStatsInfo(INOUT std::vector<uint64_t>& statsInfo) override;
	virtual void UpdateStatsUponServingRequest(IN uint64_t reqDurationNanoSec) override;

	// DesginNote: For debug & unit tests
	uint64_t GetAvgRequestDurationNanoSeconds() const;
	uint64_t GetTotalNumOfRequests() const;

// members:
private:
	size_t m_totalNumOfWordsInDB;
	uint64_t m_avgReqDurationNanoSec;
	std::mutex m_mutex;
};
