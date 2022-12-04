#include <stdio.h>

#include "reachEndOfTwoDimMatrix.h"
/*
* We will use a recursive call, where:
* 1) The stop condition will return:
*    - 1, if we reached the arr[N,M]
*    - 0, if we went out of "bounds" of the array.
* 2) The recursive call will invoke the function again, once where we move right and once where we move down.
*    NOTE: dim1 & dim2 are always sent with the original size of the array (N,M).
*
*/ 
int numOfPathsToEndOfTwoDimMatrix(int x, int y, int dim1, int dim2)
{
	if (x == dim1 - 1 && y == dim2 - 1)
	{
		return 1;
	}

	if (x > dim1 - 1 || y > dim2 - 1)
	{
		return 0;
	}

	return numOfPathsToEndOfTwoDimMatrix(x + 1, y, dim1, dim2) + numOfPathsToEndOfTwoDimMatrix(x, y + 1, dim1, dim2);
}
