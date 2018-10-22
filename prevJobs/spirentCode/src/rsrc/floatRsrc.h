#pragma once

#include "cRsrcBase.h"

class CFloatRsrc : public CRsrcBase
{
public:
	CFloatRsrc(IN const char* rsrcUri, IN bool internalCreated);
	virtual ~CFloatRsrc();

	// IAdapRsrcValue interface method
	virtual Result AdapGetRsrcValue(INOUT SpM2mRsrcValue* value);
	virtual Result AdapSetRsrcValue(IN SpM2mRsrcValue* value);
	virtual Result AdapExecRsrc();

private:
	double m_value;
};
