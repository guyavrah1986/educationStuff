/*
* What will be the output of the program ?
*/
#include <iostream>

class A 
{
	
	public:
		A() { std::cout << "A Ctor " << std::endl; }
		~A() { std::cout << "A Dtor " << std::endl; }
		
		void p1() { std::cout << "A : p1 " << std::endl; }
		virtual void p2() { std::cout << "A : p2 " << std::endl; }
};

class B : public A 
{
	public:	
		B() { std::cout << "B Ctor " << std::endl; }
		~B() { std::cout << "B Dtor " << std::endl; }
		void p1 () { std::cout << "B : p1 " << std::endl;}
		void p2() { std::cout << "B : p2 " << std::endl; }
};

class C : public A 
{
	public:
		C() { std::cout << "C Ctor " << std::endl; }
		virtual ~C() { std::cout << "C Dtor " << std::endl; }
		void p1() { std::cout << "C : p1" << std::endl;}
		void p2() { std::cout << "C : p2" << std::endl; }
};

class D : public C 
{
	public:
	D() { std::cout << "D Ctor " << std::endl; }
	~D() { std::cout << "D Dtor " << std::endl; }
	void p1() { std::cout << "D : p1" << std::endl; }
	void p2() { std::cout << "D : p2 " << std::endl; }
};

B b;

void q1()
{
	std::cout << "q1 - start" << std::endl;
	C* pc = new D;
	A* pa1 = pc;
	A* pa2 = &b;
	
	pa1->p1();
	pa1->p2();
	pa2->p1();
	pa2->p2();
	
	D d;
	d.p1();
	d.p2();
	
	delete pa1;
	std::cout << "\n \n q1 - end" <<std::endl;
}
