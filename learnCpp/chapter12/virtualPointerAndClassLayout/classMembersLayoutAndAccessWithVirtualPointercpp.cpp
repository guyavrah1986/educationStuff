// ===================================================================================================================================================================
// ===================================================================================================================================================================
// This file comes to include some more information about the behaviour of the virtual table mechanism in C++. 
// In this example a "2-levels" inheritence chain will be used to illustrate the way it works.
// 
// virtual table under the hood:
// -----------------------------
// Some notes about virtual functions and virtual tables:
// 0) Once a class has AT LEAST one virtual function --> it implies that it will have a virtual table + virtual pointer.
// 1) A virtual table is created ONCE for each class. It is located (implementation specific) somewhere (probably) in the BSS segment (all the data
//    which is relevant for constructing the virtual table is known at compile time so it could be placed there).It is static. 
// 2) The objective of the virtual pointer is to point to the virtual table.Its location will be (usually) at the first 4/8 bytes of the object (32/64 bit).
// 3) Virtual table is basically a structure that holds all the function pointers to all the VIRTUAL functions of an object. Note: It DOES NOT hold the 
//    pointers to non-virtual functions.
// 4) In the case of multiple inheritence, the derived class will inherite all it's base class(es) virtual pointer, thus increasing its size respectevly. 
//    Note that there will be no need for an additional virtual pointer "specifically" for the derived object (so in the example below - only two virtual pointers
//    will be added to the derived class). 
//    The layout will be as follows: (for the case below fo class Derived : public Base1, public Base2):
//    NOTES: 
//    - We assume "theoretically" there is no padding.
//    - Size of int and pointer is 4 bytes.
// 
//    bytes |           data
//    ---------------------------------  
//    0-3   |  vptr for Base1 v-table.
//    4-7   |  Base1 member (int)
//    8-11  |  vptr for Base2 v-table.
//    12-15 |  Base2 member (int)
//    16-19 |  Derived member (int)
//
//  5) The "extra" code that does the initialization of the v-table for each class in inserted by the compiler (for each ctor) right after the class's base class 
//     is done (in case there is one) and just before the body of the ctor is executed.
//     --> Due to this fact, calling a virtual function within a ctor, will invoke the current "most derived version" and NOT the absoulute most derived version 
//     ( as we wish...). 
//  
//  6) Some impacts of using v-table:
//     a) Calling a virtual function costs us in an extra read of the address of the actual function to be invoked during run-time (not so bad).
//        The exact arithmetic being done is pointer read + offset manipulation. 
//     b) Virtual functions CAN NOT be inline !!
//     c) For each class that has a virtual table - a table with X entires of pointers will be created ONCE.For example, if class A has 3 virtual functions in it,
//        then a virtual "table" (which usually be implemented by an array of pointers) will have 3 "entires" in it --> which will "cost" the program in 3 pointers
//        in the memory. 
//     d) For each instance of this class there will be an additional 4/8 bytes in its "size" due to the virtual pointer. 
//        IMPORTANT NOTE: In case class A derived from TWO classes which each one of them has a vritual table of its own, then the "extra" size in memory for erach 
//        instance of this class is 3 * size of pointer.
//     
// 
//     
// 
// ===================================================================================================================================================================
// ===================================================================================================================================================================
#include <iostream>

using namespace std;

class A
{
public:
	A(int a)
		: m_a(a)
	{
		cout << "A::A - calling Func1()" << endl;
		Func1();
		//Func3();
		cout << "A::A - set m_a to:" << m_a << ", this:" << this << endl;
	}

	virtual ~A()
	{
		cout << "A::~A - calling Func1()" << endl;
		Func1();
		cout << "A::~A - this:" << this << endl;
	}

	virtual void Func1()
	{
		cout << "A::Func1 - this:" << this << endl;
	}

	virtual void Func2()
	{
		cout << "A::Func2 - this:" << this << endl;
	}

	virtual void Func3() = 0;

	void Func4()
	{
		cout << "A::Func4" << endl;
	}

protected:
	int m_a;
};

class B : public A
{
public:
	B(int a, int b)
		: A(a)
		, m_b(b)
	{
		cout << "B::B - calling Func1()" << endl;
		Func1();
		cout << "B::B - set m_b to:" << m_b << ", this:" << this << endl;
	}

	virtual ~B()
	{
		cout << "B::~B - calling Func1()" << endl;
		Func1();
		cout << "B::~B - this:" << this << endl;
	}

	virtual void Func1()
	{
		cout << "B::Func1 - this:" << this << endl;
	}

	/*
	virtual void Func2()
	{
		cout << "B::Func2 - this:" << this << endl;
	}
	*/

	virtual void Func3()
	{
		cout << "B::Func3 - this:" << this << endl;
	}

	void Func4()
	{
		cout << "B::Func4" << endl;
	}

protected:
	int m_b;
};

class C : public B
{

public:
		C(int a, int b, int c)
			: B(a, b)
			, m_c(c)
		{
			cout << "C::C - set m_c to:" << m_c << endl;
		}

		virtual ~C()
		{
			cout << "C::~C" << endl;
		}

		virtual void Func1()
		{
			cout << "C::Func1" << endl;
		}

		virtual void Func2()
		{
			cout << "C::Func2" << endl;
		}

		virtual void Func3()
		{
			cout << "C::Func3" << endl;
		}

		void Func4()
		{
			cout << "C::Func4" << endl;
		}

protected:
		int m_c;
};

void callVirtualFunctionsViaPointer()
{
	cout << "callVirtualFunctionsViaPointer - start" << endl;
	B b(8,9);
	A* pa = &b;
	cout << "callVirtualFunctionsViaPointer - calling pa->Func1()" << endl;
	pa->Func1();
	cout << "callVirtualFunctionsViaPointer - calling pa->Func2()" << endl;
	pa->Func2();
	cout << "callVirtualFunctionsViaPointer - calling pa->Func3()" << endl;
	pa->Func3();	
	cout << "callVirtualFunctionsViaPointer - end" << endl;
}

void callNonVirtualFunction()
{
	cout << "callNonVirtualFunction - start" << endl;
	C c(1,2,3);
	A* pa = &c;
	cout << "callNonVirtualFunction - calling pa->Func4()" << endl;
	pa->Func4();

	B* pb = &c;
	cout << "callNonVirtualFunction - calling pb->Func4()" << endl;
	pb->Func4();

	C* pc = &c;
	cout << "callNonVirtualFunction - calling pc->Func4()" << endl;
	pc->Func4();

	cout << "callNonVirtualFunction - end" << endl;
}


void createDerivedObjectOnTheStack()
{
	cout << "createDerivedObjectOnTheStack - start" << endl;
	C c(12, 15, 17);
	cout << "createDerivedObjectOnTheStack - end" << endl;
}

// ===================================================================================================================================================================
// ===================================================================================================================================================================
// main program:
// ===================================================================================================================================================================
// ===================================================================================================================================================================
int main(int argc, char** argv)
{
	cout << "virtualTable - start" << endl;

	//createDerivedObjectOnTheStack();
	callVirtualFunctionsViaPointer();
	callNonVirtualFunction();

	cout << "virtualTable - start" << endl;
	return 0;
}


