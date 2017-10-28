#include <stdio.h>


void checkBigOrLittleEndian()
{

	size_t sizeOfInt = sizeof(int);
	int x;	
	printf("checkBigOrLittleEndian - size of int is:%lu bytes \n",sizeOfInt);

	x = 0x01020304;

	// now ,when poiting on any variable with a char* we can access it for a single byte.
	// the byte it points to will be the first memory location (address) where x is store.
	// depending on the value stored there - we can determine whether it is big or little
	// endian.
	char* ptr = (char*)&x;	
	if (*ptr == 0x01)
	{
		printf("We run on Big endian machine \n");
		// 01020304
	}
	else if (*ptr == 0x04)
	{
		printf("We run on Little endian machine \n");
		// 04030201
	}

	printf("Displaying the represntation of x (int) in memory \n");
	for (size_t i = 0; i < sizeof(int); ++i)
	{
		printf("address:%p, has value of:%x \n",ptr + i, *(ptr + i));	
	}
}


void accessingViaCharPointer()
{

	int x = 0x01020304;
	char* ptr = (char*)&x;
	*ptr = 0x05060708;

	// due to the fact that char* points to a single byte
	printf("after setting x via char*, it value is:\n");
	for (size_t i = 0; i < sizeof(int); ++i)
	{
		printf("address:%p, has value of:%x \n",ptr + i, *(ptr + i));	
	}
	// at this stage the value of x is:
	// 0x08030201

	short* sPtr = (short*)&x;
	sPtr++;
	*sPtr = 0x05060708;
	printf("after setting x via short* which was moved incremented by 1, it value is:\n");
	for (size_t i = 0; i < sizeof(int); ++i)
	{
		printf("address:%p, has value of:%x \n",ptr + i, *(ptr + i));	
	}

	// at this stage x has the value of:
	// 0x08030807
}

struct MyStructV1
{
	int a;
	int b;
	char c;
};

void updateStruct(struct MyStructV1** ptr)
{
	printf("updateStruct - (*ptr) address is:%p \n",*ptr);
	*ptr = (struct MyStructV1*)malloc(sizeof(struct MyStructV1));
	(*ptr)->a = 17;
	(*ptr)->b = 12;
	(*ptr)->c = 'n';	
}

void structureExample()
{
	printf("structureExample - start\n");
	printf("structureExample - size of MyStructV1 is:%lu \n",sizeof(struct MyStructV1));
	
	struct MyStructPacked
	{
		int a;
		char c;
		int b;
	}__attribute__((__packed__));;

	printf("structureExample - size of MyStructPacked is:%lu \n",sizeof(struct MyStructPacked));
	
	struct MyStructV2
	{
		int a;
		int b;
		char c;
	};

	printf("structureExample - size of MyStructV2 is:%lu \n",sizeof(struct MyStructV2));
	struct MyStructV1* ptr = NULL;
	updateStruct(&ptr);
	printf("structureExample - after setting the struct member using pointer to pointer the struct has the following values:\n");
	printf("ptr->a:%d, ptr->c:%c, ptr->b:%d \n", ptr->a, ptr->c, ptr->b);

	free(ptr);
	printf("structureExample - end\n");
}


int add(int a, int b)
{
	printf("add %d + %d \n",a ,b);
	return a + b;
}

int sub(int a, int b)
{
	printf("substruct %d - %d \n",a ,b);
	return a - b;
}

int mult(int a, int b)
{	
	printf("multiple %d * %d \n",a ,b);
	return a * b;
}

int divide(int a, int b)
{
	printf("divide %d / %d \n",a ,b);
	return a / b;
}

void functionPointerExample()
{
	printf("lateBindingExample - start \n");
	int a, b, input;	
 	printf("Enter your your choise: \n");
	printf("------------------------\n");
	printf("1) add \n");
	printf("2) substruct \n");
	printf("3) multiple \n");
	printf("4) divide \n");	

  	scanf ("%d",&input);

	printf("please enter two positive numbers to perfrom the desired operation on them \n");
	scanf("%d %d" , &a, &b);

	int (*func)(int, int);
	switch (input)
	{
		case 1: func = add;
			break;

		case 2: func = sub;
			break;

		case 3: func = &mult;
			break;

		case 4: func = &divide;
			break;

		default: func = NULL;
			 break;
	}


	if (func == 0)
	{
		printf("invalid input...terminating \n");
		return;
	}

	int res = func(a, b);
	printf("lateBindingExample - end \n");	
}

