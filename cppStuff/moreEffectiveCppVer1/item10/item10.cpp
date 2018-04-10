// ========================================================================================================================================================================
/*
* Item 10:
* --------
* Long story short - if a class's ctor does not "run to completion" (for instance by throwing an exception during its run) 
*
* Notes:
* ) No need to check for NULL pointer before deleting the pointers of class C in the dtor (C++ permits to delete NULL pointers).
*/
// ======================================================================================================================================================================

#define _CRTDBG_MAP_ALLOC  // NOTE: the order of the includes that FOLLOWS this define is important !!!
#include <stdlib.h>  
#include <crtdbg.h> 

#include <iostream>

using namespace std;

class A
{
public:
	A(int a)
		: m_a(a)
	{
		cout << "A::A - setting m_a to:" << m_a << endl;
	}

	~A()
	{
		cout << "A::~A" << endl;
	}

	int m_a;
};

class B
{
public:
	B(int b)
		: m_b(b)
	{
		cout << "B::B - setting m_b to:" << m_b << endl;
	}

	~B()
	{
		cout << "B::~B" << endl;
	}

	int m_b;
};

class C
{
public:
	C(int a, int b)
	{
		if (a != 0)
		{
			m_a = new A(a);
			cout << "C::C - setting m_a to a newly A object created on the heap (address):" << m_a << endl;
		}

		if (b != 0)
		{
			m_b = new B(b);
			cout << "C::C - setting m_b to a newly B object created on the heap (address):" << m_b << endl;
		}
	}

	~C()
	{
		delete m_a;
		delete m_b;
		cout << "C::~C" << endl;
	}

	A* m_a;
	B* m_b;
};

void item10Usage()
{
	cout << "item10Usage - start" << endl;

	// invoke a normal creation of a C object - on the stack
	{
		C c(1, 2);
	}

	cout << "\n \n item10Usage - " << endl;
}

int main(int argc, char** argv)
{
	cout << "main - start" << endl;

	item10Usage();
	
	char c = 0;
	cout << "main - enter any key to terminate (and press enter)" << endl;
	cin >> c;
	cout << "\n \n main - end" << endl;
	_CrtDumpMemoryLeaks();
	return 0;
}
