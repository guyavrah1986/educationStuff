
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/syscall.h>
#include <pthread.h>

typedef void* (*funcPointer)(void*);

void* func1(void* arg)
{
	int localVarFunc1 = 17;
	printf("func1 - localVarFunc1 is:%d, address of globalVar is:%p\n, address of localVarFunc1 is:%p\n", localVarFunc1, (void*)&globalVar, (void*)&localVarFunc1);
	return NULL;
}

void* func2(void* arg)
{
	int localVarFunc2 = 15;
	printf("func2 - localVarFunc2 is:%d, address of globalVar is:%p, address of localVarFunc2 is:%p\n", localVarFunc2, (void*)&globalVar, (void*)&localVarFunc2);
	return NULL;
}

int runTwoThreads()
{
	int parentPid = getpid();

	pthread_t threadIdArr[2] = {0};
	int threadNumArr[3] = {1, 2, 3};
	pid_t threadId = syscall(__NR_gettid);
	printf("runTwoThreads - threadId:%d\n", threadId);
	funcPointer funcPointerArr[2] = {&func1, &func2};
	int retCode;
	printf("runTwoThreads - parent process PID is:%d and initially the globalInt is:%d\n", parentPid, globalVar);
	
	// create the threads
	for (int i = 0; i < 2; ++i)
	{
		retCode = pthread_create(&threadIdArr[i], NULL, funcPointerArr[i], &threadNumArr[i]);	
		if (0 != retCode)
		{
			printf("runTwoThreads - was unable to create thread number:%d\n", i++);
			return 1;
		}
	}

	// join ("wait") to the threads
	for (int i = 0; i < 2; ++i)
	{
		retCode = pthread_join(threadIdArr[i], NULL);
		if (0 != retCode)
		{
			printf("runTwoThreads - was unable to join thread number:%d\n", i + 1);
			return 1;
		}
		
		printf("runTwoThreads - joined thread number:%d\n", i + 1);
	}

	printf("runTwoThreads - end\n");
	return 0;
}

	int retCode = runTwoThreads();
	if (retCode != 0)
	{
		printf("runTwoThreads - failed\n");
	}


