// ===================================================================================================================================================================
// ===================================================================================================================================================================
// Virtual functions invocations mechanisms:
// -----------------------------------------
// 1) When calling a NON virtual function via a pointer (or reference) to some object, the function to be invoked is deduced accoring to the type of the pointer (or
//    reference) that points to the actual object. This is statically determined, at compile time. So in the below cases:
// a) The Q::pf fucntion will be called, cause the pq is pointer of type Q 
// b) The P::pf fucntion will be called, cause the ppq is pointer of type P
// 
// 2) When calling a virtual function, via a pointer (or reference) to some object the most derived "version" of the virtual function will be invoked.
//    It is determined at run-time. Regardless  of the declared type of the pointer expression left of the -> operator, the virtual function to  call is the one 
//    appropriate to the type of the actual instance addressed by the pointer.
// a+b) In both cases the Q:pvf function will be called.
//
// 3) When calling a virtual (or non virtual) function that is present ONLY in the dervied class, only a pointer of type Derived can call this function. This is 
//    because to the basic fact that only thr derived class knows about this function.Due to this fact, 3b won't compile.
//
// 4) Note that due to the fact that the Derived class only inherties from one base class, the it will have only ONE virtual pointer that will point to the virtual
//    table of the Base class, to which that the "new" virtual functions of Derived will be "appended to".
//
//
// ===================================================================================================================================================================
// ===================================================================================================================================================================
#include <iostream>

using namespace std;

struct P 
{ 
	// class methods
	void pf()
	{
		cout << "P:pf" << endl;
	}
	
	virtual void pvf()
	{
		cout << "P:pvf" << endl;
	}
 
	// class members
	int p1; 
}; 

struct Q : P 
{ 
	// class methods
	
	// "hides" P::pf 
	void pf()
	{
		cout << "Q::pf" << endl;
	}
	
	// new
	void qf()
	{
		cout << "Q::qf" << endl;
	}
	
	// overrides P::pvf 
	void pvf()
	{
		cout << "Q::pvf" << endl;
	} 
	
	// new 
	virtual void qvf()
	{
		cout << "Q::qvf" << endl;
	} 
	
	// class members
	int q1;  
}; 

int main(int argc, char** argv)
{
	cout << "main - start" << endl;
	Q q;
	Q* pq = &q;
	P* ppq = &q;
	
	// calling NON virtual function 		
	cout << "main - about to call pq->pf()" << endl;
	pq->pf();					// 1a)
	cout << "main - about to call ppq->pf()" << endl;
	ppq->pf();					// 1b)
	
	// calling virtual function that is implemented both in base and derived classes
	cout << "main - about to call pq->pvf()" << endl;
	pq->pvf();					// 2a)
	cout << "main - about to call ppq->pvf()" << endl;
	ppq->pvf();					// 2b)
	
	// calling virtual function that is implemented ONLY in derived class
	cout << "main - about to call pq->qvf()" << endl;
	pq->qvf();					// 3a)
	cout << "main - about to call ppq->qvf()" << endl;
	//ppq->qvf();					// 3b)
	
	/*
	P p; P* pp = &p; Q q; P* ppq = &q; Q* pq = &q; 
pp->pf(); // pp->P::pf(); // P::pf(pp); 
ppq->pf(); // ppq->P::pf(); // P::pf(ppq); 
pq->pf(); // pq->Q::pf(); // Q::pf((P*)pq); 
pq->qf(); // pq->Q::qf(); // Q::qf(pq); 
*/
	cout << "main - end" << endl;
}
