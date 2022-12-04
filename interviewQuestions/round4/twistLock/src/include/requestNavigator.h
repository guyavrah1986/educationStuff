#pragma once

#include <string>

#include "globalInternalInclude.h"

enum RequestType
{
	TS_REQUEST_TYPE_STATS = 0,
	TS_REQUEST_TYPE_SIMILAR_WORDS,
	TS_REQUEST_TYPE_UNKNOWN
};


class IRequestNavigator
{

public:
	virtual	RequestType GetRequestTypeFromURI(IN const std::string& uri, IN const std::string& query, INOUT std::string& extractedWord) = 0;
	virtual ~IRequestNavigator() {}
};
