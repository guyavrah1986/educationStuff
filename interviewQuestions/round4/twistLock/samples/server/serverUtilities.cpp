#include "serverUtilities.h"
#include "../../src/include/basicStatsRequestResolver.h"
#include <chrono>
#include <iostream>

using namespace std;

const char* s_http_port = "8000";

struct mg_serve_http_opts s_http_server_opts;
struct mg_mgr mgr;

sock_t sock[2];
sig_atomic_t s_received_signal = 0;

BasicHttpRequestHandler* g_httpRequestHandler;

void exit_prog(IN int status, IN struct mg_mgr* mgr)
{
	mg_mgr_free(mgr);
	closesocket(sock[0]);
	closesocket(sock[1]);
	cout << "serverUtilities::exit_prog - terminating with status code:" << status << endl;
	exit(status);
}

long get_num_of_ns_since_epoch()
{
	auto now_ns = std::chrono::time_point_cast<std::chrono::nanoseconds>(std::chrono::system_clock::now());
	auto value = std::chrono::duration_cast<std::chrono::nanoseconds>(now_ns.time_since_epoch());
	return value.count();
}

void fill_work_request_item(IN struct work_request* workItem, IN const struct http_message* hm, IN struct mg_connection* nc)
{
	// copy these values anyway !!
	workItem->nc = nc;
	workItem->conn_id = (unsigned long)nc->user_data;

	workItem->invalidRequestType = get_request_invalid_request_type(hm);
	if (workItem->invalidRequestType != TS_REQUEST_VALID)
	{
		return;
	}

	// increase the g_totalNumOfRequestRecived if and only if the request is valid
	// and it is has the following uri: /api/v1/similar (i.e.- similar word request)
  	strncpy(workItem->uri, (&hm->uri)->p, (&hm->uri)->len);
  	if (memcmp(workItem->uri, "/api/v1/similar", 15) == 0)
  	{
  		++g_numOfTotalRequestsRecived;
  	}
	workItem->uri[(&hm->uri)->len] = '\0';
	strncpy(workItem->query, (&hm->query_string)->p, (&hm->query_string)->len);
	workItem->query[(&hm->query_string)->len] = '\0';
	workItem->numOfNsSinceEpoch = get_num_of_ns_since_epoch();
}

/*
 * This method verifies that the request we got is indeed one that we should
 * handle, so if any of the following rises, the method returns the respective
 * indication to note that this is an INVALID request.
 * Otherwise it returns TS_REQUEST_VALID.
 * The following scenarios are considered "not supported by the server":
// 1) URI length is greater than the "de-facto" maximum
// 2) The method is any method which is NOT GET method (i.e.- PUT,DELETE,POST...)
*/
InvalidRequestType get_request_invalid_request_type(IN const struct http_message* hm)
{
	InvalidRequestType type = TS_REQUEST_VALID;
	if ((&hm->uri)->len > TS_MAX_URI_LEN || (&hm->query_string)->len > TS_MAX_QUERY_STRING_LEN)
	{
		type = TS_REQUEST_URI_TOO_LONG;
	}
	else if ((&hm->method)->len != 3 || memcmp((&hm->method)->p, "GET", 3) != 0)
	{
		type = TS_REQUEST_UNSUPPORTED;
	}

	return type;
}

void sig_handler(int sigNum)
{
	s_received_signal = sigNum;
	switch (sigNum)
	{
	case SIGINT: cout << "serverUtilities::sig_handler - received SIGINT" << endl;
	exit_prog(SIGINT, &mgr);
	break;

	case SIGKILL: cout << "serverUtilities::sig_handler - received SIGKILL" << endl;
	exit_prog(SIGKILL, &mgr);
	break;

	default: cout << "serverUtilities::sig_handler - received signal which we did not registered to" << endl;
	break;
  }
}
