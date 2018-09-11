#pragma once

#include "jsonObjectsCreator.h"
#include "../../utils/json/src/json.hpp"

class BasicJsonObjectCreator : public IJsonObjectsCreator
{
	NO_COPY(BasicJsonObjectCreator);

public:
	BasicJsonObjectCreator();
	virtual ~BasicJsonObjectCreator();

	virtual std::string CreateJsonObjectForStatsRequest(IN uint64_t totalWords, IN uint64_t totalRequests, IN uint64_t avgProcessingTimeNs) override;
	virtual std::string CreateJsonObjectForSimilarWordRequest(IN const std::list<std::string>& similarWordsList) override;
};
