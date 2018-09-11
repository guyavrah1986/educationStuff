// =====================================================================================================================================================================
/*
*  question 7:
* ------------
* Given a list of N different songs - arrange them in a random order. You may use the random function that returns a random integer within a given (provided) range.
*
*/
// =====================================================================================================================================================================

#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#define NUM_OF_SONGS 10

void q7(int* pArr, size_t size)
{
	printf("q7 - start \n");
	srand(time(NULL));   		    // should only be called once

	size_t i = 0;
	for (; i < size; ++i)
	{		
		pArr[i] = i;
	}

	printf("q7 - BEFORE randomizing the array: \n");
	for (i = 0; i < size; ++i)
	{
		printf("[%d] ",pArr[i]);
	}

	for (i = size - 1; i > 0; --i)
	{
		int r = rand() % i;      // returns a pseudo-random integer between [0,i - 1]
		int tmp = pArr[i];
		pArr[i] = pArr[r];
		pArr[r] = tmp;
	}

	printf("\n \n q7 - end \n");
}
