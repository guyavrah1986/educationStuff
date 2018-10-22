#include <stdlib.h>
#include "../api/spirentApi.h"
#include "../src/rsrc/cRsrcBase.h"
 
struct SpM2mRsrcBase
{
    void* obj;
};
 
struct SpM2mRsrcBase* SpM2mCreateResource(IN const char* pRsrcUri,
										  IN SpEnRsrcType rsrcType,
										  IN bool bInternalCreated)
{
	struct SpM2mRsrcBase* p = (typeof p)malloc(sizeof(*p));

 
    return p;
}
 
enum SpStatus SpM2mDestroyResource(struct SpM2mRsrcBase* pRsrc)
{
    if (pRsrc == NULL)
    {
    	printf("SpM2mDestroyResource - got a NULL pointer \n");
    	return SP_M2M_STATUS_GENERAL_FAUILRE;
    }

    return SP_M2M_STATUS_SUCCESS;
}
