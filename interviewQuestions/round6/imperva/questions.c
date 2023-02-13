// ===================================================================================================================
// ===================================================================================================================
// 1) Implement your own memcpy function with the below signature.
//
//
// ===================================================================================================================
// ===================================================================================================================

#include <stdio.h>

// 1)
void myMemcpy(const void* src, void* dst, const size_t len)
{
	printf("address of src:%p\n",src);	
	printf("address of dst:%p\n",dst);	
    if ( (((char*)(dst) - (char*)(src)) < len) ||  (((char*)(src) - (char*)(dst)) < len))
    {
        printf("myMemcpy - src and dst overlapp!\n");
        return;
    }
    
    printf("myMemcpy - src and dst do NOT overlapp!\n");
    size_t i = 0;
    
    while (i < len)
    {
        *(char*)(dst + i) = *(char*)(src + i);
        ++i;
    }
}

int main()
{
    printf("main - start\n");
    const char srcStr [] = "abcd";
    char dstStr [] = "efgh";
    size_t len = 4;
    printf("main - BEFORE calling myMemcpy for the first time, srcStr points to:%s and dstStr pints to:%s\n", srcStr, dstStr);
    myMemcpy(srcStr, dstStr, len);
    printf("main - AFTER calling myMemcpy for the first time, srcStr points to:%s and dstStr pints to:%s\n", srcStr, dstStr);
    myMemcpy(srcStr, &srcStr[2], len);
    printf("main - end\n");
    return 0;
}
