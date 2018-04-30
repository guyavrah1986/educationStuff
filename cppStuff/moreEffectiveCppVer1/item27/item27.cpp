// ========================================================================================================================================================================
/*
* Item 27:
* --------
* 1) In case we wish to be able to create an object ONLY on the heap, one approach is to define either:
* a) Define the Dtor as private.
* b) Note that we do need to provide an "alternative" for the dtor.
* c) Also worth mention here is that we need to declare ONLY a single method (Dtor) as private (leaving the burdn
*	 of verifying ALL the Ctor's are private).
* 
*
* !! @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ !!
* !! @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ !!
* Key notes: - If we decide to create object only on the heap than doing so by declaring the dtor as private will 
*			   enable us to decalre ONLY a single method.
*			 - If, on the other hand we chose 
* 
* !! @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ !!
* !! @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ !!
*
*/
// ======================================================================================================================================================================
#define _CRTDBG_MAP_ALLOC  // NOTE: the order of the includes that FOLLOWS this define is important !!!
#include <stdlib.h>  
#include <crtdbg.h> 

#include <iostream>

using namespace std;

class OnlyHeapObjPrivateDtor
{
public:
	OnlyHeapObjPrivateDtor(int val)
	{
		cout << "OnlyHeapObjPrivateDtor::OnlyHeapObjPrivateDtor - set m_val to:" << val << " at"
			" address:" << this << endl;
		m_val = new int(val);
	}

	OnlyHeapObjPrivateDtor()
	{
		const int defaultVal = 8;
		cout << "OnlyHeapObjPrivateDtor::OnlyHeapObjPrivateDtor(default) - set m_val to:" << defaultVal << " at"
			" address:" << this << endl;
		m_val = new int(defaultVal);
	}

	OnlyHeapObjPrivateDtor(const OnlyHeapObjPrivateDtor& other)
	{
		const int defaultVal = 8;
		cout << "OnlyHeapObjPrivateDtor::OnlyHeapObjPrivateDtor(copy) - set m_val to:" << *(other.m_val) << " at"
			" address:" << this << endl;
		m_val = new int(*(other.m_val));
	}

	void destroy() const	// 1b)
	{
		cout << "OnlyHeapObjPrivateDtor::destroy - m_val:" << *m_val << " at"
			" address:" << this << endl;
		delete this;
	}

private:
	~OnlyHeapObjPrivateDtor()	// 1a)
	{
		cout << "OnlyHeapObjPrivateDtor::~OnlyHeapObjPrivateDtor(copy) - m_val:" << *m_val << " at"
			" address:" << this << endl;
		delete m_val;
	}

	const int* m_val;
};

void item27Usage()
{
	cout << "item27Usage - start" << endl;
	cout << "item27Usage - creating HEAP based OnlyHeapObjPrivateDtor" << endl;
	OnlyHeapObjPrivateDtor* obj1 = new OnlyHeapObjPrivateDtor(12);	// 1) works !!
	obj1->destroy();

	//OnlyHeapObjPrivateDtor obj; 	// 1) Wont compile !!
	cout << "\n \n item27Usage - end" << endl;
}

int main(int argc, char** argv)
{
	cout << "main - start" << endl;
	item27Usage();
	
	char c;
	cout << "\n \n main - enter any key and press ENTER to terminate" << endl;
	cin >> c;
	_CrtDumpMemoryLeaks();
	return 0;
}
