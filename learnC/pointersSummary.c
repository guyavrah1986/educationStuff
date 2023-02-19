// ============================================================================================================
// Pointers:
// ---------
// 1) When pointing on some variable in memory, the ACTUAL amount of memory that is being pointed is acording
//    to the pointer's type and not the pointee. 
// 2) Same goes here, only this time, sPtr points to TWO bytes (short). Due to the fact this this example was
//    tested on littele endian, the value below is the value after this "modification".
// ============================================================================================================

#include <stdio.h>
#include <stdlib.h>

char* globalStr = "globalStr";

void checkBigOrLittleEndian()
{

	size_t sizeOfInt = sizeof(short);
	short x;	
	printf("checkBigOrLittleEndian - size of short is:%lu bytes \n",sizeOfInt);

	x = 0x0102;

	// When poiting on any variable with a char* we can access it for a single byte.
	// The byte it points to will be the first memory location (address) where x is stored while the additional bytes used to store it will follow.
	// Depending on the value stored there - we can determine whether it is big or little
	// endian.
	char* ptr = (char*)&x;	
	if(*ptr == 0x01)
	{
		printf("We run on Big endian machine \n");
		//0102
	}
	else if(*ptr == 0x02)
	{
		printf("We run on Little endian machine \n");
		//0201
	}

	printf("Displaying the represntation of x (short) in memory \n");
	for (size_t i = 0; i < sizeof(short); ++i)
	{
		printf("address:%p, has value of:%x \n",ptr + i, *(ptr + i));	
	}
}

void funcWithConstPointerArg(const char* str)
{
	printf("funcWithConstPointerArg - got str that points to:%s\n", str);
	const char* origStr = str;
	str = globalStr;
	printf("funcWithConstPointerArg - after setting str= globalStr, str points to:%s\n", str);
	printf("funcWithConstPointerArg - after setting str= globalStr, origStr points to:%s\n", origStr);
	// str[0] = "d"; --> won't work, one can NOT change the value that are being pointed via const pointer
}

void funcWithPointerToConstArg(char* const str)
{
	printf("funcWithPointerToConstArg - got str that points to:%s\n", str);
	//char* origStr = str;
	char* otherStr = "def";
	printf("funcWithConstPointerArg - otherStr is:%s\n", otherStr);
	//str = otherStr; --> this is NOT allowed
	str[0] = 'd'; 
	printf("funcWithConstPointerArg - after setting str[0]='d'str points to:%s\n", str);
}

void constPointerIllustration()
{
	printf("constPointerIllustration - start\n");
	char str[] = "abc";
	printf("constPointerIllustration - str points to:%s\n", str);
	funcWithConstPointerArg(str);
	funcWithPointerToConstArg(str);
	printf("constPointerIllustration - end\n");
}

void accessingViaCharPointer()
{

	printf("accessingViaCharPointer - start\n");
	int x = 0x01020304;
	char* ptr = (char*)&x;
	#pragma GCC diagnostic push
	#pragma GCC diagnostic ignored "-Woverflow"
		*ptr = 0x05060708;
		/* 1)  */
	#pragma GCC diagnostic pop


	// due to the fact that char* points to a single byte
	printf("after setting x via char*, it value is:\n");
	for (size_t i = 0; i < sizeof(int); ++i)
	{
		printf("address:%p, has value of:%x \n",ptr + i, *(ptr + i));	
	}
	// at this stage the value of x is (assuming littele endian architecture)
	// 0x08030201

	short* sPtr = (short*)&x;
	sPtr++;
	#pragma GCC diagnostic push
	#pragma GCC diagnostic ignored "-Woverflow"
		*sPtr = 0x05060708;         /* 2) */
	#pragma GCC diagnostic pop
	
	printf("after setting x via short* which was moved incremented by 1, it value is:\n");
	for (size_t i = 0; i < sizeof(int); ++i)
	{
		printf("address:%p, has value of:%x \n",ptr + i, *(ptr + i));	
	}

	// at this stage x has the value of:
	// 0x08030807 --> on littele endian architecture. 
	printf("accessingViaCharPointer - end\n");
}

int globalInt = 17;
int* ptrToGlobalInt = &globalInt;

void changeValuePointedByPointer(int* pi1, int** pi2)
{
	printf("changeValuePointedByPointer - start\n");
	printf("changeValuePointedByPointer - got *pi1 that points to:%d and **pi2 that points to:%d\n", *pi1, **pi2);
	printf("changeValuePointedByPointer - the address of globalInt in:%p\n", &globalInt);
	*pi1 = globalInt;
	**pi2 = globalInt;
	printf("changeValuePointedByPointer - end\n");
}

void changeAddressPointedByPointer(int* pi1, int** pi2)
{
	printf("changeAddressPointedByPointer - start\n");
	printf("changeAddressPointedByPointer - got *pi1 that points to:%d and **pi2 that points to:%d\n", *pi1, **pi2);
	printf("changeAddressPointedByPointer - the address of globalInt in:%p\n", &globalInt);
	pi1 = &globalInt;
	*pi2 = &globalInt;
	printf("changeAddressPointedByPointer - end\n");
}

void changeValuePointedByPointerUsage()
{
	printf("changeValuePointedByPointerUsage - start\n");
	int i1 = 12;
	int i2 = 15;
	int* pi1 = &i1;
	int* pi2 = &i2;
	printf("changeValuePointedByPointerUsage - before calling the changeValuePointedByPointer function, i1 address is:%p and its value is:%d\n", &i1, i1);
	printf("changeValuePointedByPointerUsage - before calling the changeValuePointedByPointer function, i2 address is:%p and its value is:%d\n", &i2, i2);
	changeValuePointedByPointer(&i1, &(pi2));
	printf("changeValuePointedByPointerUsage - AFTER calling the changeValuePointedByPointer function, i1 address is:%p and its value is:%d\n", &i1, i1);
	printf("changeValuePointedByPointerUsage - AFTER calling the changeValuePointedByPointer function, i2 address is:%p and its value is:%d\n", &i2, i2);

	i1 = 12;
	i2 = 15;
	pi1 = &i1;
	pi2 = &i2;
	printf("changeValuePointedByPointerUsage - before calling the changeAddressPointedByPointer function, pi1 address is:%p and its value is:%d\n", pi1, *pi1);
	printf("changeValuePointedByPointerUsage - before calling the changeAddressPointedByPointer function, pi2 address is:%p and its value is:%d\n", pi2, *pi2);
	changeAddressPointedByPointer(pi1, &pi2);
printf("changeValuePointedByPointerUsage - AFTER calling the changeAddressPointedByPointer function, pi1 address is:%p and its value is:%d\n", pi1, *pi1);
	printf("changeValuePointedByPointerUsage - AFTER calling the changeAddressPointedByPointer function, pi2 address is:%p and its value is:%d\n", pi2, *pi2);
	printf("changeValuePointedByPointerUsage - end\n");
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
	printf("lateBindingExample - res is:%d\n", res);	
	printf("lateBindingExample - end");
}

int main(int argc, char** argv)
{
	printf("main - start\n");
	checkBigOrLittleEndian();
	constPointerIllustration();
	accessingViaCharPointer();
	changeValuePointedByPointerUsage();
	printf("main - end\n");
	return 0;
}

