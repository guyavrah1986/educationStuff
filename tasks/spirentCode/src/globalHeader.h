#pragma once

#define IN
#define OUT
#define INOUT

enum EnProtocolType
{
	SP_M2M_PROTOCOL_TYPE_LWM2M = 0,
	SP_M2M_PROTOCOL_TYPE_MQTT
};

enum EnRsrcType
{
	SP_M2M_RSRC_TYPE_PARENT_RSRC = 0,
	SP_M2M_RSRC_TYPE_INT,
	SP_M2M_RSRC_TYPE_FLOAT,
	SP_M2M_RSRC_TYPE_STRING
};

enum ErrorCode
{
	SP_M2M_ERROR_CODE_SUCCESS = 0,
	SP_M2M_ERROR_CODE_GENERAL_FAUILRE
};

class Result
{
public:
	Result(const enum ErrorCode& errorCode)
		: m_errorCode(errorCode)
	{

	}

	bool IsSuccess() const
	{
		return (m_errorCode == ErrorCode::SP_M2M_ERROR_CODE_SUCCESS);
	}

private:
	ErrorCode m_errorCode;
};

class SdkConnection
{
	public:
	SdkConnection(unsigned short portNumber, int socketNum, const char* ipAddress)
		: m_portNumber(portNumber)
		, m_socketNum(socketNum)
		, m_ipAddress(ipAddress)
	{
		std::cout << "SdkConnection::SdkConnection - setting m_ipAddress to:" << m_ipAddress << std::endl;
	}
	~SdkConnection()
	{
		std::cout << "SdkConnection::~SdkConnection" << std::endl;
	}	
	
	private:
	unsigned short m_portNumber;
	int m_socketNum;
	std::string m_ipAddress;
};


