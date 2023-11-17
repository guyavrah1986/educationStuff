#include <stdio.h>
#include <stdint.h>

// =============================================================================
// =============================================================================
// 1) 

void displayBitsInNum(uint8_t num)
{
    const char funcName [] = "displayBitsInNum - ";
    //printf("%s got the number:%u\n", funcName, num);
    for (uint8_t i = 0; i < 8; ++i)
    {
        uint8_t currBit = num & 0x1;
        num = num >> 1;
        printf("%u ", currBit);    
    }
    
    printf("\n");
}

// This is the set of memory fields that are given
#define NUM_FIELDS 8
static int arr [NUM_FIELDS] = {0};

// This is the sole register that is used to "manage" the
// set of NUM_FIELDS memory blocks. For every block of 
// memory that was allocated - its respective bit will be set.
// When it is freeded - it will be un-set
uint8_t memFieldsManager = 0;


// This function returns a block of memory from one of the 
// statically allocated blocks of memory if there is one 
// avilable. If there are none - it returns NULL.
void* getMemBlock()
{
    // Optimization - if all blocks are occuipied we
    // hit UINT32_MAX (all ones)
    if (UINT8_MAX == memFieldsManager)
    {
        printf("getMemBlock - all blocks are occuipied, return NULL\n");
        return NULL;    
    }
    
    // At least one block is free, find it in brute force manner
    // by looking for the first bit which is not set - its position
    // will be the index of the free block to provide form the 
    // static array of memory blocks
    
    uint8_t tmp = memFieldsManager;
    uint8_t foundFreeBlock = 0;
    for (; foundFreeBlock < 8; ++foundFreeBlock)
    {
        uint8_t currBit = tmp & 0x1;
        if (0 == currBit)
        {
            printf("getMemBlock - found free block at index:%u\n", foundFreeBlock);
            memFieldsManager |= (1 << foundFreeBlock);
            break;
        }
        
        tmp = tmp >> 1;
    }
    
    // Set the bit of the memory block that will be returned
    return &(arr[foundFreeBlock]);
}

void freeMemBlock(void* memBlockToFree)
{
    const char funcName [] = "freeMemBlock - ";
    if (NULL == memBlockToFree)
    {
        printf("%s got a NULL pointer as an address to free\n", funcName);
        return;
    }
    
    // make sure that the return address is in-bounds of the arr
    if (arr > memBlockToFree || &arr[NUM_FIELDS - 1] < memBlockToFree)
    {
        printf("%s the returned address is not in the expcted range\n", funcName);
        return;
    }
    
    uint8_t indexToFree = ((int*)memBlockToFree - arr);
    printf("%s the address to free is:%p, arr is at:%p, the difference between them is:%u\n", funcName, memBlockToFree, arr, indexToFree);
    // for clean-ness of this operation, zero out the array element that is to be free
    arr[indexToFree] = 0;
    
    // indicate that this cell is free again
    memFieldsManager &= ~(1 << indexToFree);
}

// Tests for the solution
int allocateTheFirstBlockWhenAllBlocksAreFreeTest()
{
    const char funcName [] = "allocateTheFirstBlockWhenAllBlocksAreFreeTest";
    printf("%s currently, the global memFieldsManager is:\n", funcName);
    displayBitsInNum(memFieldsManager);
    
    printf("%s - asking for the FIRST block of memory\n", funcName);
    void* memBlock = getMemBlock();
    
    // 1. Make sure the returned address is indeed the one of the FIRST 
    //    cell of the array
    void* firstCellArrayAddress = arr;
    if (memBlock != arr)
    {
        printf("%s the returned memory block is NOT in the address expected. returned:%p expected:%p\n", funcName, memBlock, arr);
        return 1;
    }
    
    // 2. Make sure that the bit that the only bit that is set 
    // in the memFieldsManager is the first bit
    if (0x1 != memFieldsManager)
    {
        printf("%s expected to have only the first bit of memFieldsManager set, but instead it is:\n", funcName);
        displayBitsInNum(memFieldsManager);
        return 1;
    }
    
    printf("%s currently, the global memFieldsManager is:\n", funcName);
    displayBitsInNum(memFieldsManager);
    
    // alocate the second block of memory
    printf("%s - asking for the SECOND block of memory\n", funcName);
    memBlock = getMemBlock();
    
    // 1. Make sure the returned address is indeed the one of the SECOND 
    //    cell of the array;
    if (memBlock != &arr[1])
    {
        printf("%s the returned memory block is NOT in the address expected. returned:%p expected:%p\n", funcName, memBlock, arr);
        return 1;
    }
    
    // 2. Make sure that the bit that the only bit that is set 
    // in the memFieldsManager is the first bit
    if (0b00000011 != memFieldsManager)
    {
        printf("%s expected to have only the first bit of memFieldsManager set, but instead it is:\n", funcName);
        displayBitsInNum(memFieldsManager);
        return 1;
    }
    
    printf("%s currently, the global memFieldsManager is:\n", funcName);
    displayBitsInNum(memFieldsManager);
    
    // alocate the third block of memory
    printf("%s - asking for the THIRD block of memory\n", funcName);
    memBlock = getMemBlock();
    
    // 1. Make sure the returned address is indeed the one of the SECOND 
    //    cell of the array;
    if (memBlock != &arr[2])
    {
        printf("%s the returned memory block is NOT in the address expected. returned:%p expected:%p\n", funcName, memBlock, arr);
        return 1;
    }
    
    // 2. Make sure that the bit that the only bit that is set 
    // in the memFieldsManager is the first bit
    if (0b00000111 != memFieldsManager)
    {
        printf("%s expected to have only the first bit of memFieldsManager set, but instead it is:\n", funcName);
        displayBitsInNum(memFieldsManager);
        return 1;
    }
    
    printf("%s currently, the global memFieldsManager is:\n", funcName);
    displayBitsInNum(memFieldsManager);\
    
    printf("%s about to free the THIRD block that was allocated\n", funcName);
    freeMemBlock(memBlock);
    
    printf("%s after freeing an array block that was allocated third, the global memFieldsManager is:\n", funcName);
    displayBitsInNum(memFieldsManager);
    
    return 0;
}

// =============================================================================
// =============================================================================
// 2)
//
// this function returns the number of seconds that passed since some 
// reference point in time
int calcTime()
{
    int NumOfSecondsFromStartingPoint = 17;
    return NumOfSecondsFromStartingPoint;
}

// 1 Q) What this function does?
// 1 A) The objective of this function is to wait one hour
// 2 Q) This function runs in a context in which there are interruptes
//      
void myFunction()
{
    int time = calcTime();
    while (time - calcTime() != 3600);
}

// =============================================================================
// =============================================================================
// This is the set of memory fields that are given
#define SIZE_OF_BLCOK 16
#define NUM_OF_BLCOKS 16
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
        *(unsigned long*)tmpBlock = (char*)tmpBlock + SIZE_OF_BLCOK;
        printf("%s setting block:%u that starts at address:%p, with the address of the next block:%p\n", funcName, i, tmpBlock, *(unsigned long *)tmpBlock);
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
    
    // the memory block to return now becomes the new memList - i.e. - it is 
    // now the first block to allocate
    *memBlockToFree = memList;
    memList = memBlockToFree;
    */
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
        printf("%s block:%u starts at address:%p and points to next free block at:%p\n", funcName, i, tmpBlock, *(unsigned long*)tmpBlock);
        tmpBlock = (char *)tmpBlock + SIZE_OF_BLCOK;
    }
    
    return 0;
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
