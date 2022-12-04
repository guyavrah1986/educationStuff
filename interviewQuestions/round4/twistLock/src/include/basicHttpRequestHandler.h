#pragma once

#include "httpRequestHandler.h"
#include "../include/basicRequestNavigator.h"
#include "../include/basicStatsRequestResolver.h"
#include "../include/basicJsonObjectCreator.h"
#include "../include/basicSimilarWordsResolver.h"
#include "../include/hashDbManager.h"

class BasicHttpRequestHandler : public IHttpRequestHandler
{
	NO_COPY(BasicHttpRequestHandler);

public:
	BasicHttpRequestHandler(IN const std::string& prefixApi, IN const std::string& dbFileName);
	virtual ~BasicHttpRequestHandler();
	virtual void HandleHttpRequest(IN const std::string& uri, IN const std::string& query, IN struct mg_connection* nc, IN long startTime) override;
	void handleInvalidHttpRequestEvent(IN struct mg_connection* nc, IN InvalidRequestType invalidRequestType);
	Result Init();

private:
	void sendHttpErrorResponse(IN struct mg_connection* nc, IN int errorCode);
	void sendHttpOkResponse(IN struct mg_connection* nc, IN const std::string& jsonObjStr);
	long getNumOfNsSinceEpoch();

// members:
private:
	const std::string& m_dbFileName;
	BasicRequestNavigator m_requestNavigator;
	BasicStatsRequestResolver m_statsRequestResolver;
	BasicJsonObjectCreator m_jsonObjCreator;
	BasicSimilarWordsResolver m_similarWordsRequesrResolver;
	HashDbManager m_dbManager;
};
