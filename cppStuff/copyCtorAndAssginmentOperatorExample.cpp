// ===================================================================================================================================================================
// ===================================================================================================================================================================
// copy Ctor and assignment operator:
// ---------------------------------
//
//
//
// ===================================================================================================================================================================
// ===================================================================================================================================================================

#include "copyCtorAndAssginmentOperatorExample.h"

#include <iostream>
#include <cstring>


using namespace std;



A::A(int a, const char* str)
		: m_a(a)
		, m_cstr(nullptr)
{
	if (str != nullptr)
	{
		// get the given str length
		size_t len = getStrLen(str);
		if (len > 0)
		{
			m_cstr = new char [len + 1];
			strcpy(m_cstr, str);
		}

	}

	cout << "A::A - init m_a:" << m_a << " and m_cstr:" << m_cstr << " this pointer is at:" << this << endl;
}

A::A() 
	: A(17, nullptr)
{
	cout << "A::A() - this:" << this << endl;
}

A::~A()
{
	if (m_cstr != nullptr)
	{
		delete [] m_cstr;
	}
	cout << "A::~A - this:" << this << endl; 
}

A::A(const A& other) 
	: A(other.m_a, other.m_cstr)
{
	cout << "A::A(other) - this:" << this << endl;
}

A& A::operator=(const A& rhs)
{
	if (this == &rhs)
	{
		cout << "A::operator= - trying to assgin the same instance, returning *this" << endl;
		return *this;
	}

	// free allocated memory of with the "old" content
	if (this->m_cstr != nullptr)
	{		
		delete [] m_cstr;
	}

	size_t len = getStrLen(rhs.m_cstr);
	this->m_cstr = new char [len + 1];
	strcpy(this->m_cstr, rhs.m_cstr);
	this->m_a = rhs.m_a;
	cout << "A::operator= - done assgining rhs (address):" << &rhs << " to this object(address):" << this << endl;
}


size_t A::getStrLen(const char* str) const 
{
	// get the given str length
	size_t len = 0;
	char* tmp = const_cast<char*>(str);
	while (*tmp != '\0')
	{
		++len;
		++tmp;
	}

	return len;
}

ostream& operator<<(ostream& out, const A& obj)
{	
	cout << " m_cstr is:" << obj.m_cstr << " , " << &(obj.m_cstr) << " m_a is:" << obj.m_a << " , " << &(obj.m_a) << endl;
	return out;
}


// ===================================================================================================================================================================
// =================================================================================================================================================================== 

int main(int argc, char** argv)
{
	cout << "main - start \n \n" << endl;

	cout << "size of int:" << sizeof(int) << endl;
	cout << "size of char* :" << sizeof(char*) << endl;

	A a1(12, "buba");	// --> calls ctor
	cout << "main - a1 detailes:";
	cout << a1;

	
	A a2 = a1;		// --> calls copy ctor
	cout << "main - a2 detailes:" << endl;
	cout << a2;

	cout << "main - about to assgin a1 = a1 " << endl;
	a1 = a1;	        // --> calls assignment operator (return *this)
	
	cout << "main - about to assgin a2 = a1 " << endl;
	a2 = a1;		// --> calls assignment operator

	cout << "main - after assgining a2 = a1 , a2 detailes:";
	cout << a2;




	cout << "\n \n main - end" << endl;
	return 0;
}
