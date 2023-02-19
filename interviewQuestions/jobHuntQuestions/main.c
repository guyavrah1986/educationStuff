// ===========================================================================================================================================================
// ===========================================================================================================================================================
/*
* question 1:
* -----------
* You are given an array filled with colors (red/green/blue). Reorder the array so that it will contain:
* RED,GREEN,BLUE elements in that order.
* You have no extra space for that.
*
* NOTES:
* a) 
*/
// ===========================================================================================================================================================
// ===========================================================================================================================================================

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#include "linkedList.h"
#include "q7.h"
#include "q30.h"
#include "q43.h"
#include "q53.h"
#include "q54.h"
#include "q79.h"

// for documentaion
#define IN 
#define OUT
#define INOUT 

#define NUM_OF_COLORS 3
#define NUM_OF_ELEMENTS_IN_ARRAY 8

enum Color
{
	RED = 0,
	GREEN,
	BLUE
};

uint8_t* createRandomArray(size_t size)
{
	uint8_t* arr = (uint8_t*)malloc(size * (sizeof(uint8_t)));
	printf("createRandomArray - creating the array with the following values: \n");
	for (size_t i = 0; i < size; ++i)
	{
		/* random int between 0 and (NUM_OF_COLORS - 1) */
		int r = rand() % NUM_OF_COLORS;
		arr[i] = r;
		printf("arr[%u]:%u ",i, arr[i]);
	}
	printf("createRandomArray - end \n");
	return arr;	
}

void displayArray(uint8_t* arr, size_t size)
{
	printf("displayArray - start \n");
	for (size_t i = 0; i < size; ++i)
	{
		const char* color;
		switch(*arr)
		{
			case RED: color = "RED";
				  break;
			
			case GREEN: color = "GREEN";
				  break;

			case BLUE: color = "BLUE";
				  break;

			default: color = "NON";
				  break;

		}
		printf("| %s ",color);
		arr++;	
	}
	printf("| \n");
	printf("displayArray - end \n ");
} 

void reorderArray(uint8_t* arr, size_t size)
{
	// holds the upper most NUMBER "number" that has not been "puhsed yet"
	// towards the end.
	size_t currBlueFromTheEnd = size - 1;

	// holds the upper most RED "number" that has not been "puhsed yet"
	// towards the start.
	size_t currRedFromTheStart = 0;

	// for debug
	size_t numOfIters = 0;

	while (currRedFromTheStart < currBlueFromTheEnd)
	{
		if (arr[currRedFromTheStart] != RED)
		{
			// find the "first red" you encounter from the current position of 
			// the "lower most sorted" BLUE and downwards
			size_t tmp = currBlueFromTheEnd;			
			while (tmp > currRedFromTheStart)
			{
				if (arr[tmp] != RED)
				{	
					++tmp;
				}
				else 
				{
					uint8_t tmpVal = arr[currRedFromTheStart];
					arr[currRedFromTheStart] = arr[tmp];
					arr[tmp] = tmpVal;
					break;
				}
			}	
		}


		if (arr[currBlueFromTheEnd] != BLUE)
		{
			// find the "first blue" you encounter from the current position of 
			// the "upper most sorted" RED and upwards
			size_t tmp = currRedFromTheStart;			
			while (tmp < currBlueFromTheEnd)
			{
				if (arr[tmp] != BLUE)
				{	
					++tmp;
				}
				else 
				{
					uint8_t tmpVal = arr[currBlueFromTheEnd];
					arr[currBlueFromTheEnd] = arr[tmp];
					arr[tmp] = tmpVal;
					break;
				}
			}
		}

		currRedFromTheStart++;
		currBlueFromTheEnd--;
		numOfIters++;
		printf("reorderArray - after %u iterations the array is: \n ",numOfIters);	
		displayArray(arr, NUM_OF_ELEMENTS_IN_ARRAY);
		
	}
}


void q1()
{
	printf("q1 - start \n");
	uint8_t* arr = createRandomArray(NUM_OF_ELEMENTS_IN_ARRAY);
	printf("q1 - after creating the array it is: \n");	
	displayArray(arr, NUM_OF_ELEMENTS_IN_ARRAY);

	reorderArray(arr, NUM_OF_ELEMENTS_IN_ARRAY);
	printf("q1 - after reordering the array it is: \n");	
	displayArray(arr, NUM_OF_ELEMENTS_IN_ARRAY);

	if (arr != 0)
	{
		printf("q1 - freeing arr \n");
		free(arr);
	}
	printf("\n \nq1 - end \n");
}

void question7()
{
	printf("question7 - start \n");

	const size_t sizeOfArray = 6;
	int* pArr1 = (int*)malloc(sizeof(int) * sizeOfArray);

	q7(pArr1, sizeOfArray);
	printf("question7 - FIRST random array generated is: \n");
	size_t i = 0;
	for (; i < sizeOfArray; ++i)
	{
		printf("[%d]", pArr1[i]);
	}

	printf("\n \n question7 - end \n");
}

void question30()
{
	printf("question30 - start \n");
	const char str1 [] = "abcde";
	const char str2 [] = "abcde";
	printf("question 30 - called strCmp for str1:%s and str2:%s -- which returned:%d \n",str1, str2, strCmp(str1, str2));
	
	const char str3 [] = "abcd";
	const char str4 [] = "abcde";
	printf("question 30 - called strCmp for str1:%s and str2:%s -- which returned:%d \n",str3, str4, strCmp(str3, str4));

	const char str5 [] = {'\0'};
	const char str6 [] = "e";
	printf("question 30 - called strCmp for str1:%s and str2:%s -- which returned:%d \n",str5, str6, strCmp(str5, str6));
	
	const char str7 [] = "abcdd";
	const char str8 [] = "abcde";
	printf("question 30 - called strCmp for str1:%s and str2:%s -- which returned:%d \n",str7, str8, strCmp(str7, str8));

	const char str9 [] = "ac";
	const char str10 [] = "ab";
	printf("question 30 - called strCmp for str1:%s and str2:%s -- which returned:%d \n",str9, str10, strCmp(str9, str10));
}

void question43()
{
	printf("question43 - start \n");

	// initialization required
	q43();
	void* pArr[8];
	size_t i = 0, numOfMallocs = 8;
	printf("question43 - about to call poolMalloc for %d times in a row \n", numOfMallocs);
	for (; i < numOfMallocs; ++i)
	{
		pArr[i] = poolMalloc();
	}

	printf("question43 - about to call poolMalloc after all blocks were allocated \n");
	void* pUnAllocated = poolMalloc();

	int blockToFree = 5;
	printf("question43 - about to call poolFree for the %d block at address:%p after all blocks were allocated \n", blockToFree, &(pArr[blockToFree]));
	poolFree(pArr[blockToFree]);

	pArr[blockToFree] = poolMalloc();
	printf("question43 -  after call to poolMalloc the block which we got is at address:%p \n", pArr[blockToFree]);

	printf("\n \n question43 - end \n");
}


void question53()
{
	printf("question53 - start \n");	
	char* p = myMalloc(17);
	printf("question53 - got address:%p from myMalloc \n", p);
	myFree(p);

	printf("\n \n question53 - end \n");	
}

void question54()
{
	printf("question54 - start \n");	
	q54Usage();

	printf("\n \n question54 - end \n");
}

void question79()
{
	printf("question79 - start \n");
	
}

int main(int argc, char** argv)
{
	printf("main - start \n");

	//q1();

	//q2();

	//question7();
		
	//question30();

	//question43();

	question53();

	//question54();	
	
	//question79();

	printf("\n \n main - end \n");
	return 0;
}
