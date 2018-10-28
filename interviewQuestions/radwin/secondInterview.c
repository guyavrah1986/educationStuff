#include <stdio.h>
#include <stdint.h>

void calle(uint32_t* p)
{
	uint32_t tmp = 9;
	printf("calle - tmp is located at address location:%p and p is:%p \n", &tmp, p);
}

void caller()
{
	uint32_t tmp1 = 12;
    	printf("caller - address of tmp1:%p \n", &tmp1);
	calle(&tmp1);
}


int main(int argc, char** argv)
{
	caller();
	return 0;
}
