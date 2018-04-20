// ========================================================================================================================================================================
/*
* Item 17:
* --------
* This item talk about the conecpt of "lazy evaluation" - which, bottom line means, initialize (or create) anything (usually class's
* data members) as late as possible, i.e.- only when required. 
* This concpets has several "impacts" on typical use cases, for instance:
* 1) One way to
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
	MyLazyEvaluationObj(int* pi, double* pd)
		: m_pi(nullptr)
		, m_pd(nullptr)
	{
		cout << "MyLazyEvaluationObj::MyLazyEvaluationObj" << endl;
	}

	~MyLazyEvaluationObj()
	{
		cout << "MyLazyEvaluationObj::~MyLazyEvaluationObj" << endl;
	}

	void doSomethingWithIntMember() const
	{
		cout << "MyLazyEvaluationObj::doSomethingWithIntMember" << endl;

	}

	void doSomethingWithDoubleMember() const
	{
		cout << "MyLazyEvaluationObj::doSomethingWithDoubleMember" << endl;
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
