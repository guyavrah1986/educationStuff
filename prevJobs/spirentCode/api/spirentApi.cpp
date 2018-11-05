#include <stdlib.h>

#include "../api/spirentApi.h"
#include "coreMgr.h"
 
struct SpM2mCoreMgr
{
    void* obj;
};

struct SpM2mCoreClient
{
	void* obj;
};
 
// ======================================
// CCoreMgr related APIs:
// ======================================
struct SpM2mCoreMgr* SpM2mCreateCoreMgr()
{
	struct SpM2mCoreMgr* p = (typeof p)malloc(sizeof(*p));
    p->obj = CCoreMgr::GetInstance();

    return p;
}
 
enum SpStatus SpM2mDestroyCoreMgr(struct SpM2mCoreMgr* pCoreMgr)
{
    if (pCoreMgr == NULL)
    {
    	printf("SpM2mDestroyCoreMgr - got a NULL pointer \n");
    	return SP_M2M_STATUS_GENERAL_FAUILRE;
    }

    CCoreMgr* p = static_cast<CCoreMgr*>(pCoreMgr->obj);
    if (p == NULL)
    {
    	printf("SpM2mDestroyCoreMgr - got a NULL pointer for the encapsulated CCoreMgr object\n");
    }
    else
    {
        p->DestroyInstance();
    }

    free(pCoreMgr);
    return SP_M2M_STATUS_SUCCESS;
}

// ======================================
// CCoreClient related APIs:
// ======================================
struct SpM2mCoreClient* SpM2mCreateCoreClient(struct SpM2mCoreMgr* pCoreMgr)
{
    if (pCoreMgr == NULL)
    {
    	printf("SpM2mCreateClient - got a NULL pointer \n");
    	return NULL;
    }

    CCoreMgr* p = static_cast<CCoreMgr*>(pCoreMgr->obj);
    if (p == NULL)
    {
    	printf("SpM2mCreateClient - got a NULL pointer in the object (pointer) within the SpM2mCoreMgr (which is a CCoreMgr object)\n");
    	return NULL;
    }

	struct SpM2mCoreClient* ret = (typeof ret)malloc(sizeof(*ret));
    if (ret == NULL)
    {
    	printf("SpM2mCreateClient - was unable to allocate memory to the SpM2mCoreClient struct, returning a NULL pointer\n");
    	return NULL;
    }

	CCoreClient* client = p->CreateClient();
    if (client == NULL)
    {
    	printf("SpM2mCreateClient - was unable to create a CCoreClient, returning a NULL pointer\n");
    	return NULL;
    }

    ret->obj = client;
    return ret;
}

enum SpStatus SpM2mDestroyCoreClient(IN struct SpM2mCoreClient* pCoreClient)
{
	if (pCoreClient == NULL)
	{
    	printf("SpM2mDestroyCoreClient - got NULL pointer\n");
    	return SP_M2M_STATUS_GENERAL_FAUILRE;
	}

    CCoreClient* p = static_cast<CCoreClient*>(pCoreClient->obj);
    if (p == NULL)
    {
    	printf("SpM2mDestroyCoreClient - got a NULL pointer for the encapsulated CCoreClient object\n");
    }
    else
    {
        delete p;
    }

    free(pCoreClient);
    return SP_M2M_STATUS_SUCCESS;
}

// ======================================
// AdaptorProtocol related APIs:
// ======================================
enum SpStatus SpM2mCreateAdaptor(IN struct SpM2mCoreClient* pCoreClient, IN enum EnProtocolType protocolType)
{
	if (pCoreClient == NULL)
	{
    	printf("SpM2mCreateAdaptor - got NULL pointer\n");
    	return SP_M2M_STATUS_GENERAL_FAUILRE;
	}

    CCoreClient* p = static_cast<CCoreClient*>(pCoreClient->obj);
    if (p == NULL)
    {
    	printf("SpM2mCreateAdaptor - got a NULL pointer for the encapsulated CCoreClient object\n");
    	return SP_M2M_STATUS_GENERAL_FAUILRE;
    }

    SpStatus res = p->GetAdapMgr().AddProtocolAdapter(protocolType);
    if (res != SP_M2M_STATUS_SUCCESS)
    {
    	printf("SpM2mCreateAdaptor - was unable to create protocol adaptor of type %d \n", protocolType);
    	return SP_M2M_STATUS_GENERAL_FAUILRE;
    }

	return SP_M2M_STATUS_SUCCESS;
}

