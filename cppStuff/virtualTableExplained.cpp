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

	int m_base1;
};

class Base2
{
public:
	Base2() : m_base2(15)
	{
		cout << "Base2::Base2 - setting m_base1 to:" << m_base2 << endl;
	}

	virtual ~Base2()
	{
		cout << "Base2::~Base2" << endl;
	}

	virtual void func1()
	{
		cout << "Base2::func1 - m_base2 is:" << m_base2 << endl;
	}

	int m_base2;
};


void printVirtualFunctionAddress(Base1* obj)
{

}

// ===================================================================================================================================================================
// ===================================================================================================================================================================
// main program:
// ===================================================================================================================================================================
// ===================================================================================================================================================================


int main(int argc, char** argv)
{
	cout << "main - start" << endl;

	void (Base1::*mfp)() = &Base1::func1;
	Base1* b1 = new Base1;
	printf("address: %p", (void*)(b1->*mfp));

	cout << "main - end" << endl;
	return 0;
}
