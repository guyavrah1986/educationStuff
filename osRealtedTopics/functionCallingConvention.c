// ==============================================================================================================================================
// ==============================================================================================================================================
//
//
//
//
// ==============================================================================================================================================
// ==============================================================================================================================================
#include <stdio.h>

struct MyStruct
{
	double d;
};

int foo(int a, short b, struct MyStruct ms)
{
	printf("foo - a is at address:%p, b is at address:%p, and ms is at address:%p\n", &a, &b, &ms);
	return 1;
}

int main(int argc, char** argv)
{
	printf("main - start\n");
	int x = 12;
	short y = 15;
	struct MyStruct ms = {3.4};
	printf("main - allocated struct MyStruct on the stack of the main program at address:%p, int x at address:%p and short y at address:%p\n", &ms, &x, &y);
	printf("main - calling foo\n");
	int ret = foo(x, y, ms);
	printf("main - end\n");
	return 0;
}
