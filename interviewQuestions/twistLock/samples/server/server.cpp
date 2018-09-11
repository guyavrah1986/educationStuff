/*
 * Copyright (c) 2014 Cesanta Software Limited
 * All rights reserved
 */

#include <iostream>

#include "serverUtilities.h"
#include "../../src/include/basicHttpRequestHandler.h"
#include "../../utils/http-server-mongoose/mongoose.h"

using namespace std;

// ===========================================================================
// Global objects defined outside of this file
// ===========================================================================
static unsigned long s_next_id = 0;

// ===========================================================================
// functions definitions
// ===========================================================================

void* worker_thread_proc(void* param)
{
	struct mg_mgr *mgr = static_cast<struct mg_mgr *>(param);
	struct work_request req = {0};

	while (s_received_signal == 0)
	{
		// get the thread's dedicated data that is passed to us form the main thread
		if (read(sock[1], &req, sizeof(req)) < 0)
		{
			cerr << "main::worker_thread_proc - ERROR reading worker sock - ignoring this request (unable to send the client"
					" the response cause the connection_id argument might be invalid)" << endl;
			// TODO: Should we terminate here the server ?
			// NOTE: we can not send here a response to the client such as: "Internal server error 500"
			// cause we get the struct mg_connection* struct from reading the socket (which is undefined
			// in this case).
			continue;
		}

		if (req.nc == NULL)
		{
			cerr << "main::worker_thread_proc - ERROR req.nc == NULL, ignoring this request..." << endl;
			continue;
		}

		else if (req.invalidRequestType != TS_REQUEST_VALID)
		{
			g_httpRequestHandler->handleInvalidHttpRequestEvent(req.nc, req.invalidRequestType);
		}
		else
		{
			// do the thread's job
			g_httpRequestHandler->HandleHttpRequest(string(req.uri), string(req.query), req.nc, req.numOfNsSinceEpoch);
		}
	}
	return NULL;
}

static void ev_handler(struct mg_connection* nc, int ev, void* ev_data)
{
	(void) nc;
	(void) ev_data;

	struct http_message* hm = static_cast<struct http_message*>(ev_data);
	switch (ev)
	{
		case MG_EV_ACCEPT:
		{
			nc->user_data = (void *)++s_next_id;
			break;
		}
		case MG_EV_HTTP_REQUEST:
		{
			struct work_request req = {0};
			fill_work_request_item(&req, hm, nc);
			if (write(sock[0], &req, sizeof(req)) < 0)
			{
				cerr << "main::ev_handler - ERROR writing to worker threads socket, this request will be ignored..." << endl;
				// TODO: should we send here an error for the client upon write to socket error ?
				// g_httpRequestHandler->handleInvalidHttpRequestEvent(req.nc, req.invalidRequestType);
			}
			break;
		}
		case MG_EV_CLOSE:
		{
			if (nc->user_data) nc->user_data = NULL;
		}
	}
}

// ======================================================================================================================
// ======================================================================================================================
// main function
// ======================================================================================================================
// ======================================================================================================================

int main(int argc, char *argv[])
{
	struct mg_connection* nc;
	struct mg_bind_opts bind_opts;
	int numWorkerThreads;
	int timeoutMsForPoll = 1000;
	string dbFile;
	const string prefixApi = "/api/v1/";

#if MG_ENABLE_SSL
	const char *ssl_cert = NULL;
#endif

	if (argc < 2)
	{
		cerr << "main - not enough arguments supplied to main, aborting..." << endl;
		exit_prog(1, &mgr);
	}

	// argv[1] = DB file name provided by its full path
	// argv[2] = number of worker threads
	dbFile = argv[1];
	numWorkerThreads = atoi(argv[2]);

	// registers for signals
	signal(SIGINT, sig_handler);
	signal(SIGKILL, sig_handler);

	// perform initialization to all the objects that needs to
	BasicHttpRequestHandler httpRequestHandler(prefixApi, dbFile);
	g_httpRequestHandler = &httpRequestHandler;
	Result res = g_httpRequestHandler->Init();
	if (res.IsSuccess() == false)
	{
		cerr << "main - error initializing the BasicHttpRequestHandler, aborting..." << endl;
		exit_prog(1, &mgr);
	}

	if (mg_socketpair(sock, SOCK_STREAM) == 0)
	{
		cerr << "main - error opening socket pair, aborting..." << endl;
		exit_prog(1, &mgr);
	}

	// initialize the manager struct
	mg_mgr_init(&mgr, NULL);
	memset(&bind_opts, 0, sizeof(bind_opts));

#if MG_ENABLE_SSL
	if (ssl_cert != NULL) {
		bind_opts.ssl_cert = ssl_cert;
	}
#endif

	nc = mg_bind_opt(&mgr, s_http_port, ev_handler, bind_opts);
	if (nc == NULL)
	{
		cerr << "main - error starting server on port:" << s_http_port << " .Error message:" <<  *bind_opts.error_string << endl;
		exit_prog(1, &mgr);
	}

	mg_set_protocol_http_websocket(nc);
	s_http_server_opts.enable_directory_listing = "no";


	for (size_t i = 0; i < numWorkerThreads; ++i)
	{
	    mg_start_thread(worker_thread_proc, &mgr);
	}

	cout << "main - starting server on port:" << s_http_port << " with DB file:" << dbFile << " and " << numWorkerThreads << " worker threads" << endl;
	// always-on server mode
	while (s_received_signal == 0)
	{
		mg_mgr_poll(&mgr, timeoutMsForPoll);
	}

	cout << "main - end" << endl;
	exit_prog(0, &mgr);
}
