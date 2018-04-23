// ========================================================================================================================================================================
/*
* Item 20:
* --------
* When we return objects by value from a function - we are creating a copy. Long story sort - we have nothing we can do
* about it.
* What we can do, is minimize the cost of this object creation. We can achinve that by "helping" our compiler to use the 
* famous RVO optimization (Return Value Optimization).
* 1) Enabling "completly" the RVO is done when we:
* a) Returning a "temporary" obejct from the function that returns an object by value.
* b) "Receiving" the return object into a non-constructed object.
* c) In this case, there will be an "extra" step due to the invocation of the operator=.
* 
* !! @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ !!
* !! @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ !!
* Key note: Always "help" the complier to imply the RVO by returing temporary (anonymous) object from function that return object 
*           by value.
* !! @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ !!
* !! @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ !!
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
	{
		m_a = other.m_a;
		cout << "A::A(copy) - setting m_a:" << m_a << " at this:" << this << endl;
	}

	A& operator=(const A& rhs)
	{
		if (this == &rhs)
		{
			cout << "A::operator= - trying to self assgin rhs:" << &rhs << endl;
			return *this;
		}

		cout << "A::operator= - returing this:" << this << endl;
		this->m_a = rhs.m_a;
		return *this;
	}

	A funcReturnByValueWithRVO(int a)
	{
		cout << "A::funcReturnByValueWithRVO" << endl;
		return A(a);	// 1a)
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
	A a1(1);
	cout << "\n \n item20Usage - performing: A a2 = a1.funcReturnByValueWithRVO(3)" << endl;
	A a2 = a1.funcReturnByValueWithRVO(2);	// 1b)
	cout << "item20Usage - a2 address is:" << &a2 << endl;
	cout << "\n \n item20Usage - performing: A a3 = a1.funcReturnByValueWithLocalObject(4)" << endl;
	A a3 = a1.funcReturnByValueWithLocalObject(4);
	cout << "item20Usage - a3 address is:" << &a3 << endl;
	cout << "\n \n item20Usage - performing: A a4(11); a4 = a1.funcReturnByValueWithRVO(5)" << endl;
	A a4(11);
	a4 = a1.funcReturnByValueWithRVO(5);	// 1c) 
	cout << "item20Usage - a4 address is:" << &a4 << endl;

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

