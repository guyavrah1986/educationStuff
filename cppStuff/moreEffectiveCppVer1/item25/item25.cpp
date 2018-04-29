// ========================================================================================================================================================================
/*
* Item 25:
* --------
* Sometimes it is usfull to declare the ctor as "virtual". In this specific example, we define the virtual copy ctor.
* 1a) When we define the "clone" method, which practically it is the copy ctor, we can define the return type in each of the 
*    derived's implementation with the class's specific type (and not keeping the entire function's signature identical to the 
*    Base's class signature).
*    NOTE:It is possible to return a different type from the Base's class function's ONLY if the return type is a pointer OR
*    a reference (i.e.- it will not work with objets).
*
* !! @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ !!
* !! @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ !!
* Key notes:
* 
* 
* !! @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ !!
* !! @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ !!
*
*/
// ======================================================================================================================================================================
#define _CRTDBG_MAP_ALLOC  // NOTE: the order of the includes that FOLLOWS this define is important !!!
#include <stdlib.h>  
#include <crtdbg.h> 

#include <iostream>
#include <list>

using namespace std;

class Base
{
public:
	Base(int b)
		: m_b(b)
	{
		cout << "Base::Base - setting m_b to:" << m_b << " at address:" << this << endl;
	}

	Base()
		: m_b(1)
	{
		cout << "Base::Base(default) - setting m_b to:" << m_b << " at address:" << this << endl;
	}

	Base(const Base& other)
	{
		this->m_b = other.m_b;
		cout << "Base::Base(copy)" << endl;
	}

	virtual ~Base()
	{
		cout << "Base::~Base - m_b:" << m_b << " at address:" << this << endl;
	}

	virtual Base* clone() const = 0;

	int m_b;
};

class Derived1 : public Base
{
public:
	Derived1(int d1, int b)
		: Base(b)
		, m_d1(d1)
	{
		cout << "Derived1::Derived1 - setting m_d1 to:" << m_d1 << " at address:" << this << endl;
	}

	Derived1()
		: m_d1(1)
	{
		cout << "Derived1::Derived1(default) - setting m_d1 to:" << m_d1 << " at address:" << this << endl;
	}

	Derived1(const Derived1& other)
	{
		this->m_d1 = other.m_d1;
		cout << "Derived1::Derived1(copy) - setting m_d1 to:" << m_d1 << " at address:" << this << endl;
	}

	virtual ~Derived1()
	{
		cout << "Derived1::~Derived1 - m_d1:" << m_d1 << " at address:" << this << endl;
	}

	virtual Derived1* clone() const	// 1a)
	{
		return new Derived1();
	}

	int m_d1;
};

class Derived2 : public Base
{
public:
	Derived2(int d2, int b)
		: Base(b)
		, m_d2(d2)
	{
		cout << "Derived2::Derived2 - setting m_d2 to:" << m_d2 << " at address:" << this << endl;
	}

	Derived2()
		: m_d2(2)
	{
		cout << "Derived2::Derived2(default) - setting m_d2 to:" << m_d2 << " at address:" << this << endl;
	}

	Derived2(const Derived2& other)
	{
		this->m_d2 = other.m_d2;
		cout << "Derived2::Derived2(copy) - setting m_d2 to:" << m_d2 << " at address:" << this << endl;
	}

	virtual ~Derived2()
	{
		cout << "Derived2::~Derived2 - m_d2:" << m_d2 << " at address:" << this << endl;
	}

	virtual Derived2* clone() const	// 1a)
	{
		return new Derived2();
	}

	int m_d2;
};

class X
{
public:
	X()
	{
		cout << "X::X" << endl;
	}

	X(const X& other)
	{
		cout << "X::X(copy) - about to copy " << other.m_list.size() << " elements of other.m_list" << endl;
		for (list<Base*>::const_iterator it = other.m_list.begin(); it != other.m_list.end(); ++it)
		{
			this->m_list.emplace_back((*it)->clone());
		}
	}

	~X()
	{
		cout << "X::~X" << endl;
		for (list<Base*>::const_iterator it = m_list.begin(); it != m_list.end(); ++it)
		{
			delete *it;
		}
	}

	list<Base*> m_list;
};

void fillM_listWithDerivedObjects(X& x)
{
	x.m_list.emplace_back(new Derived1(1, 1));
	x.m_list.emplace_back(new Derived2(2, 2));
	x.m_list.emplace_back(new Derived1(3, 3));
	x.m_list.emplace_back(new Derived2(4, 4));
}

void item25Usage()
{
	cout << "item25Usage - start" << endl;
	X x1;
	cout << "item25Usage - about to add Derived's elements to x1 object" << endl;
	fillM_listWithDerivedObjects(x1);
	cout << "item25Usage - about to copy construct x1 into newly created x2 object" << endl;
	X x2(x1);

	cout << "\n \n item25Usage - end" << endl;
}

int main(int argc, char** argv)
{
	cout << "main - start" << endl;
	item25Usage();
	
	char c;
	cout << "\n \n main - enter any key and press ENTER to terminate" << endl;
	cin >> c;
	_CrtDumpMemoryLeaks();
	return 0;
}
