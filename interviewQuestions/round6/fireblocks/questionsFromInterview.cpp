// ====================================================================================================================
// Question that raised to this code block:
// 1) Due to the fact that there is no virtual in the base class (A) constructor, when 
//    a B ojbect that is pointed via A pointer is deleted, only the "A part" of the 
//    destructor chain is invoked.
// 2) This will compile, but in C++ it is very bad practice - to use C style cast.
// 3) If you uncomment this, a compiler error will raise cause without explictly indicating to the compiler that the 
//    object being pointed is a D object, it is NOT aware that the pointed object even has a function g1 --> cause it
//    is pointed by A8 pointer.
//
// ====================================================================================================================

#include <iostream>

using namespace std;

class A
{
public:
	A()
	{ 
		a = 1;
		cout << "A::A" << endl;
	}

	~A() { cout << "A::~A" << endl; } // 1)

	virtual void f1()
	{ 
		cout << "A::f1()" << endl; 
	}

	virtual void f2()
	{ 
		cout << "A::f2()" << endl; 
	}

	int a;
};

class B : public A
{
public:
	B()
	{ 
		b = 2;
		cout << "B::B" << endl;
	}

	~B() { cout << "B::~B" << endl; }

	virtual void f1()
	{ 
		cout << "B::f1 - a is:" << a << endl;
	}

	int b;
};

class C
{
public:
	C()
	{ 
		c = 3;
		cout << "C::C" << endl;
	}

	~C() { cout << "C::~C" << endl; }
	virtual void f1() { cout << "C::g1" << endl; }

	int c;
};

class D : public B,C
{
public:
	D()
	{
		cout << "D::D" << endl;
		d = 4;
	}

	~D()
	{
		cout << "D::~D" << endl;
	}

	virtual void g1() { cout << "D::g1" << endl; }

	int d;
};


int main(int argc, char** argv)
{

	cout << "main - start" << endl;
	
	cout << "main - creating A on the stack" << endl;
	A a;
	A* pa;
	cout << "main - creating B on the stack" << endl;
	B b;
	cout << "main - pointing to the B object with an A* via C style cast" << endl;
	pa = (A*)&b;
	cout << "main - calling the f1() function of the B object via the A*" << endl;
	pa->f1();
	
	cout << "main - creating C on the stack" << endl;	
	C c;
	A* pc = (A*)&c;
	cout << "main - calling the (non existing) f1() function of the C object which is pointed by A*" << endl;
	pc->f1();

	cout << "main - calling the (non existing) f2() function of the C object which is pointed by A*" << endl;
	pc->f2();
	
	cout << "main - creating D on the stack" << endl;
	D d;
	A* pd1 = (A*)&d;	// 2)
	//pd->g1();		// 3) 
	D* pd2 = dynamic_cast<D*>(pd1);
    	if (nullptr != pd2)
	{
		cout << "main - calling the g1() function of the D object via the A*" << endl;
	        pd2->g1();
	}

	cout << "main - end" << endl;
	return 0;
}



