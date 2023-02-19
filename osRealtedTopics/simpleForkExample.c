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
    	ptr = fopen(sharedFilePath, "a+");
 
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
 

	printf("main - parent process PID is:%d\n", parentPid);
	// make two process which run same program after this instruction
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
		pid_t waitPid = wait(&status);
		printf("main (parent) - after waiting for child process with PID:%d, that terminated with status(zero == success):%d\n", waitPid, status);
		printf("main (parent) - content of the file in the parent context AFTER IT WAS ALTERD by the child process eariler are:\n");
	        printf("%s\n", buffToReadFileInto);
		fclose(ptr);
  	}

	printf("main - end\n");
	return 0;
}
