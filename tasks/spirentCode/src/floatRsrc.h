#pragma once

#include "cRsrcBase.h"

class CFloatRsrc : public CRsrcBase
{
public:
	CFloatRsrc(IN const char* rsrcUri, IN bool internalCreated);
	virtual ~CFloatRsrc();

	// IAdapRsrcValue interface method
	virtual Result AdapGetRsrcValue(INOUT SpM2mRsrcValue* value); 		//server ask to read the rsrc value.
	virtual Result AdapSetRsrcValue(IN SpM2mRsrcValue* value);			//server ask to write the rsrc value.
	virtual Result AdapExecRsrc();										//server ask to perform execution related to the rsrc.

private:
	double m_value;
};
