#include <stdio.h>
#include <stdint.h>

int main()
{
    const char funcName [] = "main - "; 
    printf("%s start\n", funcName);
    uint16_t myShort = 0x0001;
    unsigned char* tmp = (unsigned char*)&myShort;
    
    printf("%s myShort value in hex is:0x%x, its address is:%p\n", funcName, myShort, tmp);
    printf("%s myShort[0] value in hex is:0x%x, its address is:%p\n", funcName, *tmp, tmp);
    printf("%s myShort[1] value in hex is:0x%x, its address is:%p\n", funcName, *(++tmp), tmp);

    myShort = 0x9876;
    tmp = (unsigned char*)&myShort;
    printf("%s myShort value in hex is:0x%x, its address is:%p\n", funcName, myShort, tmp);
    printf("%s myShort[0] value in hex is:0x%x, its address is:%p\n", funcName, *tmp, tmp);
    printf("%s myShort[1] value in hex is:0x%x, its address is:%p\n", funcName, *(++tmp), tmp);
    printf("%s end\n", funcName);
    return 0;
}
