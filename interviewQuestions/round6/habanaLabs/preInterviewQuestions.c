#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>

#define LEN 2

void multipleTwoMatrix(const int mat1[][LEN], const int mat2[][LEN], int resMat[][LEN])
{
    const char funcName [] = "multipleTwoMatrix - ";
    printf("%s got matrix1 is at address:%p, matrix2 at address:%p with size(NxN):%u\n", funcName, mat1, mat2, LEN);

    for (int row = 0; row < LEN; ++row)
    {
        for (int col = 0; col < LEN; ++col)
        {
            resMat[row][col] = 0;
            for (int k = 0; k < LEN; ++k)
            {
                resMat[row][col] += mat1[row][k] * mat2[k][col];
            }
        }
    }
}

void printTwoDimMat(const int* mat, const size_t numRows, const size_t numCols)
{
    for (uint8_t row = 0; row < numRows; ++row)
    {
        for (uint8_t col = 0; col < numCols; ++col)
        {
            
            printf("%d\t", *(mat + row* numCols + col));
        }
        
        printf("\n");
    }
}

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
/*
* The answer:
* - Academic: 
* Minimum value is the number of times each thread increments the global variable.
* For example, if each thread increments the global variable by 20, then the minimum value is 20:
* thread1 reads 0 
* thread2 reads 0
* thread1 writes 1
* thread2 writes 1
* ....
* Maximum value is when the threads work "propely" by magic (as if the global variable is indeed synchronized) and it is
* the number of threads that increment the global variable multiple the number of increments each thread does.
* Also note that the number threads does NOT effect the MINIMUM value in the "wrost" case scenarion.
*    relevant link: https://stackoverflow.com/questions/47988994/final-value-of-a-global-variable-which-is-being-incremented-via-two-threads
* - Practical answer: It is, by definition, due to the fact that it has an inherent race condition, a case of undefined
* behaviour. 
void twoThreadsGlobalVar()
{
    const char funcName [] = "twoThreadsGlobalVar - ";
    const uint8_t numOfThreads = 2;
    printf("%s about to initiate %u threads that each will increment the global variable which is initially:%d\n", funcName, numOfThreads, globalInt);
    
    pid_t threads [2] = {0};
    printf("%s eventually the global variable has the value of:%d\n", funcName, globalInt);
}

/*
* Given n=2: {1,1} {2} --> return 2
* Given n=3: {1,1,1}, {1,2}, {2,1} --> return int3 
* Given n=4: {1,1,1,1}, {1,1,2}, {1,2,1}, {2,1,1}, {2,2} --> return 5 
* Given n=5: {1,1,1,1,1}, {1,1,1,2}, {1,1,2,1}, {1,2,1,1}, {2,1,1,1}, {1,2,2}, {2,1,2}, {2,2,1} --> return 5 
*
*
*/
size_t getNumOfOptionsToClimb(size_t n)
{
    if (1 == n)
    {
        return 1;
    }
    
    if (2 == n)
    {
        return 2;
    }
    
    return getNumOfOptionsToClimb(n - 1) + getNumOfOptionsToClimb(n - 2);
}

int climbStairs(const size_t numOfStairsToClimb)
{
    uint32_t* dp = (uint32_t *)malloc(sizeof(uint32_t) * (numOfStairsToClimb + 1));
    dp[0] = 1;
    dp[1] = 1;
    for (size_t i = 2; i <= numOfStairsToClimb; ++i)
    {
        dp[i] = dp[i - 1] + dp[i - 2];
    }
    
    uint32_t retVal = dp[numOfStairsToClimb];
    free(dp);
    return retVal;
}

void hilazonStairs()
{
    const char funcName [] = "hilazonStairs - ";
    size_t numOfStairsToClimb = 5;
    printf("%s got number of stairs to climb:%lu\n", funcName, numOfStairsToClimb);
    
    // recursion approach
    // ------------------
    // let's break the problem to a "smaller" one each time, so upon having N 
    // stairs to climb, climb one OR two and then calculate the number 
    size_t numOfOptionsToClimbStairs = getNumOfOptionsToClimb(numOfStairsToClimb);
    printf("%s the recursion function returned:%lu for %lu staris to climb\n", funcName, numOfOptionsToClimbStairs, numOfStairsToClimb);
    
    // loop approach:
    // --------------
    numOfOptionsToClimbStairs = climbStairs(numOfStairsToClimb);
    printf("%s the dynamic programming (loop) approach function returned:%lu for %lu staris to climb\n", funcName, numOfOptionsToClimbStairs, numOfStairsToClimb);
}

int maxProfit(int* prices, int pricesSize)
{
    const char funcName [] = "maxProfit - ";
    int ans = 0;
    for (int i = 0; i < pricesSize - 1; ++i)
    {
        if (prices[i] < prices[i + 1])
        {
            ans += prices[i + 1] - prices[i];
        }
    }

    
    printf("%s for the array of prices\n", funcName);
    for (int i = 0; i < pricesSize; ++i)
    {
        printf("%d\t", prices[i]);
    }
    
    printf("\n%s about to return the answer:%d\n", funcName, ans);
    return ans; 
}

void buyLowSellHigh()
{
    int prices [] = { 7, 1, 5, 3, 6, 4 };
    int n = sizeof(prices)/sizeof(prices[0]);
    int ans = maxProfit(prices, n);
}

void multipleTwoMatrixExample()
{
    const char funcName [] = "multipleTwoMatrixExample - ";
    int mat1[][LEN] = {{1,1},
                      {1,1}};
    int mat2[][LEN] = {{1,2},
                      {3,4}};
    int resMat [][LEN] = {{0, 0},
                         {0, 0}};
    printf("%s about to mutiple mat1 with mat2\n", funcName);
    printf("%s mat1 is:\n", funcName);
    printTwoDimMat(&mat1[0][0], LEN, LEN);
    printf("%s mat2 is:\n", funcName);
    printTwoDimMat(mat2[0], LEN, LEN);
    multipleTwoMatrix(mat1, mat2, resMat);
    printf("%s the resulting matrix is:\n", funcName);
    printTwoDimMat(resMat[0], LEN, LEN);
}

void multipleThreeDimensionalArrayWithThreeDimensionalVector()
{
    const char funcName [] = "multipleThreeDimensionalArrayWithThreeDimensionalVector - ";
    #define DIM1 2
    
    int threeDimArr[][3][4] = 
    { 
        { {0,1,2,3}, {4,5,6,7}, {8,9,10,11} },
        { {12,13,14,15}, {16,17,18,19}, {20,21,22,23} }
    };
    
    printf("%s about to display the THREE dimensional array as a collection of two dimensional arrays\n", funcName);
    for (uint8_t i = 0; i < DIM1; ++ i)
    {
        printTwoDimMat(threeDimArr[i], 3 ,4);
        printf("\n\n");
    }
}

// =======================================================================================================
// =======================================================================================================
// main program 
// =======================================================================================================
// =======================================================================================================
int main(int argc, char** argv)
{
    printf("main - start\n");

    // 1)
    //char strWithSeveralWords [] = "ab cd";
    //reverseStringWithSeveralWords(strWithSeveralWords);
    //printf("main - after reversing the entire word, it is now:%s\n", strWithSeveralWords);

    // 2)
    //myAlignedMallocAndFreeUsageExample();
    
    // 5)
    //buyLowSellHigh();
    
    // 6)
    //multipleTwoMatrixExample();
    
    // 7) 
    multipleThreeDimensionalArrayWithThreeDimensionalVector();
    
    printf("main - end\n");
    return 0;
}
