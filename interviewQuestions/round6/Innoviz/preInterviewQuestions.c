#include <stdio.h>
#include <stdint.h>

// This is the set of memory fields that are given
#define NUM_FIELDS 32
static int arr [NUM_FIELDS] = {0};

// This is the sole register that is used to "manage" the
// set of NUM_FIELDS memory blocks. For every block of 
// memory that was allocated - its respective bit will be set.
// When it is freeded - it will be un-set
uint32_t memFieldsManager = 0;


// This function returns a block of memory from on of the 
// statically allocated blocks of memory if there is one 
// avilable. If there are none - it returns NULL.
void* getMemBlock()
{
    // Optimization - if all blocks are occuipied When
    // hit UINT32_MAX (all ones)
    if (UINT32_MAX == memFieldsManager)
    {
        printf("getMemBlock - all blocks are occuipied, return NULL\n");
        return NULL;    
    }
    
    // At least one block is free, find it in brute force manner
    // by looking for the first bit which is not set - its position
    // will be the index of the free block to provide form the static
    // static array of memory blocks
    
    uint32_t tmp = memFieldsManager;
    uint8_t foundFreeBlock = 0;
    while (tmp >= 0)
    {
        uint8_t currBit = (tmp >> ++foundFreeBlock) & 0x1;
        if (0 == currBit)
        {
            printf("getMemBlock - found free block at index:%u\n", --foundFreeBlock);
            break;
        }
        
        tmp = tmp >> 1;
    }
    
    // When we get here, foundFreeBlock will be the index of the 
    // memory block we will return
    memFieldsManager |= (1 << foundFreeBlock);
    return &(arr[foundFreeBlock]);
}

void freeMemBlock(uint8_t indexOfMemBlockToFree)
{
    if (NUM_FIELDS <= indexOfMemBlockToFree)
    {
        printf("freeMemBlock - got an invalid index of memory block\n");
        return;
    }
    
    // if needed, clear the memory block that was released
    
    
}

// this function returns the number of seconds that passed since some 
// reference point in time
int calcTime()
{
    NumOfSecondsFromStartingPoint = 17;
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

int main()
{
    printf("Hello World");

    return 0;
}
