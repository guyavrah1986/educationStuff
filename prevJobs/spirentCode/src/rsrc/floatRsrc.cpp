#include <iostream>

#include "floatRsrc.h"

using namespace std;

CFloatRsrc::CFloatRsrc(IN const char* rsrcUri, IN bool internalCreated)
	: CRsrcBase(rsrcUri, SP_M2M_RSRC_TYPE_FLOAT, internalCreated)
	, m_value(0.0)
{
	cout << "CFloatRsrc::CFloatRsrc" << endl;
}

CFloatRsrc::~CFloatRsrc()
{
	cout << "CFloatRsrc::~CFloatRsrc" << endl;
}

Result CFloatRsrc::AdapGetRsrcValue(INOUT SpM2mRsrcValue* value)
{
	cout << "CFloatRsrc::AdapGetRsrcValue" << endl;
	if (value == nullptr)
	{
		return Result(ErrorCode::SP_M2M_ERROR_CODE_GENERAL_FAUILRE);
	}

	value->type = SP_M2M_RSRC_TYPE_FLOAT;
	cout << "CFloatRsrc::AdapGetRsrcValue - rsrcVal->value is at address:" << value->value << endl;
	*(static_cast<double*>(value->value)) = m_value;
	return Result(ErrorCode::SP_M2M_ERROR_CODE_SUCCESS);
}

Result CFloatRsrc::AdapSetRsrcValue(IN SpM2mRsrcValue* value)
{
	cout << "CFloatRsrc::AdapSetRsrcValue" << endl;
	if (value == nullptr || value->type != AdapGetRsrcType())
	{
		return Result(ErrorCode::SP_M2M_ERROR_CODE_GENERAL_FAUILRE);
	}

	m_value = *(static_cast<double*>(value->value));
	return Result(ErrorCode::SP_M2M_ERROR_CODE_SUCCESS);
}

Result CFloatRsrc::AdapExecRsrc()
{
	// this resource type does not support execution...
	return Result(ErrorCode::SP_M2M_ERROR_CODE_GENERAL_FAUILRE);
}
