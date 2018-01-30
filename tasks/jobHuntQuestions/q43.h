// =========================================================================================================================================
/*
* Question 43:
* ------------
* The solution will be based on the fact that - each block (8 bytes) can be pointed (we can hold its address) with less than 8 bytes,
* so each block will hold (initialy) the address of the first bytes of the next block - which basically will form a "linked list".
* 
*
*
*
*/
// =========================================================================================================================================

#include <stdio.h>


#define BLOCK_SIZE_IN_BYTES 8
#define NUM_OF_BLOCKS 8

static char pool [(BLOCK_SIZE_IN_BYTES) * (NUM_OF_BLOCKS)];
static char* nextFreeBlock = &(pool[0]);

void initPoolOfBlock()
{
	size_t i = 0;
	for (; i < NUM_OF_BLOCKS - 1; ++i)
	{
		printf("initPoolOfBlock - setting pool block [%lu]:%p \n", i, &(pool[(i + 1) * (BLOCK_SIZE_IN_BYTES)])); 
		pool[i] = &(pool[(i + 1) * (BLOCK_SIZE_IN_BYTES)]);
	}

	// last cell will be set to point to "NULL" (zero)
	printf("initPoolOfBlock - setting the LAST pool block [%lu]:0 \n", i); 
	pool[i] = 0;
	printf("initPoolBlock - setting nextFreeBlock to:%p \n", nextFreeBlock);
}

void disaplyPool()
{
	size_t i = 0;
	for (; i < NUM_OF_BLOCKS ; ++i)
	{
		printf("disaplyPool - pool[%lu]:%p \n", i, (char*)pool[i]);
	}
}

void* poolMalloc()
{
	printf("poolMalloc - start \n");
	if (nextFreeBlock == 0)
	{
		printf("poolMalloc - no free block, returning NULL \n");
		return NULL;
	}

	
}

void q43()
{
	printf("foo - start \n");
	initPoolOfBlock();
	disaplyPool();
}


