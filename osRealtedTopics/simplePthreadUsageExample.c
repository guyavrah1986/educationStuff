// =================================================================================================================================
// =================================================================================================================================
// Threads in Linux (POSIX based):
// -------------------------------
// 1) All threads of a process are creating usign the pthread_create (POSIX based) pthread library call.
// 2) All threads of a process, despite the fact that they are threads, have PCB (=Process Control Block) and a PID, just like
//    any other process in the system.
// 3) All threads of the same process are "linked" together via a concept called "thread group". Within the PCB of each thread of 
//    the same process, the thread_group field will be the SAME. The filed tgid for ALL threads will have the value of the "first"
//    thread of this threads group --> which is the "main thread".
// 4) The unique per thread ID for each thread in the process is avialble via this system call. It provides the actual 
//    "kernel-aware" thread ID for the thread - which is in fact the kernel PID of this thread (as seen in the figure below).
//     A potential output of the below program might be (where 14458 is the thread ID of the "main thread"):
//     guya@guya-ubuntu:/tmp$ ps -T -p 14458
//     PID     SPID   TTY      TIME      CMD
//     14458   14458  pts/1    00:00:00  prog
//     14458   14459  pts/1    00:00:00  prog
//     14458   14460  pts/1    00:00:00  prog
//
// 5) All threads of the same process share the "main thread" PID as thier tgid (=Thread Group ID).
// 6) Threads of the same process share (can access) all "global" variables that they have "scope" access to. In this case the
//    only applicable "global" variable is this.
// 7) When working (linking) with POSIX threds (pthread.h), this library "replaces" the implementation of some of the relevant
//    system calls that deal with threads on Linux machines.
// 8) It is possible to terminate the run of the thread, usually when it is done with the execution of its function, with 
//    the pthread_exit API.
//
//
// Usefull links:
// - Get thread ID in a portable manner: https://stackoverflow.com/a/32211287/1971003
// - PID, TGID and thier relationships: https://stackoverflow.com/a/9306150/1971003
//
//                          USER VIEW
//                          vvvv vvvv
//              |          
//<-- PID 43 -->|<----------------- PID 42 ----------------->
//              |                           |
//              |      +---------+          |
//              |      | process |          |
//              |     _| pid=42  |_         |
//         __(fork) _/ | tgid=42 | \_ (new thread) _
///       /     |      +---------+          |       \
//+---------+   |                           |    +---------+
//| process |   |                           |    | process |
//| pid=43  |   |                           |    | pid=44  |
//| tgid=43 |   |                           |    | tgid=42 |
//+---------+   |                           |    +---------+
//              |                           |
//<-- PID 43 -->|<--------- PID 42 -------->|<--- PID 44 --->
//              |                           |
//                        ^^^^^^ ^^^^
//                        KERNEL VIEW
//
//
// =================================================================================================================================
// =================================================================================================================================
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/syscall.h>

typedef void* (*funcPointer)(void*);

int globalInt = 17; //6)

void* thread1_func(void* arg)
{
	int intArg = *(int*)arg;
	printf("thread1_func - got an int value of:%d\n", intArg);
	pid_t threadId = syscall(__NR_gettid); // 4)
	printf("thread1_func - the thread ID is:%d\n", threadId);
	int input;
	printf("thread1_func - please enter a number\n");
	scanf("%d", &input);
	globalInt++;
	printf("thread1_func - got:%d\n", input);
	printf("thread1_func - terminating thread\n");
	*(int*)arg = 0;
 	pthread_exit(arg); // 8) 
}

void* thread2_func(void* arg)
{
	int intArg = *(int*)arg;
	printf("thread2_func - got an int value of:%d\n", intArg);
	pid_t threadId = syscall(__NR_gettid);
	printf("thread2_func - the thread ID is:%d\n", threadId);
	int input;
	printf("thread2_func - please enter a number\n");
	scanf("%d", &input);
	globalInt++;
	printf("thread2_func - got:%d\n", input);
	printf("thread2_func - terminating thread\n");
	return NULL;
}

int main()
{
	printf("main - start\n");
	int parentPid = getpid();
	pthread_t threadIdArr[2] = {0};
	int threadNumArr[2] = {1, 2};
	funcPointer funcPointerArr[2] = {&thread1_func, &thread2_func};
	int retCode;
	printf("main - parent process PID is:%d and initially the globalInt is:%d\n", parentPid, globalInt);
	
	// create the threads
	for (int i = 0; i < 2; ++i)
	{
		retCode = pthread_create(&threadIdArr[i], NULL, funcPointerArr[i], &threadNumArr[i]); // 1)	
		if (0 != retCode)
		{
			printf("main - was unable to create thread number:%d\n", i++);
			return 1;
		}
	}

	// join ("wait") to the threads
	for (int i = 0; i < 2; ++i)
	{
		retCode = pthread_join(threadIdArr[i], NULL);
		if (0 != retCode)
		{
			printf("main - was unable to join thread number:%d\n", i + 1);
			return 1;
		}
		
		printf("main - joined thread number:%d\n", i + 1);
	}

	printf("main - eventually globalInt is:%d\n", globalInt);
	printf("main - end\n");
	return 0;
}
