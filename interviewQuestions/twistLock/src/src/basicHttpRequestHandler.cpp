#include "../include/basicHttpRequestHandler.h"
#include "../include/requestNavigator.h"
#include "../../utils/http-server-mongoose/mongoose.h"

#include <iostream>
#include <vector>
#include <list>

using namespace std;

BasicHttpRequestHandler::BasicHttpRequestHandler(IN const string& prefixApi, IN const string& dbFileName)
	: m_dbFileName(dbFileName)
	, m_requestNavigator(prefixApi)
	, m_dbManager()
	, m_statsRequestResolver(0)

{
	cout << "BasicHttpRequestHandler::BasicHttpRequestHandler" << endl;
}

Result BasicHttpRequestHandler::Init()
{
	Result res = m_dbManager.InitDB(m_dbFileName);
	if (res.IsSuccess() == false)
	{
		return res;
	}

	m_statsRequestResolver.Init(m_dbManager.GetTotalNumOfWordsInDb());
	return res;
}

BasicHttpRequestHandler::~BasicHttpRequestHandler()
{
	cout << "BasicHttpRequestHandler::~BasicHttpRequestHandler" << endl;
}

void BasicHttpRequestHandler::HandleHttpRequest(IN const string& uri, IN const string& query, IN struct mg_connection* nc, IN long startTime)
{
	cout << "BasicHttpRequestHandler::HandleHttpRequest - got URI:" << uri << " and query:" << query << endl;
	string extractedWord;
	RequestType reqType = m_requestNavigator.GetRequestTypeFromURI(uri, query, extractedWord);

	if (reqType == RequestType::TS_REQUEST_TYPE_STATS)
	{
		vector<uint64_t> statsInfoVec;
		statsInfoVec.reserve(3);
		Result res = m_statsRequestResolver.GetStatsInfo(statsInfoVec);
		if (res.IsSuccess() == true)
		{
			string jsonObjStr = m_jsonObjCreator.CreateJsonObjectForStatsRequest(statsInfoVec[0], statsInfoVec[1], statsInfoVec[2]);
			sendHttpOkResponse(nc, jsonObjStr);
		}
		else
		{
			sendHttpErrorResponse(nc , 500);
		}
	}
	else if (reqType == TS_REQUEST_TYPE_SIMILAR_WORDS)
	{
		list<string> matchedWordsList;
		Result res = m_similarWordsRequesrResolver.GetListOfSimilarWords(m_dbManager, extractedWord, matchedWordsList);
		if (res.IsSuccess() == false)
		{
			sendHttpErrorResponse(nc , 500);
		}
		else
		{
			string jsonObjStr = m_jsonObjCreator.CreateJsonObjectForSimilarWordRequest(matchedWordsList);
			sendHttpOkResponse(nc, jsonObjStr);
			long numOfNsSinceEpochEnd = getNumOfNsSinceEpoch();
			m_statsRequestResolver.UpdateStatsUponServingRequest(numOfNsSinceEpochEnd - startTime);
		}
	}
	else
	{
		cerr << "BasicHttpRequestHandler::HandleHttpRequest - got an unsupported  HTTP request" << endl;
		sendHttpErrorResponse(nc , 500);
	}
}

void BasicHttpRequestHandler::sendHttpErrorResponse(IN struct mg_connection* nc, IN int errorCode)
{
	mg_http_send_error(nc, errorCode, NULL);
}

void BasicHttpRequestHandler::sendHttpOkResponse(IN struct mg_connection* nc, IN const string& jsonObjStr)
{
	mg_printf(nc, "%s", "HTTP/1.1 200 OK\r\nTransfer-Encoding: chunked\r\n\r\n");
	mg_printf_http_chunk(nc, jsonObjStr.c_str());

	 // send empty chunk to indicate the end of response
	mg_send_http_chunk(nc, "", 0);
}

void BasicHttpRequestHandler::handleInvalidHttpRequestEvent(IN struct mg_connection* nc, IN InvalidRequestType invalidRequestType)
{
	cout << "serverHttpRequestHandling::handle_invalid_http_request_event" << endl;
	switch (invalidRequestType)
	{
		case TS_REQUEST_URI_TOO_LONG:
		{
			sendHttpErrorResponse(nc , 414);
			break;
		}
		case TS_REQUEST_UNSUPPORTED:
		{
			sendHttpErrorResponse(nc , 400);
			break;
		}
		default:
		{
			sendHttpErrorResponse(nc , 500);
			break;
		}
	}
}

long BasicHttpRequestHandler::getNumOfNsSinceEpoch()
{
	auto now_ns = std::chrono::time_point_cast<std::chrono::nanoseconds>(std::chrono::system_clock::now());
	auto value = std::chrono::duration_cast<std::chrono::nanoseconds>(now_ns.time_since_epoch());
	return value.count();
}
