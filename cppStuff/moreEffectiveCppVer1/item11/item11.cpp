// ========================================================================================================================================================================
/*
* Item 11:
* --------
*
*
*/
// ======================================================================================================================================================================

#define _CRTDBG_MAP_ALLOC  // NOTE: the order of the includes that FOLLOWS this define is important !!!
#include <stdlib.h>  
#include <crtdbg.h> 

#include <iostream>
#include <memory>

using namespace std;

class A
{
public:
	A(int a)
		: m_a(a)
	{
		cout << "A::A - set m_a to:" << m_a << endl;
	}

	A()
		: A(17)
	{
		cout << "A::A(default)" << endl;
	}

	~A()
	{
		cout << "A::~A" << endl;
		throw exception("sample exception to simulate situation where the dtor of class A threw an exception");
	}

	int m_a;
};

class B
{
public:
	B(int a)
		: m_a(new A())
	{
		cout << "B::B" << endl;
	}

	~B()
	{
		cout << "B::B" << endl;
	}

	unique_ptr<A> m_a;
};
void item11Usage()
{
	cout << "item11Usage - start" << endl;
	
	cout << "\n \n item11Usage - end" << endl;
}

int main(int argc, char** argv)
{
	cout << "main - start" << endl;

	item11Usage();

	char c = 0;
	cout << "main - enter any key to terminate (and press enter)" << endl;
	cin >> c;
	cout << "\n \n main - end" << endl;
	_CrtDumpMemoryLeaks();
	return 0;
}
