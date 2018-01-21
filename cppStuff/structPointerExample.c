#include <stdio.h>

struct __attribute__((__packed__)) myStruct 
{
	int i;
	char* pc;
	void* vp;
	char arr[4];
};

void initStruct(struct myStruct** ps)
{
	printf("initStruct - got **ps:%p \n", ps);
	struct myStruct* p = (struct myStruct*)(*ps);
	printf("initStruct - after normalizing it to *ps:%p \n", p);
}

void structPointerExample()
{
	printf("structPointerExample - start \n");
	
	struct myStruct s,*p;
	p = &s;
	printf("structPointerExample - sizeof(int):%d ,sizeof(void*):%d,  sizeof(struct myStruct) is:%d \n", sizeof(int), sizeof(void*), sizeof(struct myStruct));
	printf("structPointerExample - sending the address of the address of struct s to the function:%p \n", &p);
	initStruct(&p);

	printf("\n \n structPointerExample - end");
}

void main(int argc, char** argv)
{	
	printf("structPointerExe - start \n \n");

	structPointerExample();

	printf("\n \n structPointerExe - end \n");
	return;
}

