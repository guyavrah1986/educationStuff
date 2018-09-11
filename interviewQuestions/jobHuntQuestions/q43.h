// =========================================================================================================================================================
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
// =========================================================================================================================================================

#include <stdio.h>


#define BLOCK_SIZE_IN_BYTES 8
#define NUM_OF_BLOCKS 8

static char pool [(BLOCK_SIZE_IN_BYTES) * (NUM_OF_BLOCKS)];
static size_t numOfFreeBlocks = NUM_OF_BLOCKS;
static int nextFreeBlock = 0;

void initPoolOfBlock()
{
	size_t i = 0;
	for (; i < NUM_OF_BLOCKS - 1; ++i)
	{
		printf("initPoolOfBlock - setting next free block for block [%lu]:%lu at address:%p \n", i, (i + 1), &(pool[(i * BLOCK_SIZE_IN_BYTES)])); 
		pool[(i * BLOCK_SIZE_IN_BYTES)] = (i + 1);
	}

	// last cell will be set to point to "NULL" (-1)
	pool[(i * BLOCK_SIZE_IN_BYTES)] = NUM_OF_BLOCKS;
	printf("initPoolOfBlock - setting the LAST pool block [%lu]:%lu at address:%p \n", i, pool[(i * BLOCK_SIZE_IN_BYTES)], NUM_OF_BLOCKS, &(pool[(i * BLOCK_SIZE_IN_BYTES)])); 
	nextFreeBlock = 0;
	printf("initPoolBlock - setting nextFreeBlock to:%lu , start of the pool is at address:%p \n", nextFreeBlock, &(pool[0]));
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

	printf("poolMalloc - current free block is:%lu with an offset of %lu bytes from the start of the pool \n", nextFreeBlock, (nextFreeBlock * BLOCK_SIZE_IN_BYTES));

	// calculate the offset of the current free block - and return its address
	void* ret = &(pool[(nextFreeBlock * BLOCK_SIZE_IN_BYTES)]);
	printf("poolMalloc - returning address:%p \n", &(pool[(nextFreeBlock * BLOCK_SIZE_IN_BYTES)]));

	// get the number of the "next" free block - by extracting the block number from this block
	nextFreeBlock = *((int*)ret);
	numOfFreeBlocks--;
	printf("poolMalloc - the next free block is block:%d \n", nextFreeBlock); 
	return ret;
}

void poolFree(void* block)
{
	printf("poolFree - got block at address:%p \n", block);
	
	// calculate the offset of the block from the start of the pool	
	size_t offset = (char*)block - (char*)&(pool[0]);
	size_t numOfBlockToFree = offset / BLOCK_SIZE_IN_BYTES;

	if (numOfFreeBlocks == 0)
	{
		printf("poolFree - there are no free block untill now, so we set the NEXT free block to be NULL (-1). current (only) free block is at address:%p \n", &(pool[(numOfBlockToFree * BLOCK_SIZE_IN_BYTES)]));
		pool[(numOfBlockToFree * BLOCK_SIZE_IN_BYTES)] = -1;
	}
	else
	{
		printf("poolFree - there were %d free blocks untill now, so we set the NEXT free block to be block number:%lu at address:%p \n", numOfFreeBlocks,  numOfBlockToFree,  &(pool[(nextFreeBlock * BLOCK_SIZE_IN_BYTES)]));
		*((size_t*)pool[(nextFreeBlock * BLOCK_SIZE_IN_BYTES)]) = numOfBlockToFree;
	}
	printf("poolFree - block to free is at offset of:%lu from the start of the pool , which is block:%d \n", offset, numOfBlockToFree);
	numOfFreeBlocks++;
}

void q43()
{
	printf("foo - start \n");
	initPoolOfBlock();
	disaplyPool();
}


