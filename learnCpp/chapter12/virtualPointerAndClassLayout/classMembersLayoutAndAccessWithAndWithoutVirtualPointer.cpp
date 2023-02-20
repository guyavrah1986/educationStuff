// ===================================================================================================================================================================
// ===================================================================================================================================================================
// NOTE: Compile the program with the following line:
// g++ -g -O0 -c -fverbose-asm -Wa,-adhln classMembersLayoutAndAccessWithVirtualPointercpp.cpp > test.lst
//
// 1) When accessing data members without virtual pointer, the only offset that needs to take place is the "constant" offset that is known in advance. For example,
//    when accessing the two members of the classes that have or don't have virtual table and pointer the following takes place:
/*
343              	# virtualTableExplained.cpp:140: 	AwithoutVirtualPointer* pa1 = &a1;
 140:virtualTableExplained.cpp **** 	AwithoutVirtualPointer* pa1 = &a1;
 344              		.loc 1 140 0
 345 002e 488D45C8 		leaq	-56(%rbp), %rax	#, tmp89
 346 0032 488945B8 		movq	%rax, -72(%rbp)	# tmp89, pa1
 347              	# virtualTableExplained.cpp:144: 	int x1 = pa1->m_a;
 144:virtualTableExplained.cpp **** 	int x1 = pa1->m_a;
 348              		.loc 1 144 0
 349 0036 488B45B8 		movq	-72(%rbp), %rax	# pa1, tmp90
 350 003a 8B00     		movl	(%rax), %eax	# pa1_4->m_a, tmp91          // GuyA: pa1 points to the first byte of a1, which is the first byte of its m_a member
 351 003c 8945A8   		movl	%eax, -88(%rbp)	# tmp91, x1
 352              	# virtualTableExplained.cpp:145: 	int y1 = pa1->m_b;
 145:virtualTableExplained.cpp **** 	int y1 = pa1->m_b;
 353              		.loc 1 145 0
 354 003f 488B45B8 		movq	-72(%rbp), %rax	# pa1, tmp92
 355 0043 8B4004   		movl	4(%rax), %eax	# pa1_4->m_b, tmp93 	    // GuyA: pa1 needs to be incremented by sizeof(int) bytes to point to the second member m_b
 356 0046 8945AC   		movl	%eax, -84(%rbp)	# tmp93, y1


 357              	# virtualTableExplained.cpp:147: 	A a2(12,17);

 366              	# virtualTableExplained.cpp:148: 	A* pa2 = &a2;
 148:virtualTableExplained.cpp **** 	A* pa2 = &a2;
 367              		.loc 1 148 0
 368 005f 488D45D0 		leaq	-48(%rbp), %rax	#, tmp95
 369 0063 488945C0 		movq	%rax, -64(%rbp)	# tmp95, pa2
 370              	# virtualTableExplained.cpp:149: 	int x2 = pa2->m_a;
 149:virtualTableExplained.cpp **** 	int x2 = pa2->m_a;
 371              		.loc 1 149 0
 372 0067 488B45C0 		movq	-64(%rbp), %rax	# pa2, tmp96
 373 006b 8B4008   		movl	8(%rax), %eax	# pa2_8->m_a, tmp97       // GuyA: pa2 needs ADJUSTED because it has a "new member" - his virtual pointer so it is incremented by 8 bytes
 374 006e 8945B0   		movl	%eax, -80(%rbp)	# tmp97, x2
 375              	# virtualTableExplained.cpp:150: 	int y2 = pa2->m_b;
 150:virtualTableExplained.cpp **** 	int y2 = pa2->m_b;
 376              		.loc 1 150 0
 377 0071 488B45C0 		movq	-64(%rbp), %rax	# pa2, tmp98
 378 0075 8B400C   		movl	12(%rax), %eax	# pa2_8->m_b, tmp99
 379 0078 8945B4   		movl	%eax, -76(%rbp)	# tmp99, y2
*/
// Class members location upon multiple inheritance:
// -------------------------------------------------
// 1) When a derived class inherites from two (or more) "base" classes, the layout of all her members (hers + the inherited ones) are according to the order of the 
//    inheritence:
//    # Base1's members
//    # Base2's members
//    # Derived's members
// 2) The address of the "this" pointer of the Derived class is the same as the address of the first member of her -- which is the first member of the "first"
//    base class.
//    NOTE: The term "first base class" referes to the actuall first base class name in the dervied class definition. For example, as in the case below where the dervied class is 
//    defined as follows:class Derived : public Base1 , public Base2 --> Base1 is the "first base class" and Base2 is the second.
// 
// ===================================================================================================================================================================
// ===================================================================================================================================================================
#include <iostream>

using namespace std;

class AwithoutVirtualPointer
{
public:	
	AwithoutVirtualPointer(int a, int b) : m_a(a), m_b(b)
	{
		cout << "AwithoutVirtualPointer::AwithoutVirtualPointer" << endl;
	}

	~AwithoutVirtualPointer()
	{
		cout << "AwithoutVirtualPointer::~AwithoutVirtualPointer" << endl;
	}

	int m_a;
	int m_b;
};

class A
{
public:
	A(int a, int b) : m_a(a), m_b(b)
	{
		cout << "A::A - setting m_a to:" << m_a << ", and m_b to:" << m_b << endl;
	}

	virtual ~A()
	{
		cout << "A::~A" << endl;
	}
	
	int m_a;
	int m_b;
};

void accessDataMembersOfBothClassA()
{
	//string funcName = "accessDataMembersOfBothClassA - ";
	//cout << funcName + "start" << endl;
	//cout << funcName + "creating AwithoutVirtualPointer on the stack of the function" << endl;
	AwithoutVirtualPointer a1(12,17);
	AwithoutVirtualPointer* pa1 = &a1;
	//void* addressOfAwithoutVirtualPointer = static_cast<void*>(pa2);
	//cout << funcName + "the address of &a2 is:" << static_cast<void*>(addressOfAwithoutVirtualPointer) << endl;
	//cout << funcName + "the address of the first member of AwithoutVirtualPointer is:" << static_cast<void*>(&pa2->m_a) << endl;
	int x1 = pa1->m_a;
	int y1 = pa1->m_b;

	A a2(12,17);
	A* pa2 = &a2;
	int x2 = pa2->m_a;
	int y2 = pa2->m_b;
	//cout << funcName + "end" << endl;
}

int main(int argc, char** argv)
{
	cout << "main - start " << endl;
	cout << "main - sizeof(int) is:" << sizeof(int) << " bytes " << endl;
	cout << "main - sizeof(void*) is:" << sizeof(void*) << " bytes " << endl;
	
	//displayBothClassA();	
	accessDataMembersOfBothClassA();
	cout << "main - end" << endl;
	return 0;
}


