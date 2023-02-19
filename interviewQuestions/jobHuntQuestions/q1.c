#include <stdio.h>
#include <stdbool.h>

void reorderArr(int* arr, const size_t arrLen)
{
    size_t start = 0;
    size_t end = arrLen - 1;
    while (start < end)
    {
        if (1 == arr[start])
        {
            ++start;
            continue;
        }
        else if (2 == arr[end])
        {
            --end;
            continue;
        }
        else
        {
            arr[start] = 1;
            arr[end] = 2;
            ++start;
            --end;
        }
    }
}

bool testFunc()
{
    int arr1 [] = {1,2,1,2,1,2,1};
    int expectedArr1 [] = {1,1,1,1,2,2,2};
    reorderArr(arr1, sizeof(arr1)/sizeof(int));
    int arr2 [] = {1,2,1,3,3,2,3,1,2,1};
    int expectedArr2 [] = {1,1,1,1,2,2,2,3,3,3};
    for (size_t i = 0; i < sizeof(arr1)/sizeof(int); ++i)
    {
        if (arr1[i] != expectedArr1[i])
        {
            return false;
        }
    }
    
    return true;
}

int main()
{
    printf("main - start\n");
    if (true == testFunc())
    {
        printf("main - PASSED\n");
    }
    else
    {
        printf("main - FAILED\n");
    }
    
    printf("main - end\n");
    return 0;
}

