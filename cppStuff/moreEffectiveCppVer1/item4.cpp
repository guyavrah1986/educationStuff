// =============================================================================================================================================
/*
* item 4:
* ------
* 
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
