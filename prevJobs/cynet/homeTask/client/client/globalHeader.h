#pragma once

// ====================================================================================
// COMPILATION (CONFIGURATION) RELATERD MACROS
// ====================================================================================

// Uncomment (and re-build) this in order to send ASCII characters (default is UTF-16)
//#define SEND_ASCII

// Uncomment this in order to disable the application and run unit tests
//#define UNIT_TESTING

// ====================================================================================
// FUNCTION RELATERD MACROS
// ====================================================================================

// Specify the type of the argument
#define IN 
#define OUT
#define INOUT

#define NO_COPY(T) T& operator=(const T& rhs) = delete;\
				   T(const T& other) = delete;


// ====================================================================================
// enums, classes, structs, etc...
// ====================================================================================

enum ErrorCode
{
	ERROR_CODE_SUCCESS = 0,
	ERROR_CODE_GENERAL_FAUILRE
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
		return (m_errorCode == ErrorCode::ERROR_CODE_SUCCESS);
	}

private:
	ErrorCode m_errorCode;
};