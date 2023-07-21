#include <stdio.h>

#include "sampleFile.h"

void func1(int x)
{
	printf("func1 - got x:%d\n", x);
}

short func2(int* ptr)
{
	printf("func2 - the value pointed by ptr is:%d, at location:%p\n", *ptr, ptr);
}

int func3(struct myStruct* pMyStruct)
{
	printf("func3 - pMyStruct points to location:%p\n",pMyStruct);
}
