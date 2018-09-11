#pragma once

#include "../../src/include/globalInternalInclude.h"
#include "../../src/include/basicHttpRequestHandler.h"
#include "../../utils/http-server-mongoose/mongoose.h"

// ===========================================================================
// Global objects
// ===========================================================================
// DesginNote: see discussion here: https://stackoverflow.com/questions/417142/what-is-the-maximum-length-of-a-url-in-different-browsers
const size_t TS_MAX_URI_LEN = 2040;
const size_t TS_MAX_QUERY_STRING_LEN = 2040;

extern const char* s_http_port;;
extern struct mg_serve_http_opts s_http_server_opts;
extern struct mg_mgr mgr;

extern sig_atomic_t s_received_signal;
extern sock_t sock[2];

extern BasicHttpRequestHandler* g_httpRequestHandler;

// ===========================================================================
// structs definitions
// ===========================================================================

// This info is passed to the worker thread
struct work_request
{
	unsigned long conn_id;  // needed to identify the connection where to send the reply
	// optionally, more data that could be required by worker
	char uri [TS_MAX_URI_LEN];
	char query [TS_MAX_QUERY_STRING_LEN];
	long numOfNsSinceEpoch;
	struct mg_connection* nc;
	InvalidRequestType invalidRequestType;
};

// This info is passed by the worker thread to mg_broadcast
struct work_result
{
	unsigned long conn_id;
	long startTime;
};


// ===========================================================================
// functions definitions
// ===========================================================================

void exit_prog(IN int status, IN struct mg_mgr* mgr);
void fill_work_request_item(IN struct work_request* workItem, IN const struct http_message* hm, IN struct mg_connection* nc);
InvalidRequestType get_request_invalid_request_type(IN const struct http_message* hm);
void sig_handler(IN int sigNum);

