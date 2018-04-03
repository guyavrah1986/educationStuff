// =============================================================================================================================================
/*
* item 4:
* ------
* C++ compilers automatically creates several functions to any user defined class. One of them is the default constructor. 
*
* 1) First, let us see some "issues" we might suffer in case we DON'T have a default constructor in our class. 
* a) In this case, we can see that it is impossible to declare (create) a "stack-Base1d" array of objects with no default Ctor.
* b) The same goes when the araay is created on the heap.
* 
* 2) It is worth mentionng that most (maybe all) of the STL containers DOES NOT require to have a default ctor --> so in these cases
*    there won't be any problem.
*
*/
// =============================================================================================================================================
#include <iostream>
#include <vector>
#include <map>

using namespace std;

class Base1
{
	public:
	Base1(int a) 
		: m_a(a)
	{
		cout << "Base1::Base1 - setting m_a to:" << m_a << " this address is:" << this << endl;
	}
	
	virtual ~Base1()
	{
		cout << "Base1::~Base1 - this address is:" << this << endl;
	}

	int m_a;
};

class Base2
{
	public:
	Base2(int b) 
		: m_b(b)
	{
		cout << "Base2::Base2 - setting m_b to:" << m_b << " this address is:" << this << endl;
	}
	
	Base2()
		: m_b(17)
	{
		cout << "Base2::Base2(default) - setting m_b to:" << m_b << endl;	
	}
	
	virtual ~Base2()
	{
		cout << "Base2::~Base2 - this address is:" << this << endl;
	}

	int m_b;
};


void noDefaultCtorIssueWithArraysInitializationExample()
{
	cout << "noDefaultCtorIssueWithArraysInitializationExample - start" << endl;

	const size_t size = 3;
	// 1a) Won't compile cause we defined (at least) one ctor in our class
	// which causes the default ctor of the compiler NOT to be generated, so 
	// declare "stack-based" array of this kind of object is not possible.
	// Base1 arr [size];

	// 1b) This also won't work
	// Base1* bp = new Base1 [size]; 
	
	// 2) No probelem - STL containers has the copy-constructable and 
	//    assginmenable --> so this code will work.
	map<Base1, int> m;
	vector<Base1> vec1;
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
	
	
	cout << "main - please enter any key to terminate..." << endl;
	char c;
	cin >> c;
	cout << "\n \n main - end" << endl;
	return 0;
}
