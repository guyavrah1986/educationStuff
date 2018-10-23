#include <stdio.h>

// The inclusion of the Spirent SDK
#include "../api/spirentApi.h"

void mainLoop()
{
	printf("mainLoop - start \n");
	return;
}

int main(int argc, char** argv)
{
	printf("main - start\n");

	struct SpM2mCoreMgr* pCoreMgr = SpM2mCreateCoreMgr();
	if (pCoreMgr == NULL)
	{
		printf("main - was unable to create SpM2mCoreMgr correctly, aborting\n");
		return 1;
	}

	struct SpM2mCoreClient* pCoreClient = SpM2mCreateCoreClient(pCoreMgr);
	if (pCoreClient == NULL)
	{
		printf("main - was unable to create SpM2mCoreClient correctly, aborting\n");
		return 1;
	}

	enum SpStatus res = SpM2mCreateAdaptor(pCoreClient, SP_M2M_PROTOCOL_TYPE_LWM2M);
	if (res != SP_M2M_STATUS_SUCCESS)
	{
		printf("main - was unable to add adaptor of type %d \n", SP_M2M_PROTOCOL_TYPE_LWM2M);
	}

	mainLoop();

	printf("main - done with main loop, about to destroy SpM2mCoreClient \n");

	res = SpM2mDestroyCoreClient(pCoreClient);
	if (res != SP_M2M_STATUS_SUCCESS)
	{
		printf("main - was unable to destroy SpM2mCoreClient correctly \n");
	}

	printf("main - done with main loop, about to destroy SpM2mCoreMgr \n");
	res = SpM2mDestroyCoreMgr(pCoreMgr);
	if (res != SP_M2M_STATUS_SUCCESS)
	{
		printf("main - was unable to destroy SpM2mCoreMgr correctly \n");
	}

	printf("\n \n main - end \n");
	return 0;
}
