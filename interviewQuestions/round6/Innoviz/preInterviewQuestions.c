#include <stdio.h>
#include <stdint.h>

// =============================================================================
// =============================================================================
// This is the set of memory fields that are given
#define SIZE_OF_BLCOK 16
#define NUM_OF_BLCOKS 4
static char arr [SIZE_OF_BLCOK * NUM_OF_BLCOKS] = {0};

// This is the sole register that is used to "manage" the
// set of NUM_FIELDS memory blocks. For every block of 
// memory that was allocated - its respective bit will be set.
// When it is freeded - it will be un-set
void* memList = NULL;

void initMemoryBuffers()
{
    const char funcName [] = "initMemoryBuffers - ";
    size_t numOfBytesInMemory = sizeof(arr);
    printf("%s about to allocate an array that will represents the %lu bytes in memory to be used at address:%p\n", funcName, numOfBytesInMemory, arr);
    unsigned long* tmpBlock = (unsigned long *)arr;
    for (uint8_t i = 0; i < NUM_OF_BLCOKS - 1; ++i)
    {
        // for each cell, point to the next one's address
        //printf("%s (char*)tmpBlock + SIZE_OF_BLCOK is:%p\n", funcName, (char*)tmpBlock + SIZE_OF_BLCOK);
        *tmpBlock = (char*)tmpBlock + SIZE_OF_BLCOK;
        printf("%s setting block:%u that starts at address:%p, with the address of the next block:%p\n", funcName, i, tmpBlock, (void *)*(unsigned long *)tmpBlock);
        tmpBlock = (char *)tmpBlock + SIZE_OF_BLCOK;
    }
    
    //arr[NUM_FIELDS - 1] = NULL;
    *(unsigned long*)tmpBlock = 0;
    memList = arr;
}

// This function returns a block of memory from one of the 
// statically allocated blocks of memory if there is one 
// avilable. If there are none - it returns NULL.
void* getMemBlock()
{
    const char funcName [] = "getMemBlock - ";
    
    // the memList at any given time points to the next block to provide
    // so if it is NULL - that means there are no free memory blocks
    
    if (NULL == memList)
    {
        printf("%s there are no free blocks, return NULL\n", funcName);
        return NULL;
    }
    
    void* blockToReturn = memList;
    unsigned long* nextFreeBlockAddress = *(unsigned long *)memList;
    memList = nextFreeBlockAddress;
    
    // zero out the block before it is returned if needed using memset and SIZE_OF_BLCOK

    return blockToReturn;
}

void freeMemBlock(void* memBlockToFree)
{
    const char funcName [] = "freeMemBlock - ";
    if (NULL == memBlockToFree)
    {
        printf("%s got a NULL pointer as an address to free\n", funcName);
        return;
    }
    
    /*
    // validate input - make sure that the returned address is indeed in the 
    // range of the actuall block of memory
    if (memBlockToFree < arr || memBlockToFree > &arr[NUM_FIELDS - 1])
    {
        printf("%s the address of the block of memory to return:%p - is not in the range of the given array\n", funcName, memBlockToFree);
        return;
    }
    */
    printf("%s freeing memory block at address:%p\n", funcName, memBlockToFree);
    // the memory block to return now becomes the new memList - i.e. - it is 
    // now the first block to allocate
    *(unsigned long *)memBlockToFree = memList;
    memList = memBlockToFree;
    
}

// Tests for the solution
int allocateTheFirstBlockWhenAllBlocksAreFreeTest()
{
    const char funcName [] = "allocateTheFirstBlockWhenAllBlocksAreFreeTest";
    initMemoryBuffers();
    void* tmpBlock = arr;
    for (uint8_t i = 0; i < NUM_OF_BLCOKS; ++i)
    {
        // for each cell, point to the next one's address
        //arr[i] = &arr[i + 1];
        //*(unsigned long*)tmpBlock = arr + SIZE_OF_BLCOK * i;
        printf("%s block:%u starts at address:%p and points to next free block at:%p\n", funcName, i, tmpBlock, (void *)*(unsigned long*)tmpBlock);
        tmpBlock = (char *)tmpBlock + SIZE_OF_BLCOK;
    }
    
    void* memBlock1 = getMemBlock();
    printf("%s got FIRST memory block of address:%p\n", funcName, memBlock1);
    
    void* memBlock2 = getMemBlock();
    printf("%s got SECOND memory block of address:%p\n", funcName, memBlock2);
    
    void* memBlock3 = getMemBlock();
    printf("%s got THIRD memory block of address:%p\n", funcName, memBlock3);
    
    freeMemBlock(memBlock2);
    freeMemBlock(memBlock1);
    freeMemBlock(memBlock3);
    
    memBlock1 = getMemBlock();
    printf("%s got FIRST memory block after releasing all of the 3 before - it is in address:%p\n", funcName, memBlock1);
    return 0;
}

// =============================================================================
// =============================================================================

int timeOfDay()
{
    return 17;
}

int absoult(int val)
{
    if (val < 0)
    {
        return val * (-1);
    }
    
    return val;
}

// original question function 
void func()
{
    int start = timeOfDay();
    while (timeOfDay() - start != 3600);
}

// solutiion
void funcFixed()
{
    int timeout = 3600;
    int start = timeOfDay();
    int lastTime = 0;
    while (1)
    {
        lastTime = timeOfDay() - start;
        if (lastTime < 0)
        {
            timeout = absoult(lastTime);
            start = timeOfDay();
        }
        if (timeOfDay() - start >= timeout)
        {
            break;
        }
    }
}

// =============================================================================
// =============================================================================

int main()
{
    printf("main - start\n");
    
    // 1)
    if (0 != allocateTheFirstBlockWhenAllBlocksAreFreeTest())
    {
        printf("main - allocateTheFirstBlockWhenAllBlocksAreFreeTest FAILED\n");
    }
    else
    {
        printf("main - allocateTheFirstBlockWhenAllBlocksAreFreeTest PASSED\n");
    }
    
    printf("main - end\n");
    return 0;
}
