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

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

// for documenataion
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

int main(int argc, char** argv)
{
	printf("main - start \n");
	uint8_t* arr = createRandomArray(NUM_OF_ELEMENTS_IN_ARRAY);
	printf("main - after creating the array it is: \n");	
	displayArray(arr, NUM_OF_ELEMENTS_IN_ARRAY);

	reorderArray(arr, NUM_OF_ELEMENTS_IN_ARRAY);
	printf("main - after reordering the array it is: \n");	
	displayArray(arr, NUM_OF_ELEMENTS_IN_ARRAY);

	if (arr != 0)
	{
		printf("main - freeing arr \n");
		free(arr);
	}
	printf("\n \n main - end \n");
	return 0;
}
