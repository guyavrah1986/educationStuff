// ========================================================================================================================================================================
/*
* Item 12:
* --------
* Preface:
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

void item12Usage()
{
	cout << "item12Usage - start" << endl;

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
