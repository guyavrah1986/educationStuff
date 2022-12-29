#include <stdio.h>

void orderArr(int* arr, size_t len, int valBegin, int valEnd)
{
    int* p1 = arr;
    int* p2 = &(arr[len - 1]);
    while(p1 <= p2)
    {
        if(*p1 == valBegin)
        {
            p1++;
        }
        else if(*p2 == valEnd)
        {
            p2--;
        }
        else
        {
            *p1 = valBegin;
            *p2 = valEnd;
            p1++;
            p2--;
        }
    }
    
}

int compareArrays(const int* arr1, const int* arr2, size_t len)
{
    size_t i = 0;
    while (i < len)
    {
        if (arr1[i] != arr2[i])
        {
            return 1;
        }
        
        ++i;
    }
    
    return 0;
}

int test1()
{
    int arr[] = {4,7,4,7,7,4,7,4};
    int retArr[] = {4,4,4,4,7,7,7,7};
    orderArr(arr, 8, 4, 7);
    if (0 == (compareArrays(arr, retArr, 8)))
    {
        return 1;
    }

    return 0;
}

int main()
{
    printf("main - start\n");
    if (1 == test1())
    {
        printf("test passed\n");
    }
    else
    {
        printf("test failed\n");
    }
    
    printf("main - end\n");
    return 0;
}
