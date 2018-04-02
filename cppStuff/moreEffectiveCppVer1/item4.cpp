// =============================================================================================================================================
/*
* item 4:
* ------
* C++ compilers automatically creates several functions to any user defined class. One of them is the default constructor. 
*
* 1) First, let us see some "issues" we might suffer in case we WON'T have a default constructor to our class. 
* a) In this case, we can see that it is impossible to declare (create) a "stack-based" array of objects with no default Ctor.
*
*/
// =============================================================================================================================================

#include <iostream>

using namespace std;

class Base
{
	public:
	Base(int a) 
		: m_a(a)
	{
		cout << "Base::Base - setting m_a to:" << m_a << " this address is:" << this << endl;
	}
	
	/*
	Base() 
		: m_a(12)
	{
		cout << "Base::Base(defualt)" << endl;
	}
	*/
	
	virtual ~Base()
	{
		cout << "Base::~Base - this address is:" << this << endl;
	}

	int m_a;
};

void noDefaultCtorIssueWithArraysInitializationExample()
{
	cout << "noDefaultCtorIssueWithArraysInitializationExample - start" << endl;
	
	// 1a) 
	const size_t size = 3;
	//Base arr [size]; --> Won't compile: "no appropriate default constructor avialble
}

void item4Usage()
{
	cout << "item4Usage - start" << endl;

	noDefaultCtorIssueWithArraysInitializationExample();
	
	cout << "\n \n item4Usage - end" << endl;
}

int main(int argc, char** argv)
{
	cout << "main - start" << endl;
	item4Usage();
	cout << "\n \n main - end" << endl;
	return 0;
}
