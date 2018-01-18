#include <stdio.h>

struct myStruct
{
	int i;
	double d;
	char arr[4];
	struct myStruct* next;
};

void displayStructMembers(const struct myStruct* s)
{
	printf("displayStructMembers - dispalying struct members of struct at address:%p \n", s);
	char* tmp = (char*)s;
	int* pInt = (int*)tmp;
	printf("s.i:<%p, %d> \n",pInt, *pInt);
	tmp += sizeof(int*);
	double* pD = (double*)tmp;
	printf("s.d:<%p, %f> \n", pD, *pD);
	tmp += sizeof(double);
	printf("s.arr:<%p, %s> \n", tmp, tmp);
}

void structExample()
{
	struct myStruct s {3, 6.7, "abc", NULL};
	printf("structExample - size of myStruct is:%d \n",sizeof(myStruct));
	printf("structExample - s members are - s.i:%d, s.d:%f, s.arr:%s, s.next:%p \n", s.i, s.d, s.arr, s.next);

	printf("structExample - the address of s is:%p , while also the address of the first member s.i is:%p \n", &s, &(s.i));
	printf("structExample - the address of s.d is:%p , s.d is:%p \n", &(s.d), s.d);
	displayStructMembers(&s);
}
