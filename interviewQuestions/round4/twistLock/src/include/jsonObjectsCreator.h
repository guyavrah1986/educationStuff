#pragma once

#include "globalInternalInclude.h"

#include <string>
#include <list>

class IJsonObjectsCreator
{
public:
	/*
	 * 	The output of this function is a JSON object structured as follows:
		{
		    totalWords:int
		    totalRequests:int
		    avgProcessingTimeNs:int
		}
	 *
	 */
	virtual std::string CreateJsonObjectForStatsRequest(IN uint64_t totalWords, IN uint64_t totalRequests, IN uint64_t avgProcessingTimeNs) = 0;
	/*
	The output of this function is a JSON object as follows:
	{
	    similar:[list,of,words,that,are,similar,to,provided,word]
	}
	*/
	virtual std::string CreateJsonObjectForSimilarWordRequest(IN const std::list<std::string>& similarWordsList) = 0;
	virtual ~IJsonObjectsCreator() {}
};
