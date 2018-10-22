#include <stdlib.h>
#include "../api/spirentApi.h"
#include "coreMgr.h"
 
struct SpM2mCoreMgr
{
    void* obj;
};
 
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

    CCoreMgr *p = static_cast<CCoreMgr*>(pCoreMgr->obj);
    p->DestroyInstance();
    free(pCoreMgr);
    return SP_M2M_STATUS_SUCCESS;
}
