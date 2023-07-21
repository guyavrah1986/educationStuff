#include <stdio.h>

long myMemcpy(void* dst, const void* src, size_t len)
{
    if (NULL == dst || NULL == src)
    {
        printf("myMemcpy - dst and/or src are NULL\n");
        return -1;
    }
    
    if (0 == len)
    {
        printf("myMemcpy - len is zero, nothing to copy, finish\n");
        return 0;
    }
    
    if ((char*)dst + len < (char*)src)
    {
        printf("myMemcy - the last byte of dst is BEFORE the first byte of src - copying\n");
    }
    else if ((char*)src + len < (char*)dst)
    {
        printf("myMemcy - the first byte of dst is AFTER the last byte of src - copying\n");
    }
    else
    {
        printf("myMemcpy - addresses of src and dst collide, NOT copying\n");
        return -1;
    }
}

int main()
{
    printf("main - start\n");
    char arr [10] = {0};
    size_t len = 0;
    long retCode = myMemcpy((void*)(&arr[2]), (const void*)(&arr[0]), len);
    if (0 != retCode)
    {
        printf("main - expected return value of:%ld but did not get it\n", retCode);
    }
    
    len = 4;
    retCode = myMemcpy((void*)(&arr[2]), (const void*)(&arr[0]), len);
    if (-1 != retCode)
    {
        printf("main - expected return value of:%ld but did not get it\n", retCode);
    }
    
    retCode = myMemcpy((void*)(&arr[2]), (const void*)(&arr[0]), len);
    if (-1 != retCode)
    {
        printf("main - expected return value of:%ld but did not get it\n", retCode);
    }
    printf("main - end\n");
    return 0;
}
