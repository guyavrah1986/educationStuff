// ========================================================================================================================================================================
/*
* Item 17:
* --------
* This item talk about the conecpt of "lazy evaluation" - which, bottom line means, initialize (or create) anything (usually class's
* data members) as late as possible, i.e.- only when required. 
* This concpets has several "impacts" on typical use cases, for instance:
* 1) The need to check whether a data member is NULL or not in each member function.
* a) One way we can use lazy evalution is to initialize the data members to NULL pointers in the ctor 
* b) Then, only upon demand to actually "fetch" (initialize) them.
* c) In order to be able to perfomr the reuqired initialization in each member function (even those who are declared to be const) - we need 
*    to use the mutable keyword, which allows us to set the pointer to some values EVEN WITHIN "const member functions".
*
* !! @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ !!
* !! @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ !!
* Key note:
* !! @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ !!
* !! @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ !!
*/
// ======================================================================================================================================================================
#include <iostream>

using namespace std;

class MyLazyEvaluationObj
{
public:
	MyLazyEvaluationObj(int* pi, double* pd) // 1a)
		: m_pi(nullptr)
		, m_pd(nullptr)
	{
		cout << "MyLazyEvaluationObj::MyLazyEvaluationObj" << endl;
	}

	MyLazyEvaluationObj()
		: m_pi(nullptr)
		, m_pd(nullptr)
	{
		cout << "MyLazyEvaluationObj::MyLazyEvaluationObj(default)" << endl;
	}

	~MyLazyEvaluationObj()
	{
		cout << "MyLazyEvaluationObj::~MyLazyEvaluationObj" << endl; 
		delete m_pd;
		delete m_pi;
	}

	void doSomethingWithIntMember() const
	{
		cout << "MyLazyEvaluationObj::doSomethingWithIntMember" << endl;
		if (m_pi == nullptr)
		{
			cout << "MyLazyEvaluationObj::doSomethingWithIntMember - m_pi is NULL, initializing it with some value" << endl;
			m_pi = new int(17); // 1b)
		}
		else
		{
			cout << "MyLazyEvaluationObj::doSomethingWithIntMember - m_pi is already initialized with value:" << *m_pi << endl;
		}
	}

	void doSomethingWithDoubleMember() const
	{
		cout << "MyLazyEvaluationObj::doSomethingWithDoubleMember" << endl;
		if (m_pd == nullptr)
		{
			cout << "MyLazyEvaluationObj::doSomethingWithDoubleMember - m_pd is NULL, initializing it with some value" << endl;
			m_pd = new double(12.3); // 1b)
		}
		else
		{
			cout << "MyLazyEvaluationObj::doSomethingWithDoubleMember - m_pd is already initialized with value:" << *m_pd << endl;
		}
	}

	mutable int* m_pi;		// 1c)
	mutable double* m_pd;	// 1c)
};

void item17Usage()
{
	cout << "item17Usage - start" << endl;
	cout << "item17Usage - creating a MyLazyEvaluationObj on the stack" << endl;
	MyLazyEvaluationObj obj;
	cout << "item17Usage - FIRST time calling its const member function" << endl;
	obj.doSomethingWithIntMember();
	cout << "item17Usage - SECOND time calling its const member function" << endl;
	obj.doSomethingWithIntMember();
	
	cout << "\n \n item17Usage - end" << endl;
}

int main(int argc, char** argv)
{
	cout << "main - start" << endl;

	item17Usage();

	char c = 0;
	cout << "main - enter any key to terminate (and press enter)" << endl;
	cin >> c;
	cout << "\n \n main - end" << endl;
	return 0;
}
