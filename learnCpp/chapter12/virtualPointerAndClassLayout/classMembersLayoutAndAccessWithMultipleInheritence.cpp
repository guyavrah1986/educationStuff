// ================================================================================================================================================================================================
// ================================================================================================================================================================================================
// NOTE: Compile the program with the following line:
// g++ -g -O0 -c -fverbose-asm -Wa,-adhln classMembersLayoutAndAccessWithMultipleInheritence.cpp > test.lst
//
/*

  82:classMembersLayoutAndAccessWithMultipleInheritence.cpp **** 	F* pf = &f1;
 557 002f 488D45DC 		leaq	-36(%rbp), %rax	#, tmp85
 558 0033 488945D0 		movq	%rax, -48(%rbp)	# tmp85, pf
  84:classMembersLayoutAndAccessWithMultipleInheritence.cpp **** 	int base1Member = pf->c; 
 561 0037 488B45D0 		movq	-48(%rbp), %rax	# pf, tmp86
 562 003b 8B00     		movl	(%rax), %eax	# pf_3->D.44380.c, tmp87
 563 003d 8945C4   		movl	%eax, -60(%rbp)	# tmp87, base1Member
  85:classMembersLayoutAndAccessWithMultipleInheritence.cpp **** 	int base2Member = pf->e;
 566 0040 488B45D0 		movq	-48(%rbp), %rax	# pf, tmp88
 567 0044 8B4004   		movl	4(%rax), %eax	# pf_3->D.44381.e, tmp89
 568 0047 8945C8   		movl	%eax, -56(%rbp)	# tmp89, base2Member
  86:classMembersLayoutAndAccessWithMultipleInheritence.cpp **** 	int derivedMember = pf->f;
 571 004a 488B45D0 		movq	-48(%rbp), %rax	# pf, tmp90
 572 004e 8B4008   		movl	8(%rax), %eax	# pf_3->f, tmp91
 573 0051 8945CC   		movl	%eax, -52(%rbp)	# tmp91, derivedMember
*/
// NOTES:
// 1) Similarly to single inheritence, also with multiple inheritence, when accessing class members via the derived object, all the offest are constants and known in advance, 
//
// ================================================================================================================================================================================================
// ================================================================================================================================================================================================
#include<iostream>

using namespace std;

class C
{
public:
	C() : c(17)
	{
		cout << "C::C - setting c to:" << c << " this is at:" << this << " m_base1 is at:" << &c << endl;	
	}

	~C()
	{
		cout << "C::~C" << endl;
	}
	
	void func1()
	{
		cout << "C::func1 - c is:" << c << endl;
	}
	
	int c;
};

class E
{
public:
	E() : e(15)
	{
		cout << "E::E - setting m_base2 to:" << e << " this is at:" << this << " e is at:" << &e << endl;
	}

	~E()
	{
		cout << "E::~E" << endl;
	}

	void func2()
	{
		cout << "E::func2 - e is:" << e << endl;
	}
	
	int e;
};

class F : public C , public E
{
public:
	F() : f(12)
	{
		cout << "F::F - setting f to:" << f << " this is at:" << this << " f is at:" << &f<< endl;
	}

	~F()
	{
		cout << "F::~F" << endl;
	}

	void func1()
	{
		cout << "F::func1 - f is:" << f << endl;
	}
	
	int f;
};

int main(int argc, char** argv)
{
	F f1;
	F* pf = &f1;

	int base1Member = pf->c;    // *(pf + dFC + dCc1); // *(pf + dFc1); 
	int base2Member = pf->e;    // *(pf + dFE + dEe1); // *(pf + dFe1); 
	int derivedMember = pf->f;  // *(pf + dFf1); 
	return 0;
}

