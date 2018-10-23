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
enum SpStatus SpM2mDestroyCoreMgr(IN struct SpM2mCoreMgr* pCoreMgr);

// ======================================
// CCoreClient related APIs:
// ======================================
struct SpM2mCoreClient;

struct SpM2mCoreClient* SpM2mCreateCoreClient(IN struct SpM2mCoreMgr* pCoreMgr);
enum SpStatus SpM2mDestroyCoreClient(IN struct SpM2mCoreClient* pCoreClient);

// ======================================
// AdaptorProtocol related APIs:
// ======================================

enum SpStatus SpM2mCreateAdaptor(IN struct SpM2mCoreClient* pCoreClient, IN enum EnProtocolType protocolType);

// ======================================
// CRsrcBase related APIs:
// ======================================

enum SpStatus CreateRsrc(IN const char* rsrcUri,
						 IN enum SpEnRsrcType rsrcType,
						 IN enum EnProtocolType protocolType);

// ======================================
// Adaptors related APIs:
// ======================================

enum SpStatus CreateAdapter(IN enum EnProtocolType);

#ifdef __cplusplus
}
#endif

