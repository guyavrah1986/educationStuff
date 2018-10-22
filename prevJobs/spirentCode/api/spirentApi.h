#pragma once

#include "spirentSdkInclude.h"

#ifdef __cplusplus
extern "C"
{
#endif

struct SpM2mCoreMgr;

struct SpM2mCoreMgr* SpM2mCreateCoreMgr();
enum SpStatus SpM2mDestroyCoreMgr(struct SpM2mCoreMgr* pCoreMgr);

#ifdef __cplusplus
}
#endif

//enum SpStatus SpM2mCreateCoreMgr(INOUT SpM2mCoreMgr** pCoreMgr);

//enum SpStatus CreateClient(INOUT struct CCoreClient** p);

/*
SpStatus CreateRsrc(IN const char* rsrcUri,
					IN EnProtocolType eType,
					IN bool bInternalCreated,
					INOUT CRsrcBase*& pRsrc);
*/
