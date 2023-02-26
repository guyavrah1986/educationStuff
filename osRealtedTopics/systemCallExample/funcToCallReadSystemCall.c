#include<stdio.h>
#include<unistd.h>

void callReadSystemCall(const int fileDescriptor)
{
	int sz = 0;
	char buff[64] = {0};
	sz = read(fileDescriptor, buff, 40);
	//printf("callReadSystemCall - read the following %d bytes with content from file descriptor:%d - %s\n", sz, fileDescriptor, buff);
}
