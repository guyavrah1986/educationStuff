// =========================================================================================================================
// =========================================================================================================================
// System call example:
// --------------------
// gcc -g -O0 -c -fverbose-asm -Wa,-adhln classMembersLayoutAndAccessWithSingleInheritence.cpp > test.lst
//
//
// =========================================================================================================================
// =========================================================================================================================
#include<stdio.h>
#include<string.h>
#include <fcntl.h>

#include "funcToCallReadSystemCall.h"

int main(int argc, char** argv)
{
	printf("main - start\n");
	printf("main - argument is: %s\n", argv[1]);
	char fileName[16] = {0};
	size_t strLen = strlen(argv[1]);
	memcpy(fileName, argv[1], strLen);
	printf("main - got file name:%s\n", fileName);
    	int fileDescriptor = open(fileName, O_RDONLY | O_CREAT);
	printf("main - the file descriptor for file:%s, is:%d\n", fileName, fileDescriptor);
	callReadSystemCall(fileDescriptor);
	printf("main - end\n");
	return 0;
}
