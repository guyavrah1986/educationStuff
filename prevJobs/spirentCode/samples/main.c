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

	mainLoop();

	printf("main - done with main loop, about to destroy SpM2mCoreMgr \n");

	enum SpStatus res = SpM2mDestroyCoreMgr(pCoreMgr);
	if (res != SP_M2M_STATUS_SUCCESS)
	{
		printf("main - was unable to destroy SpM2mCoreMgr correctly \n");
	}

	printf("\n \n main - end \n");
	return 0;
}
