#include <stdio.h>
#include <stdbool.h>

int set_bit(int val, int pos, bool shouldSet)
{
    int mask = 1;
    mask = mask << pos;
    printf("after initially setting the mask it is:%d\n", mask);

    if (true == shouldSet)
    {
        return val | mask;
    }
    
    mask = ~mask;
    printf("after converting the initial setting, the mask is:%d\n", mask);
    return val & mask;
}

int testTheSetBitFunction()
{
    const char funcName [] = "testTheSetBitFunction - ";
    printf("%s start\n", funcName);
    int val1 = 0;
    int posToSet = 1;
    bool shouldSet = true;
    int retVal = set_bit(val1, posToSet, shouldSet);
    int expectedRes = 2;
    if (expectedRes != retVal)
    {
        printf("%s did not return correct value\n", funcName);
        return 1;
    }
    
    val1 = 0;
    posToSet = 0;
    shouldSet = true;
    retVal = set_bit(val1, posToSet, shouldSet);
    expectedRes = 1;
    if (expectedRes != retVal)
    {
        printf("%s did not return correct value\n", funcName);
        return 1;
    }
    
    printf("%s all unit tests PASSED!\n", funcName);
    return 0;
}

int main()
{
    printf("main start\n");
    return testTheSetBitFunction();
}
