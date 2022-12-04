// ================================================================================================================================
/*
* What will be the output of the program ?
*/
// ================================================================================================================================
#include <iostream>

using namespace std;

class A 
{
	public:
		A() { cout << "A Ctor " << endl; }
		~A() { cout << "A Dtor " << endl; }
		
		void p1() { cout << "A : p1 " << endl; }
		virtual void p2() { cout << "A : p2 " << endl; }
};

class B : public A 
{
	public:	
		B() { cout << "B Ctor " << endl; }
		~B() { cout << "B Dtor " << endl; }
		void p1 () { cout << "B : p1 " << endl;}
		void p2() { cout << "B : p2 " << endl; }
};

class C : public A 
{
	public:
		C() { cout << "C Ctor " << endl; }
		virtual ~C() { cout << "C Dtor " << endl; }
		void p1() { cout << "C : p1" << endl;}
		void p2() { cout << "C : p2" << endl; }
};

class D : public C 
{
	public:
	D() { cout << "D Ctor " << endl; }
	~D() { cout << "D Dtor " << endl; }
	//void p1() { std::cout << "D : p1" << std::endl; }
	void p2() { cout << "D : p2 " << endl; }
};

B b;

int main(int argc, char** argv)
{	
	cout << "main question 1 - start" << endl;
	C* pc = new D;
	A* pa1 = pc;
	A* pa2 = &b;
	
	pa1->p1();
	pa1->p2();
	pa2->p1();
	pa2->p2();
	pc->p1();
	pc->p2();
	
	D d;
	d.p1();
	d.p2();
	
	delete pa1;
	cout << "\n \n main question 1 - end" << endl;
	return 0;
}
