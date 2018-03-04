#pragma once

#include "globalHeader.h"

typedef struct _SpM2mRsrcValue SpM2mRsrcValue;

struct _SpM2mRsrcValue
{
	EnRsrcType type;
	void* value;
};

class IAdapRsrcValue
{
public:
	virtual Result AdapGetRsrcValue(INOUT SpM2mRsrcValue* value) = 0; 		// server ask to read the rsrc value.
	virtual Result AdapSetRsrcValue(IN SpM2mRsrcValue* value) = 0;			// server ask to write the rsrc value.
	virtual Result AdapExecRsrc() = 0;										// server ask to perform execution related to the rsrc.

	virtual ~IAdapRsrcValue() {}
};
