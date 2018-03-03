// ========================================================================================================================================================================
/*
* Temporaries:
* ------------
* The "formal" definition of when temporary objects are created is when:A non heap object is created AND it is not named.
* Practiaclly it happens in two main cases:
* a) An implict conversion is made in a function call to make the passed argument being valid argument.
* # By passing an object by value.
* # When passing an object by non const reference - a good example will be the conversion of char arr[] into a string object (see example in the book).
* 
* b) When a function returns an object by value.
* This is relevant almost in all cases, there are some exceptions though (the Return Value Optimization aka RVO is one of them).
*
*/
// ======================================================================================================================================================================

#include <iostream>

using namespace std;

class A
{
	public:
	A(int a) : m_a(a)
	{
		cout << "A::A - setting m_a to:" << m_a << endl;
	}

	virtual ~A()
	{
		cout << "A::~A" << endl;
	}

	A(const A& other) : A(other.m_a)
	{
		cout << "A::A(copy)" << endl;
	}

	int m_a;
};


void passArgByConstRef(const A& arg)
{
	cout << "passArgByConstRef - address of recived argument is:" << &arg << endl;
}

void passArgByValue(A arg)
{
	cout << "passArgByNonConstRef - address of recived argument is:" << &arg << endl;
}

void item19Usage()
{
	cout << "item19Usage - start" << endl;

	A obj(17);
	cout << "item19Usage - creating an object on the stack with address of:" << &obj << endl;
	
	passArgByConstRef(obj);	// no temp is created !!

	passArgByValue(obj);	// a temp object is created and destroyed once the function returns !!

	cout << "\n \n item19Usage - end" << endl;
}

int main(int argc, char** argv)
{
	cout << "main - start" << endl;
	item19Usage();
	
	cout << "\n \n main - end" << endl;
	return 0;
}

