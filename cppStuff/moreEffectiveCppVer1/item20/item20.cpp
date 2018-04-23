// ========================================================================================================================================================================
/*
* Item 20:
* --------
*
*
*/
// ======================================================================================================================================================================

#include <iostream>

using namespace std;

class A
{
public:
	A(int a)
		: m_a(a)
	{
		cout << "A::A - setting m_a:" << m_a << " at this:" << this << endl;
	}

	~A()
	{
		cout << "A::~A - m_a:" << m_a << " at this:" << this << endl;
	}

	A(const A& other)
		: A(other.m_a)
	{
		cout << "A::A(copy) - created A object with address:" << this << endl;
	}

	A& operator=(const A& rhs)
	{
		if (this == &rhs)
		{
			cout << "A::operator= - trying to self assgin rhs:" << &rhs << endl;
			return *this;
		}

		this->m_a = rhs.m_a;
		return *this;
	}

	A funcReturnByValueWithRVO(int a)
	{
		cout << "A::funcReturnByValueWithRVO" << endl;
		return A(a);
	}

	A funcReturnByValueWithLocalObject(int a)
	{
		A stackA(a);
		cout << "A::funcReturnByValueWithLocalObject - returning stack based A object with"
			" address:" << &stackA << endl;
		return stackA;
	}

	int m_a;
};

void item20Usage()
{
	cout << "item20Usage - start" << endl;


	cout << "\n \n item20Usage - end" << endl;
}

int main(int argc, char** argv)
{
	cout << "main - start" << endl;
	item20Usage();
	
	char c;
	cout << "main - enter any key to terminate and hit ENTER" << endl;
	cin >> c;
	return 0;
}

