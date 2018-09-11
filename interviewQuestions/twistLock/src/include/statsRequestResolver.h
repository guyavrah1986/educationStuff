#pragma once

#include "globalInternalInclude.h"

#include <cstdint>
#include <vector>
#include <chrono>

class IStatsRequestResolver
{

public:
	virtual Result GetStatsInfo(INOUT std::vector<uint64_t>& statsInfo) = 0;
	virtual void UpdateStatsUponServingRequest(IN uint64_t reqDurationNanoSec) = 0;
	virtual ~IStatsRequestResolver() {}
};
