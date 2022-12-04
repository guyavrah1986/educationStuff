#include "../include/basicJsonObjectCreator.h"

#include <iostream>
#include <algorithm>

using namespace std;

BasicJsonObjectCreator::BasicJsonObjectCreator()
{
	cout << "BasicJsonObjectCreator::BasicJsonObjectCreator" << endl;
}

BasicJsonObjectCreator::~BasicJsonObjectCreator()
{
	cout << "BasicJsonObjectCreator::~BasicJsonObjectCreator" << endl;
}

string BasicJsonObjectCreator::CreateJsonObjectForStatsRequest(IN uint64_t totalWords, IN uint64_t totalRequests, IN uint64_t avgProcessingTimeNs)
{
	string ret = "{\"totalWords\":" + to_string(totalWords) + ", \"totalRequests\":"
			+ to_string(totalRequests) + ", \"avgProcessingTimeNs\":" + to_string(avgProcessingTimeNs) + "}";

	return ret;
}

string BasicJsonObjectCreator::CreateJsonObjectForSimilarWordRequest(IN const list<string>& similarWordsList)
{
	nlohmann::json j_list(similarWordsList);
	string ret = j_list.dump();
	ret = "{\"similar\":" + ret + "}";

	return ret;
}
