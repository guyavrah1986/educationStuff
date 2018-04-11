// ========================================================================================================================================================================
/*
* Item 12:
* --------
* Preface:
* 1) Some key difference between passing an argument to a function than catching an exception in the catch clause:
* a) When we throw an exception (which might be any "std home-made" OR user defined class/object) to a catch cluases, if the catch 
*    clauses DOES NOT recive a pointer, meaning, it recives the exception "by reference" OR "by value" --> the object being thrown
*    is copied (!!) from the throw site ("caller").
* b) This is NOT the case with "simple" object passing to function's arguments.
* 
* !! @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ !!
* !! @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ !!
* Key note: 
* !! @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ !!
* !! @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ !!
*/
// ======================================================================================================================================================================

#define _CRTDBG_MAP_ALLOC  // NOTE: the order of the includes that FOLLOWS this define is important !!!
#include <stdlib.h>  
#include <crtdbg.h> 

#include <iostream>
#include <string>

using namespace std;

class A
{
public:
	A(const string& str)
		: m_str(str)
	{
		cout << "A::A - set m_str to:" << m_str << endl;
	}

	~A()
	{
		cout << "A::~A" << endl;
	}

	A(const A& other)
		: A(other.m_str)
	{
		cout << "A::A(copy)" << endl;
	}

	A& operator=(const A& rhs)
	{
		if (this == &rhs)
		{
			cout << "A::operator= - returning *this" << endl;
			return *this;
		}

		this->m_str = rhs.m_str;
		return *this;
	}

	string m_str;
};

class B : public A
{
public:
	B(const string& str, int b)
		: A(str)
		, m_b(b)
	{
		cout << "B::B - set m_b to:" << m_b << endl;
	}

	~B()
	{
		cout << "B::~B" << endl;
	}

	B(const B& other)
		: B(other.m_str, other.m_b)
	{
		cout << "B::B(copy)" << endl;
	}

	int m_b;
};

void getAByRef(const A& a)
{
	cout << "getAByRef - got a object with address:" << &a << endl;
}

void diffBetweenCatchAndArgumentByValOrRef()
{
	cout << "diffBetweenCatchAndArgumentByValOrRef - start" << endl;
	try
	{
		A a("A on function stack");
		cout << "diffBetweenCatchAndArgumentByValOrRef - within try block, calling getAByRef, sending it a local object with address:" << &a << " as an argument" << endl;
		getAByRef(a); // 1b)
		cout << "diffBetweenCatchAndArgumentByValOrRef - within try block, throwing the same local A object as an exception" << endl;
		throw a; // 1a)
	}
	catch (const A& a) // 1a) 
	{
		cout << "diffBetweenCatchAndArgumentByValOrRef - within catch block, caught an A object with address:" << &a << endl;
	}

}

void item12Usage()
{
	cout << "item12Usage - start" << endl;

	diffBetweenCatchAndArgumentByValOrRef();

	cout << "\n \n item12Usage - end" << endl;
}

int main(int argc, char** argv)
{
	cout << "main - start" << endl;

	item12Usage();

	char c = 0;
	cout << "main - enter any key to terminate (and press enter)" << endl;
	cin >> c;
	cout << "\n \n main - end" << endl;
	_CrtDumpMemoryLeaks();
	return 0;
}
