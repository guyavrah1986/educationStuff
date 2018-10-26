#include <stdio.h>
#include <stdint.h>

void calle()
{
	uint32_t tmp = 17;
	*((&tmp) + sizeof(uint32_t) * 3) = 12;
}

void caller()
{
	printf("caller - start \n");
	uint32_t p1 = 17;
	calle();
	printf("caller - after calling calle, p1 has the value of:%u \n", p1);
}


int main(int argc, char** argv)
{
	printf("main - start \n \n");
	caller();

	printf("main - end \n \n");
	return 0;
}
