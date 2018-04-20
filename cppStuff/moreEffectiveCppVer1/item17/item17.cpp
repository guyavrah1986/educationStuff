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
			//m_pi = new double;
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
			//m_pd = new double;
		}
		else
		{
			cout << "MyLazyEvaluationObj::doSomethingWithDoubleMember - m_pd is already initialized with value:" << *m_pd << endl;
		}
	}

	int* m_pi;
	double* m_pd;
};

void item17Usage()
{
	cout << "item17Usage - start" << endl;



	cout << "\n \n item17Usage - end" << endl;
}

int main(int argc, char** argv)
{
	cout << "main -start" << endl;

	item17Usage();

	cout << "\n \n main - end" << endl;
	return 0;
}
