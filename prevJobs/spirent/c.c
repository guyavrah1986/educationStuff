#include <stdio.h>

#include "c.h"

void funcThatGetPointerToCppClassAndTreatItAsStrcut(void* pStruct)
{
	const char funcName[] = "funcThatGetPointerToCppClassAndTreatItAsStrcut - ";
	printf("%s start\n", funcName);
	printf("%s got pointer in address:%p\n", funcName, pStruct);
	
	/* first member of the struct (class) is an int, so "extract" it */
	int* px = (int *)pStruct;
	int x = *px;
	pStruct += sizeof(int);
	int* py = (int *)pStruct;
	int y = *py;
	pStruct += sizeof(int);
	char* pc = (char*)pStruct;
	char c = *pc;
	printf("%s got the following values pointed by pStruct: x=%d, y=%d, c=%c\n", funcName, x, y, c);
	printf("%s end\n", funcName);
}

