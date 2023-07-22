// =================================================================================================================================
// =================================================================================================================================
// Processes in Linux (POSIX based):
// --------------------------------
// 1) The return value of this system call will return the PID of the child process that we were waiting for.
// 2) Note that all the "common" variables that were declared BEFORE the fork took place will reside in both the parent and the
//    child processes in DIFFERENT copies - i.e. - each of which will have its own copy, thus modifiying the variable in one 
//    process DOES NOT affect the "other copy" in the child process.
// 3) Note that this pointer to file, is avialble for both the parent and the child process. In this example, the father opened it
//    nevertheless, it is totally fine that the child will "use it" as well.
//
// =================================================================================================================================
// =================================================================================================================================
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>

int main()
{
	printf("main - start\n");
	int parentPid = getpid();
	int childPid = -1;
	const char sharedFilePath [] = "textFileOfFatherProcess.txt";
	FILE* ptr;
    	char buffToReadFileInto[2048] = {0};
    	ptr = fopen(sharedFilePath, "a+"); // 3)
 
	if (NULL == ptr)
	{
        	printf("main - file can't be opened\n");
		return 1;
	}
 
    	printf("main - content of the file at first are:\n");
 
	while (fgets(buffToReadFileInto, 2048, ptr) != NULL)
	{
        	printf("%s", buffToReadFileInto);
	}
 
	// till here only a single process (and thread) were used.

	printf("main - parent process PID is:%d\n", parentPid);
	// make two process which run same program after this instruction
	// from this line of code and on, there will be the parent + child processes 
	// running.
	if (fork() == 0)
	{
		// this code will run in the child process
		childPid = getpid();
		printf("main (child) - the child process PID is:%d\n", childPid);
		printf("main (child) - content of the file in the child context are:\n");
        	printf("%s", buffToReadFileInto);
		// now let's do some "hack" by altering the content of the buffToReadFileInto
		buffToReadFileInto[4] = '\0';
		printf("main (child) - content of the file in the child context AFTER IT WAS ALTERD are:\n");
	        printf("%s\n", buffToReadFileInto);
	
	}
	else
	{
		// here, we are still in "parent context"
		printf("main (parent) - after forking, parent process PID is:%d, YET the child PID is:%d\n", parentPid, childPid);
		int status;
		pid_t waitPid = wait(&status);// 1) Wait for "some" child process to finish
		printf("main (parent) - after waiting for child process with PID:%d, that terminated with status(zero == success):%d\n", waitPid, status);
		printf("main (parent) - content of the file in the parent context AFTER IT WAS ALTERD by the child process eariler are:\n");
	        printf("%s\n", buffToReadFileInto); // 2)
		fclose(ptr);
  	}

	printf("main - end\n");
	return 0;
}
