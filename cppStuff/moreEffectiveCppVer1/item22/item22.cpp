// ========================================================================================================================================================================
/*
* Item 22:
* --------
* When implementing the operator@ (stand-alone) and operator@= (compund) we face different motivations to use each one 
* of them.
* 1) Note that we:
* a) Enabling the RVO by NOT naming the return object (keeping it anonymous).
* b) Implementing the stand-alone IN TERMS of the compund flavour.
* 
* !! @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ !!
* !! @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ !!
* Key note: 
* !! @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ !!
* !! @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ !!
*
*/
// ======================================================================================================================================================================

#include <iostream>

using namespace std;

class MyInt
{
public:
	MyInt()
		: m_int(0)
	{
		cout << "MyInt::MyInt - setting m_int to:" << m_int << " at address:" << this << endl;
	}

	MyInt(int val)
		: m_int(val)
	{
		cout << "MyInt::MyInt - setting m_int to:" << m_int << " at address:" << this << endl;
	}

	~MyInt()
	{
		cout << "MyInt::~MyInt - m_int:" << m_int << " at address:" << this << endl;
	}

	MyInt& operator+=(const MyInt& rhs)
	{
		cout << "operator+=(const MyInt& rhs)" << endl;
		this->m_int = this->m_int + rhs.m_int;
		return *this;
	}

	friend const MyInt operator+(const MyInt& lhs, const MyInt& rhs);

	int m_int;
};

const MyInt operator+(const MyInt& lhs, const MyInt& rhs)
{
	cout << "operator+(const MyInt& lhs, const MyInt& rhs)" << endl;
	return MyInt(lhs.m_int) += rhs;	// 1)
}

void item22Usage()
{
	cout << "item22Usage - start" << endl;


	cout << "\n \n item22Usage - end" << endl;
}

int main(int argc, char** argv)
{
	cout << "main - start" << endl;
	item22Usage();
	
	char c;
	cout << "\n \n main - enter any key and press ENTER to terminate" << endl;
	cin >> c;
	return 0;
}
