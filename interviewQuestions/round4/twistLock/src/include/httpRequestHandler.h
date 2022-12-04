#pragma once

#include <string>
#include "../../utils/http-server-mongoose/mongoose.h"
#include "globalInternalInclude.h"

class IHttpRequestHandler
{
public:
	virtual void HandleHttpRequest(IN const std::string& uri, IN const std::string& query, IN struct mg_connection* nc, IN long startTime) = 0;
	virtual ~IHttpRequestHandler() {}
};
