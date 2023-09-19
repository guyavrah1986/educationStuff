#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>


/*
Currently the assumption is that every word is separated from the next one by exactly
one ' ' (space character). If later another assumption is made, change the 
implementation of this function.
*/
char* forwardStringPointerToNextWord(char* origStr)
{
    while (' ' == *origStr)
    {
        ++origStr;
    }
    
    return origStr;
}

/*
This function gets a pointer to a string that might contain several words (i.e.
 - sub strings within it that are separate by space character). Its role is to
extract the "current word", i.e. - iterating over the "big" string till it hits
either space (' ') or the NULL terminator that basically indicates that this is 
the last word in the string.
The function returns the length of the current word.
*/
size_t extractWordFromString(char* str)
{
    const char funcName [] = "extractWordFromString - ";
    printf("%s got the string:%s\n", funcName, str);
    size_t currWordLen = 0;
    while (*str != ' ' && *str != '\0')
    {
        ++str;
        ++currWordLen;
    }
    
    return currWordLen;
}

void reverseWord(char* str, size_t strLen)
{
    const char funcName [] = "reverseWord - ";
    //size_t strLen = strlen(src);
    printf("%s got the word(string):%s, at address:%p, with size:%lu\n", funcName, str, (void*)str, strLen);
    for (uint8_t startIndex = 0, endIndex = strLen - 1; startIndex < endIndex; ++startIndex, --endIndex)
    {
        char tmp = str[startIndex];
        printf("%s startIndex:%u, endIndex:%u, tmp is:%c\n", funcName, startIndex, endIndex, tmp);
        str[startIndex] = str[endIndex];
        str[endIndex] = tmp;
    }
    
    printf("%s finally the string is now:%s\n", funcName, str);
}

void reverseStringWithSeveralWords(char* origStr)
{
    const char funcName [] = "reverseStringWithSeveralWords - ";
    size_t strLen = 0;
    char* tmp = origStr;
    while ((*tmp) != '\0')
    {
        ++strLen;
        ++tmp;
    }
    
    printf("%s the original string is:%s with length of:%lu characters\n", funcName, origStr, strLen);
    
    // first reverse the entire string as a whole
    // ab cd --> dc ba
    reverseWord(origStr, strLen);
    printf("%s after reversing the entire string as a whole it is:%s\n", funcName, origStr);
    while (*origStr != '\0')
    {
        size_t currWordLen = extractWordFromString(origStr);
        reverseWord(origStr, currWordLen);
        origStr += currWordLen;
        
        // move on to the next word or to the end of the main string (the 
        // terminating NULL character)
        origStr = forwardStringPointerToNextWord(origStr);    
    }
}



/*Write an aligned malloc & free function. Which takes number of bytes and aligned byte (which is always power of 2)

Ex. align_malloc (1000,128);

it will return memory address which is a multiple of 128 and have the size of 1000.
(at least this is how it will appear to the user)
aligned_free(); 

it will free memory allocated by align_malloc.*/
void* align_malloc(size_t numBytesToAllocate, const uint8_t alignedFactor)
{
    const char funcName [] = "align_malloc - ";
    printf("%s requested:%lu bytes to allocated which will be in an address which is a multiple of:%u\n", funcName, numBytesToAllocate, alignedFactor);
    // Assumptions: 
    // 1. The number of "offset bytes" from the actual starting location given
    // by the original malloc will always fit into one byte
    // 2. numBytesToAllocate + alignedFactor --> can fit into size_t
    // 3. numBytesToAllocate % alignedFactor --> can fit into uint8_t

    uint8_t* p = (uint8_t*)malloc(numBytesToAllocate + alignedFactor);
    printf("%s the ORIGINAL address (that points to the entire capacity of bytes allocated) is:%p (in decimal:%lu)\n", funcName, p, (unsigned long)p);
    uint8_t residue = (unsigned long)p % alignedFactor;
    printf("%s the residue is:%u\n", funcName, residue);
    uint8_t numBytesToMoveForward = alignedFactor - residue;
    p += numBytesToMoveForward - 1;
    *p = numBytesToMoveForward;
    printf("%s placed the value of:%u at address:%p\n", funcName, numBytesToMoveForward, p);
    ++p;
    printf("%s after moving forward:%u bytes, now p points to memory address:%p (in decimal:%lu)\n", funcName, numBytesToMoveForward, p, (unsigned long)p);
    
    return (void*)p;
}

void aligned_free(void* ptrToFree)
{
    const char funcName [] = "aligned_free - ";
    uint8_t* p = (uint8_t*)ptrToFree;
    printf("%s got the ORIGINAL address from the user to free:%p\n", funcName, ptrToFree);
    uint8_t numOfBytesToGoBackwards = *(--p);
    printf("%s the number of bytes extracted that need to traverse backwards is:%u\n", funcName, numOfBytesToGoBackwards);
    p -= numOfBytesToGoBackwards - 1;
    printf("%s the actuall address that is about to be de-allocated is:%p\n", funcName, p);
    free((void *)p);
}

void myAlignedMallocAndFreeUsageExample()
{
    const char funcName [] = "myAlignedMallocAndFreeUsageExample - ";
    printf("%s start\n", funcName);
    uint8_t alignedNum = 4;
    size_t numBytesToAllocate = 11;
    void* ret = align_malloc(numBytesToAllocate, alignedNum);
    printf("%s got the address of:%p\n", funcName, ret);
    printf("%s about to call the free on this pointer\n \n \n", funcName);
    aligned_free(ret);
    printf("%s end\n", funcName);
}

void twoThreadsGlobalVar()
{
    const char funcName [] = "twoThreadsGlobalVar - ";
    const uint8_t numOfThreads = 2;
    printf("%s about to initiate %u threads that each will increment the global variable which is initially:%d\n", funcName, numOfThreads, globalInt);
    
    pid_t threads [2] = {0};
    printf("%s eventually the global variable has the value of:%d\n", funcName, globalInt);
}

int main(int argc, char** argv)
{
    printf("main - start\n");

    // 1)
    char strWithSeveralWords [] = "ab cd";
    reverseStringWithSeveralWords(strWithSeveralWords);
    printf("main - after reversing the entire word, it is now:%s\n", strWithSeveralWords);

    // 2)
    myAlignedMallocAndFreeUsageExample();
    return 0;
}
