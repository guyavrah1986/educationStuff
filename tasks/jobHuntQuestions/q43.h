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
static size_t numOfFreeBlocks = NUM_OF_BLOCKS;
static void* nextFreeBlock = NULL;

void initPoolOfBlock()
{
	size_t i = 0;
	for (; i < NUM_OF_BLOCKS - 1; ++i)
	{
		printf("initPoolOfBlock - setting pool block [%lu]:%p \n", i, &(pool[(i + 1) * (BLOCK_SIZE_IN_BYTES)])); 
		pool[i] = &(pool[(i + 1) * (BLOCK_SIZE_IN_BYTES)]);
	}

	// last cell will be set to point to "NULL" (zero)
	printf("initPoolOfBlock - setting the LAST pool block [%lu]:NULL \n", i); 
	pool[i] = 0;
	nextFreeBlock = &(pool[0]);
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
	if (numOfFreeBlocks == 0)
	{
		printf("poolMalloc - no free blocks, returning NULL \n");
		return NULL;
	}

	printf("poolMalloc - the current free block is block at address:%p \n", nextFreeBlock);
	void* nextNextFreeBlock = *((*)nextFreeBlock);
	printf("poolMalloc - the address of the next free block (after using the current free block) is:%p \n", nextNextFreeBlock); 
	void* ret = nextFreeBlock;
	nextFreeBlock = nextNextFreeBlock;
	return ret;
}

void q43()
{
	printf("foo - start \n");
	initPoolOfBlock();
	disaplyPool();
}


