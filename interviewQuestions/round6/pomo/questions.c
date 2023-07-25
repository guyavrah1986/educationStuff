#include <stdio.h>

int myMemcpy(void* dst, const void* src, size_t len)
{
    if (NULL == dst || NULL == src)
    {
        printf("myMemcpy - NULL pointer recived\n");
        return -1;
    }
    
    // validations of overlappoing
    char* ldst = (char*)dst;
    char* lsrc = (char*)src;
    printf("src points to:%p | dest points to:%p\n", src, dst);
    
    if (ldst < lsrc)
    {
        printf("myMemcpy - dst is lower than src\n");
        if ((ldst + (len * sizeof(char)) >= lsrc))
        {
            printf("myMemcpy - dst is lower than src BUT not enough, do not copy\n");
            return -1;
        }

    }
    
    if (lsrc < ldst)
    {
        printf("myMemcpy - src is lower than dst\n");
        if (lsrc + (len * sizeof(char)) >= ldst)
        {
            printf("myMemcpy - src is lower than dst but not far enough\n");
            return -1;            
        }

    }
    
    
    printf("myMemcpy - copying was successfull, returning:%ld\n", len);
    return len;
}

int main()
{
    printf("main - start\n");
    char shareBuff [12] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l'};
    char* src = &shareBuff[3];
    char* dst = shareBuff;
    size_t len = 4;
    int res = myMemcpy((void*)dst, (void*)src, len);
    printf("main - FIRST attempt returned:%d\n", res);
    
    src = shareBuff;
    dst = &shareBuff[3];
    res = myMemcpy((void*)dst, (void*)src, len);
    printf("main - SECOND attempt returned:%d\n", res);
    printf("main - end\n");
    return 0;
}

