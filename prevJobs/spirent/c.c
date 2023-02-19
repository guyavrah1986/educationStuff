#include <stdio.h>

#include "c.h"

struct sampleStruct funcThatGetPointerToCppClassAndTreatItAsStrcut(void* pStruct)
{
	const char funcName[] = "funcThatGetPointerToCppClassAndTreatItAsStrcut - ";
	printf("%s start\n", funcName);
	printf("%s got pointer in address:%p\n", funcName, pStruct);
	
	struct sampleStruct ss;
	/* first member of the struct (class) is an int, so "extract" it */
	int* px = (int *)pStruct;
	int x = *px;
	ss.x = *px;
	pStruct = (char*)pStruct + sizeof(int);
	int* py = (int *)pStruct;
	int y = *py;
	ss.y = *py;
	pStruct = (char*)pStruct + sizeof(int);
	char* pc = (char*)pStruct;
	char c = *pc;
	ss.c = c;
	printf("%s got the following values pointed by pStruct: x=%d, y=%d, c=%c\n", funcName, x, y, c);
	printf("%s end\n", funcName);
	return ss;
}

