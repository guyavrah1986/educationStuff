#pragma once

/*
Question 1 (understanding of C++ memory)
-----------------------------------------
1) Find any errors in the code and discuss.
2) What the difference between s1 and s2 ?


Answers:
-------
1)
	a) When returning s1 like so - we return a variable that is defined within a function --> outside of its scope.
	b) The definition of s2 as it is, defined a "const string" in the text segment, so if we intend to point to it with a char*
       it should be with a const char* in order to preserve its "constness".
    c) When returning from the foo function, upon writing to p[0] we probably will get a error like segmentation fault.

2) s1 is defined within the stack of the foo function.The compiler automatically allocates enough memory for it upon compilation time --> in this
   case 5 bytes.It will be "destroyed" the moment the function foo terminates.
   s2 is defined in the text segment of the process - which is READ ONLY area. Any attempt to try and modify this area will cause a RUN TIME
   error (possibly crash). The lifetime of it is throughout the entire life of the program.

*/

#include <iostream>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
using namespace std;


void segfault_sigaction(int signal, siginfo_t* si, void* arg)
{
    printf("Caught segfault at address %p\n", si->si_addr);
    exit(0);
}

char* foo()
{
	char s1 [] = "abcd";
	char* s2 = "abcd";
	return s1;
}

void invokeFoo()
{
	struct sigaction sa;
	memset(&sa, 0, sizeof(struct sigaction));
	sigemptyset(&sa.sa_mask);
	sa.sa_sigaction = segfault_sigaction;
	sa.sa_flags = SA_SIGINFO;
	sigaction(SIGSEGV, &sa, NULL);

	char* p = foo();
	cout << "invokeFoo - after returning from foo" << endl;
	// ORIGINALLY this was enabled p[0] = 'A';
	cout << "invokeFoo - after setting p[0] = 'A' " << endl;
}

/*
Question 2 (C++ templates).
--------------------------
What lines in the code can't be compiled and how to correct it ?

Answer:
a) can compile
b) can't compile because A<false> is undefined, works like "static_assert".
c) can't compile because test2 is variable, to fix it we must declare: const int test2 = 2;
*/

template<bool b> class A;
template<> class A<true> {};

#define test1 2
int test2 = 2;

void q1()
{
	A<2 == test1> x1; // a)
	//A<1 == test1> x2; // b)
	//A<2 == test2> x3; // c)
}

/*
Question 3 (low-level memory):
Explain what the following function does. In what context such code can be used.
*/
void modify(int& x, int& b)
{
	cout << "modify - b is:" << b << " before doing trick, x is:" << x << endl;
	x &=~(1 << b);
	cout << "modify - after doing trick, x is:" << x << endl;

}

