#pragma once

enum ErrorCode
{
	FS_SQS_ERROR_CODE_SUCCESS = 0,
	FS_SQS_ERROR_CODE_GENERAL_FAUILRE
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
		return (m_errorCode == ErrorCode::FS_SQS_ERROR_CODE_SUCCESS);
	}

private:
	ErrorCode m_errorCode;
};
