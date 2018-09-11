//
// sync_client.cpp
// ~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2011 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <iostream>
#include <istream>
#include <ostream>
#include <string>
#include <fstream>
#include <list>
#include <boost/asio.hpp>

#include "../include/simpleHttpGetRequestClient.h"

using boost::asio::ip::tcp;
using namespace std;

int main(int argc, char* argv[])
{
	cout << "main -start" << endl;

	if (argc < 2)
	{
		cout << "main - required more arguments, usage: exeName <wordsListFullPath> <number of requests to send>" << endl;
		return 1;
	}

	string  dbWordsListFile = argv[1];
	uint64_t numOfRequestsToSend = atoi(argv[2]);
	const string apiStr = "/api/v1/similar?word=";
	cout << "main - got words list file name:" << dbWordsListFile << endl;
	SimpleHttpGetRequestClient client;
	client.initWordsMap(dbWordsListFile);

	try
	{
		boost::asio::io_service io_service;
		string ipAddress = "localhost"; 		// in this case - loopback
		string portNum = "8000";
		string hostAddress;
		if (portNum.compare("80") != 0)
		{
			hostAddress = ipAddress + ":" + portNum;
		}
		else
		{
			hostAddress = ipAddress;
		}


		// Get a list of endpoints corresponding to the server name.
		tcp::resolver resolver(io_service);
		tcp::resolver::query query(ipAddress, portNum);
		tcp::resolver::iterator endpoint_iterator = resolver.resolve(query);

		// Try each endpoint until we successfully establish a connection.
		tcp::socket socket(io_service);
		boost::asio::connect(socket, endpoint_iterator);

		// Form the request. We specify the "Connection: close" header so that the
		// server will close the socket after transmitting the response. This will
		// allow us to treat all data up until the EOF as the content.

		boost::asio::streambuf request;
		std::ostream request_stream(&request);

		for (uint64_t i = 0; i < numOfRequestsToSend; ++i)
		{
			string wordToQuery = client.GetRandomWordFromList();
			string queryStr = apiStr + wordToQuery;
			request_stream << "GET " << queryStr << " HTTP/1.1\r\n";
			request_stream << "Host: " << hostAddress << "\r\n";
			request_stream << "Accept: */*\r\n";
			request_stream << "Connection: close\r\n\r\n";

			// Send the request.
			boost::asio::write(socket, request);
		}

		//======================================================================

		// Read the response status line. The response streambuf will automatically
		// grow to accommodate the entire line. The growth may be limited by passing
		// a maximum size to the streambuf constructor.
		boost::asio::streambuf response;
		boost::asio::read_until(socket, response, "\r\n");

		// Check that response is OK.
		std::istream response_stream(&response);
		std::string http_version;
		response_stream >> http_version;
		unsigned int status_code;
		response_stream >> status_code;
		std::string status_message;
		std::getline(response_stream, status_message);
		if (!response_stream || http_version.substr(0, 5) != "HTTP/")
		{
			std::cout << "Invalid response\n";
			return 1;
		}
		if (status_code != 200)
		{
			std::cout << "Response returned with status code " << status_code << "\n";
			return 1;
		}

		// Read the response headers, which are terminated by a blank line.
		boost::asio::read_until(socket, response, "\r\n\r\n");

		// Process the response headers.
		std::string header;
		while (std::getline(response_stream, header) && header != "\r")
		{
			std::cout << header << "\n";
		}

		std::cout << "\n";

		// Write whatever content we already have to output.
		if (response.size() > 0)
		{
			std::cout << &response;
		}

	    // Read until EOF, writing data to output as we go.
	    boost::system::error_code error;
	    while (boost::asio::read(socket, response,boost::asio::transfer_at_least(1), error))
	    {
		      std::cout << &response;
	    }

	    if (error != boost::asio::error::eof)
	    {
		      throw boost::system::system_error(error);

	    }
	}
	catch (std::exception& e)
	{
		std::cout << "Exception: " << e.what() << "\n";
	}

	return 0;
}
