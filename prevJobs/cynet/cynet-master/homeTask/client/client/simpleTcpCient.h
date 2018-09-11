#pragma once

#include "cpp.hint"
#include "globalHeader.h"

#include <string>

// For the SOCKET definition (extracted from headers that are included in <winsock2.h>)
typedef unsigned __int64 UINT_PTR;
typedef UINT_PTR SOCKET;

class CSimpleTcpCient
{
	NO_COPY(CSimpleTcpCient);

public:
	CSimpleTcpCient(IN const char* ip, IN const char* port);
	~CSimpleTcpCient();

	Result ConnectToServer();
	Result DisconnectFromServer() const;
	int SendBuffer(IN const char* sendBuff, IN int len);

private:
	SOCKET m_connectSocket;

	std::string m_ip;
	std::string m_port;
};