// ===================================================================================================================================================================
// ===================================================================================================================================================================
//
// virtual table under the hood:
// -----------------------------
// 
// 
// ===================================================================================================================================================================
// ===================================================================================================================================================================


#include <iostream>
using namespace std;


class Base1
{
public:
	Base1() : m_base1(17)
	{
		cout << "Base1::Base1 - setting m_base1 to:" << m_base1 << endl;
	}

	virtual ~Base1()
	{
		cout << "Base1::~Base1" << endl;
	}

	virtual void func1()
	{
		cout << "Base1::func1 - m_base1 is:" << m_base1 << endl;
	}

	void foo()
	{
		cout << "Base1::foo" << endl;
	}

	int m_base1;
};

class Base2
{
public:
	Base2() : m_base2(15)
	{
		cout << "Base2::Base2 - setting m_base2 to:" << m_base2 << endl;
	}

	virtual ~Base2()
	{
		cout << "Base2::~Base2" << endl;
	}

	virtual void func2()
	{
		cout << "Base2::func2 - m_base2 is:" << m_base2 << endl;
	}

	int m_base2;
};

class Derived : public Base1, public Base2
{
public:
	Derived() : m_derived(12)
	{
		cout << "Derived::Derived - setting m_derived to:" << m_derived << endl;
	}

	virtual ~Derived()
	{
		cout << "Derived::~Derived" << endl;
	}

	virtual void func1()
	{
		cout << "Derived::func1 - m_derived is:" << m_derived << endl;
	}

	int m_derived;
};

// ===================================================================================================================================================================
// ===================================================================================================================================================================
// main program:
// ===================================================================================================================================================================
// ===================================================================================================================================================================


int main(int argc, char** argv)
{
	cout << "virtualTableExplained - start " << endl;
	Base1* b1 = new Base1;
	Base2* b2 = new Base2;

	{
		void (Base1::*mfp)() = &Base1::func1;
		printf("virtualTableExplained - address of Base1::func1 is: %p \n", (void*)(b1->*mfp));
	}

	{
		void (Base2::*mfp)() = &Base2::func2;
		printf("virtualTableExplained - address of Base2::func2 is: %p \n", (void*)(b2->*mfp));
	}

	Derived* d = new Derived;
	{
		void (Derived::*mfp)() = &Derived::func1;
		printf("virtualTableExplained - address of Derived::func1 is: %p \n", (void*)(d->*mfp));
	}

	delete b1;
	delete b2;
	delete d;

	cout << "virtualTableExplained - end" << endl;
	return 0;
}
