#pragma once

#include "spirentSdkInclude.h"

#ifdef __cplusplus
extern "C"
{
#endif

// ======================================
// CCoreMgr related APIs:
// ======================================
struct SpM2mCoreMgr;

struct SpM2mCoreMgr* SpM2mCreateCoreMgr();
enum SpStatus SpM2mDestroyCoreMgr(struct SpM2mCoreMgr* pCoreMgr);

// ======================================
// CRsrcBase related APIs:
// ======================================
/*
SpStatus CreateRsrc(IN const char* rsrcUri,
					IN EnProtocolType eType,
					IN bool bInternalCreated,
					INOUT CRsrcBase** pRsrc);
					*/
#ifdef __cplusplus
}
#endif

