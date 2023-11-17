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
