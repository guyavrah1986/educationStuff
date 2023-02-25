// ================================================================================================================================================================================================
// ================================================================================================================================================================================================
// NOTE: Compile the program with the following line:
// g++ -g -O0 -c -fverbose-asm -Wa,-adhln classMembersLayoutAndAccessWithSingleInheritence.cpp > test.lst
//
//
/*
 393              	# classMembersLayoutAndAccessWithSingleInheritence.cpp:80: 	Derived* dp = &d1;
  80:classMembersLayoutAndAccessWithSingleInheritence.cpp **** 	Derived* dp = &d1;
 394              		.loc 1 80 11
 395 002f 488D45E0 		leaq	-32(%rbp), %rax	#, tmp85
 396 0033 488945D8 		movq	%rax, -40(%rbp)	# tmp85, dp
 397              	# classMembersLayoutAndAccessWithSingleInheritence.cpp:81: 	int baseMember = dp->m_base1;
  81:classMembersLayoutAndAccessWithSingleInheritence.cpp **** 	int baseMember = dp->m_base1;
 398              		.loc 1 81 6
 399 0037 488B45D8 		movq	-40(%rbp), %rax	# dp, tmp86
 400 003b 8B00     		movl	(%rax), %eax	# dp_3->D.44339.m_base1, tmp87
 401 003d 8945D0   		movl	%eax, -48(%rbp)	# tmp87, baseMember
 402              	# classMembersLayoutAndAccessWithSingleInheritence.cpp:82: 	int sderivedMember = dp->m_derived;
  82:classMembersLayoutAndAccessWithSingleInheritence.cpp **** 	int sderivedMember = dp->m_derived;
 403              		.loc 1 82 6
 404 0040 488B45D8 		movq	-40(%rbp), %rax	# dp, tmp88
 405 0044 8B4004   		movl	4(%rax), %eax	# dp_3->m_derived, tmp89
 406 0047 8945D4   		movl	%eax, -44(%rbp)	# tmp89, sderivedMember
*/
//
// NOTES:
// 1) Due to the fact that in single inheritence the pointers of type Derived & Base points to the SAME location, which is the first member of Derived, which is the first memeber of the sole 
//    Base class -- there is no need in "special" offset adjusments here, i.e. m_derived is simply 4 bytes (sizeof(int)) "away" from the m_base member.
//
// ================================================================================================================================================================================================
// ================================================================================================================================================================================================
#include<iostream>

using namespace std;

class Base1
{
public:
	Base1() : m_base1(17)
	{
		cout << "Base1::Base1 - setting m_base1 to:" << m_base1 << " this is at:" << this << " m_base1 is at:" << &m_base1 << endl;	
	}

	~Base1()
	{
		cout << "Base1::~Base1" << endl;
	}
	
	void func1()
	{
		cout << "Base1::func1 - m_base1 is:" << m_base1 << endl;
	}
	
	int m_base1;
};

class Derived : public Base1
{
public:
	Derived() : m_derived(12)
	{
		cout << "Derived::Derived - setting m_derived to:" << m_derived << " this is at:" << this << " m_derived is at:" << &m_derived<< endl;
	}

	~Derived()
	{
		cout << "Derived::~Derived" << endl;
	}

	void func1()
	{
		cout << "Derived::func1 - m_derived is:" << m_derived << endl;
	}
	
	int m_derived;
};

int main(int argc, char** argv)
{
	Derived d1;
	Derived* dp = &d1;
	int baseMember = dp->m_base1;  		// dp->m_base1; // *(dp + dDC + dCm_base1); {dDC == 0} }// *(dp + dCm_base1); 
	int sderivedMember = dp->m_derived;	// dp->m_derived; // *(dp + dDm_derived); 

	return 0;
}


