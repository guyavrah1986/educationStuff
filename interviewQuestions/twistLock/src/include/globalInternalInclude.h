#pragma once

// ====================================================================================
// MACROS
// ====================================================================================

// Specify the type of the argument
#define IN 
#define OUT
#define INOUT

#define NO_COPY(T) T& operator=(const T& rhs) = delete; \
				   T(const T& other) = delete;


// ====================================================================================
// enums, classes, structs, etc...
// ====================================================================================


enum InvalidRequestType
{
	TS_REQUEST_VALID = 0,
	TS_REQUEST_URI_TOO_LONG,
	TS_REQUEST_UNSUPPORTED,
	TS_INTERNAL_SERVER_ERROR
};

enum ErrorCode
{
	TS_SUCCESS = 0,
	TS_DB_MG_NO_SIMILAR_WORDS,
	TS_GENERAL_FAUILRE
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
		return (m_errorCode == ErrorCode::TS_SUCCESS);
	}

private:
	ErrorCode m_errorCode;
};

