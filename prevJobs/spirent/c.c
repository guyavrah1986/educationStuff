#include <stdio.h>

#include "c.h"

struct sampleStruct funcThatGetPointerToCppClassAndTreatItAsStrcut(void* pStruct)
{
	const char funcName[] = "funcThatGetPointerToCppClassAndTreatItAsStrcut - ";
	printf("%s start\n", funcName);
	printf("%s got pointer in address:%p\n", funcName, pStruct);
	
	struct sampleStruct ss;
	/* first member of the struct (class) is an int, so "extract" it */
	int* intPointer = (int *)pStruct;
	ss.x = *intPointer;
	pStruct = (char*)pStruct + sizeof(int);
	intPointer = (int *)pStruct;
	ss.y = *intPointer;
	pStruct = (char*)pStruct + sizeof(int);
	char* charPointer = (char*)pStruct;
	ss.c = *charPointer;
	printf("%s got the following values pointed by pStruct: x=%d, y=%d, c=%c\n", funcName, ss.x, ss.y, ss.c);
	printf("%s end\n", funcName);
	return ss;
}

