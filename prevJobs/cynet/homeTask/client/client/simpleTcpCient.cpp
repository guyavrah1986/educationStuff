#include "stdafx.h"
#include "simpleTcpCient.h"

#include <ws2tcpip.h>
#include <iostream>

// Need to link with Ws2_32.lib, Mswsock.lib, and Advapi32.lib
#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "Mswsock.lib")
#pragma comment (lib, "AdvApi32.lib")

using namespace std;

CSimpleTcpCient::CSimpleTcpCient(IN const char* ip, IN const char* port)
	: m_connectSocket(INVALID_SOCKET)
	, m_ip(ip)
	, m_port(port)
{
	cout << "CSimpleTcpCient::CSimpleTcpCient" << endl;
}

CSimpleTcpCient::~CSimpleTcpCient()
{
	cout << "CSimpleTcpCient::~CSimpleTcpCient" << endl;
}

Result CSimpleTcpCient::ConnectToServer()
{
	WSADATA wsaData;
	struct addrinfo* serverAddrInfo = NULL, hints;
	int iResult;

	// Initialize Winsock
	iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iResult != 0) 
	{
		cerr << " CSimpleTcpCient::ConnectToServer - was unable to initialize Winsock" << endl;
		return Result(ErrorCode::ERROR_CODE_GENERAL_FAUILRE);
	}

	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;

	// Resolve the server address and port
	iResult = getaddrinfo(m_ip.c_str(), m_port.c_str(), &hints, &serverAddrInfo);
	if (iResult != 0) 
	{
		cerr << "CSimpleTcpCient::ConnectToServer - getaddrinfo failed with error:" << iResult << endl;
		WSACleanup();
		return Result(ErrorCode::ERROR_CODE_GENERAL_FAUILRE);
	}

	// Create a SOCKET for connecting to server
	m_connectSocket = socket(serverAddrInfo->ai_family, serverAddrInfo->ai_socktype, serverAddrInfo->ai_protocol);
	if (m_connectSocket == INVALID_SOCKET) 
	{
		cerr << "CSimpleTcpCient::ConnectToServer - socket failed with error:" << WSAGetLastError() << endl;
		WSACleanup();
		return Result(ErrorCode::ERROR_CODE_GENERAL_FAUILRE);
	}

	// Connect to server
	iResult = connect(m_connectSocket, serverAddrInfo->ai_addr, (int)serverAddrInfo->ai_addrlen);
	
	// Delete the server address's info struct
	freeaddrinfo(serverAddrInfo);

	if (iResult == SOCKET_ERROR) 
	{
		closesocket(m_connectSocket);
		m_connectSocket = INVALID_SOCKET;
		cerr << "CSimpleTcpCient::ConnectToServer - unable to connect to server" << endl;
		WSACleanup();
		return Result(ErrorCode::ERROR_CODE_GENERAL_FAUILRE);
	}

	cout << "CSimpleTcpCient::ConnectToServer - successfully connected to server:" << m_ip << " port:" << m_port << endl;
	return Result(ErrorCode::ERROR_CODE_SUCCESS);
}

Result CSimpleTcpCient::DisconnectFromServer() const
{
	int iResult;
	iResult = shutdown(m_connectSocket, SD_SEND);
	if (iResult == SOCKET_ERROR) 
	{
		cerr << "CSimpleTcpCient::DisconnectFromServer - shutdown failed with error:" << WSAGetLastError() << endl;;
		closesocket(m_connectSocket);
		WSACleanup();
		return Result(ErrorCode::ERROR_CODE_GENERAL_FAUILRE);
	}

	cout << "CSimpleTcpCient::DisconnectFromServer - successfully disconnected from server" << endl;
	return Result(ErrorCode::ERROR_CODE_SUCCESS);
}

int CSimpleTcpCient::SendBuffer(IN const char* sendBuff, IN int len) 
{
	// DEBUG: make it send the entire length of the sendBuff (which is filled
	// with NULL within it).
	int iResult = send(m_connectSocket, sendBuff, len, 0);
	if (iResult == SOCKET_ERROR) 
	{
		int error = WSAGetLastError();
		cerr << "CSimpleTcpCient::SendBuffer - send failed with error:" << WSAGetLastError() << " closing the connection with the server" << endl;
		//closesocket(m_connectSocket);
		//WSACleanup();
		//return -1;
	}

	cout << "CSimpleTcpCient::SendBuffer - " << iResult << " bytes were sent" << endl;
	return iResult;
}
