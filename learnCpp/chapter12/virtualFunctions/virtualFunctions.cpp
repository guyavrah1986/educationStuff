// ===================================================================================================================================================================
// ===================================================================================================================================================================
// NOTE: Compile the program with the following line:
// g++ -g -O0 -c -fverbose-asm -Wa,-adhln virtualfunctions.cpp > test.lst
//
/*
  38              	# virtualFunctions.cpp:47: 	explicit A(int a) : m_a(a)  // GuyA: This is the "extra" class member that the ctor initialized during the ctor
  40 0013 488D1500 		leaq	16+_ZTV1A(%rip), %rdx	#, _1		    //        initialization list --> the virtual pointer (=_vptr).
  41 001a 488B45F8 		movq	-8(%rbp), %rax	# this, tmp89
  42 001e 488910   		movq	%rdx, (%rax)	# _1, this_9(D)->_vptr.A
*/
//
// Virtual functions:
// -----------------
// This file comes to include some more information about the behaviour of the virtual functions mechanism in C++. 
// In this example a "3-levels" inheritence chain will be used to illustrate the way it works.
// 
// 1) Calling a pure virtual function from within a CTOR will most likely cause a compiler/linker error.
// 2) Calling a pure virtual function from some function (not the ctor) is OK, cause eventually, the actuall object (at run-time after it was instancisated) that will call the
//    the "encapsulating function" will be called by an object that DOES implement the pure virtual funcntion (otherwise it could not have
//    been instanicated).   
// 3) Whether we call a virtual function via Base class pointer OR reference, automatically we "invoke" the virtual functions mechanism (i.e. - method reolution order).
//    Meaning, if the function that is called, again, via the pointer OR reference is virtual, then the MOST derived version of it will 
//    be (eventually) invoked (dynamic binding).
// 4) In this case it is even "simpler" than the previous case - the most derived flavor of the function will be invoked. 
//    NOTE: A distincation from the previous note is that in this case the reolution of the function to be called is known at compile time
//    which means that it will take less cycels to execute this function (early binding).
// 5) In this case, it is quite stragiht forward - there is no "precesne" of virtual functions what so ever, it is simply a call to a "noraml"
//    class member function.Note however, that the phenomen of "Name hiding" is taking place here, causing the B::Func4() to be invoked and not
//    the A::Func4().
// 6) When calling a non virtual function via a pointer OR reference of any type of class along the inheritence chain - "Name hiding" takes
//    place as well, so the function that will be invoked is the one of the B class.
// 7) Calling a virtual function from the ctor of some base class, will invoke the most derived virtual function SO FAR during the creation of the object.
//    For example, assume that a C object is created. At the time the A part of it is constructed, the "most derived version" of Func2 is the one that A implements.
//    So in this case, it is the function that will be called. This is "enforced" by the fact that each compiler addds implictly, to the class members initialization
//    list, an initialization to the vptr of the instance that is being created. So, during the creation of the A part of a C object, the vptr of the C instance, is
//    set to (temporary) A's v-table --> so Func2 of A will be invoked. 
//    Note, however, that the virtual table itself, of any object (i.e. - A, B, C) is created ONCE for every object during COMPILATION.
// 8) Same goes for the "destruction flow" of an object. Say a C object is being deleted. by the time it will arrive to the A dtor, the "only version" that A knows
//    for Func2 is the one it has.
// 9) In this case, during the destruction of B, the "most derived" version of Func1 is the one that B implemented, so this is what will be invoked.
//10) Note that for every NON-STATIC member function of a class, when invoked, an implict "argument 0" is sent, which is the "this" pointer is sent also. Thus, when
//    for example, invoking the Func4 for a C object, the this pointer that is passed to B::Func4 will cause C::Func1 to be invoked.
//
// ===================================================================================================================================================================
// ===================================================================================================================================================================
#include <iostream>

using namespace std;

class A
{
public:
	explicit A(int a) : m_a(a)
	{
		cout << "A::A" << endl;
		//Func3();	// 1)
		Func2();	// 7) 
		cout << "A::A - set m_a to:" << m_a << ", this:" << this << endl;
	}

	virtual ~A()
	{
		cout << "A::~A" << endl;
		Func2();	// 8)
		cout << "A::~A - this:" << this << endl;
	}

	virtual void Func1()
	{
		cout << "A::Func1 - this:" << this << endl;
		Func3();	// 2)
	}

	virtual void Func2()
	{
		cout << "A::Func2 - this:" << this << endl;
	}

	virtual void Func3() = 0;
	
	virtual void Func4()
	{
		cout << "A::Func4 - this:" << this << endl;
	}

protected:
	int m_a;
};

class B : public A
{
public:
	B(int a, int b) : A(a), m_b(b)
	{
		cout << "B::B" << endl;
		Func1();
		Func4();
		cout << "B::B - set m_b to:" << m_b << ", this:" << this << endl;
	}

	virtual ~B()
	{
		cout << "B::~B" << endl;
		Func1(); 	// 9)
		cout << "B::~B - this:" << this << endl;
	}

	virtual void Func1()
	{
		cout << "B::Func1 - this:" << this << endl;
	}

	/*
	virtual void Func2()
	{
		cout << "B::Func2 - this:" << this << endl;
	}
	*/

	virtual void Func3()
	{
		cout << "B::Func3 - this:" << this << endl;
	}
	
	void Func4()
	{
		cout << "B::Func4 - this:" << this << endl;
		Func1();	// 10)
	}	

protected:
	int m_b;
};

class C : public B
{
public:
		C(int a, int b, int c) : B(a,b), m_c(c)
		{
			cout << "C::C - set m_c to:" << m_c << ", this is at:" << this << endl;
		}
			
		virtual ~C()
		{
			cout << "C::~C" << endl;
		}
		
		virtual void Func1()
		{
			cout << "C::Func1 - this:" << this << endl;
		}

		virtual void Func2()
		{
			cout << "C::Func2 - this:" << this << endl;
		}
		
		virtual void Func3()
		{
			cout << "C::Func3 - this:" << this << endl;
		}
		
		/*
		void Func4()
		{
			cout << "C::Func4 - this:" << this << endl;
		}
		*/

		int m_c;
};

// ===================================================================================================================================================================
// ===================================================================================================================================================================
// main program:
// ===================================================================================================================================================================
// ===================================================================================================================================================================

/*
void callVirtualFunctionWithPointerOrReferenceOfBaseClasses()	// 3)
{
	cout << "callVirtualFunctionWithPointerOrReferenceOfBaseClasses - start" << endl;
	C c(1,2,3);
	A* pa = &c;
	A& ra = c;
	B* pb = &c;
	B& rb = c;
	C* pc = &c;
	C& rc = c;
	
	cout << "-------------------------------------------------------------------------------------------" << endl;
	cout << "-------------------------------------------------------------------------------------------" << endl;
	cout << "callVirtualFunctionWithPointerOrReferenceOfBaseClasses - calling all virtual functions via pointer and ref of type A" << endl;
	cout << "callVirtualFunctionWithPointerOrReferenceOfBaseClasses - calling pa->Func1()" << endl;
	pa->Func1();
	cout << "callVirtualFunctionWithPointerOrReferenceOfBaseClasses - calling ra.Func1()" << endl;
	ra.Func1();
	
	cout << "callVirtualFunctionWithPointerOrReferenceOfBaseClasses - calling pa->Func2()" << endl;
	pa->Func2();
	cout << "callVirtualFunctionWithPointerOrReferenceOfBaseClasses - calling ra.Func2()" << endl;
	ra.Func2();
	
	cout << "callVirtualFunctionWithPointerOrReferenceOfBaseClasses - calling pa->Func3()" << endl;
	pa->Func3();
	cout << "callVirtualFunctionWithPointerOrReferenceOfBaseClasses - calling ra.Func3()" << endl;
	ra.Func3();
	cout << "-------------------------------------------------------------------------------------------" << endl;
	cout << "-------------------------------------------------------------------------------------------" << endl;
	
	cout << "-------------------------------------------------------------------------------------------" << endl;
	cout << "-------------------------------------------------------------------------------------------" << endl;
	cout << "callVirtualFunctionWithPointerOrReferenceOfBaseClasses - calling all virtual functions via pointer and ref of type B" << endl;
	cout << "callVirtualFunctionWithPointerOrReferenceOfBaseClasses - calling pb->Func1()" << endl;
	pb->Func1();
	cout << "callVirtualFunctionWithPointerOrReferenceOfBaseClasses - calling rb.Func1()" << endl;
	rb.Func1();
	
	cout << "callVirtualFunctionWithPointerOrReferenceOfBaseClasses - calling pb->Func2()" << endl;
	pb->Func2();
	cout << "callVirtualFunctionWithPointerOrReferenceOfBaseClasses - calling rb.Func2()" << endl;
	rb.Func2();
	
	cout << "callVirtualFunctionWithPointerOrReferenceOfBaseClasses - calling pb->Func3()" << endl;
	pb->Func3();
	cout << "callVirtualFunctionWithPointerOrReferenceOfBaseClasses - calling rb.Func3()" << endl;
	rb.Func3();
	cout << "-------------------------------------------------------------------------------------------" << endl;
	cout << "-------------------------------------------------------------------------------------------" << endl;
	
	cout << "-------------------------------------------------------------------------------------------" << endl;
	cout << "-------------------------------------------------------------------------------------------" << endl;
	cout << "callVirtualFunctionWithPointerOrReferenceOfBaseClasses - calling all virtual functions via pointer and ref of type C" << endl;
	cout << "callVirtualFunctionWithPointerOrReferenceOfBaseClasses - calling pc->Func1()" << endl;
	pc->Func1();
	cout << "callVirtualFunctionWithPointerOrReferenceOfBaseClasses - calling rc.Func1()" << endl;
	rc.Func1();
	
	cout << "callVirtualFunctionWithPointerOrReferenceOfBaseClasses - calling pc->Func2()" << endl;
	pc->Func2();
	cout << "callVirtualFunctionWithPointerOrReferenceOfBaseClasses - calling rc.Func2()" << endl;
	rc.Func2();
	
	cout << "callVirtualFunctionWithPointerOrReferenceOfBaseClasses - calling pc->Func3()" << endl;
	pc->Func3();
	cout << "callVirtualFunctionWithPointerOrReferenceOfBaseClasses - calling rc.Func3()" << endl;
	rc.Func3();
	cout << "-------------------------------------------------------------------------------------------" << endl;
	cout << "-------------------------------------------------------------------------------------------" << endl;
	
	cout << "callVirtualFunctionWithPointerOrReferenceOfBaseClasses - end" << endl;
}

void callVirtualFunctionDirectlyViaDerivedObject()	// 4)
{
	cout << "callVirtualFunctionDirectlyViaDerivedObject - start" << endl;
	C c(4,5,6);
	cout << "callVirtualFunctionDirectlyViaDerivedObject - calling c.Func1()" << endl;
	c.Func1();
	cout << "callVirtualFunctionDirectlyViaDerivedObject - calling c.Func2()" << endl;
	c.Func2();
	cout << "callVirtualFunctionDirectlyViaDerivedObject - calling c.Func3()" << endl;
	c.Func3();
	cout << "callVirtualFunctionDirectlyViaDerivedObject - end" << endl;
}

void callNonVirtualFunctionDirectlyViaDerivedObject()	// 5)
{
	cout << "callNonVirtualFunctionDirectlyViaDerivedObject - start" << endl;
	C c(7,8,9);
	cout << "callNonVirtualFunctionDirectlyViaDerivedObject - calling c.Func4()" << endl;
	c.Func4();
	cout << "callNonVirtualFunctionDirectlyViaDerivedObject - end" << endl;
}
*/
void testFuntion()
{
	C c(1,2,3);
	A* pa = &c;
	A& ra = c;
	B* pb = &c;
	B& rb = c;
	C* pc = &c;
	C& rc = c;

	// Func1 invocations
	cout << "\n \n \n \n testFuntion - calling pa.Func1()" << endl;
	pa->Func1();
	cout << "testFuntion - calling ra.Func1()" << endl;
	ra.Func1();
	cout << "testFuntion - calling pb.Func1()" << endl;
	pb->Func1();
	cout << "testFuntion - calling rb.Func1()" << endl;
	rb.Func1();
	cout << "testFuntion - calling cb.Func1()" << endl;
	pc->Func1();
	cout << "testFuntion - calling rc.Func1()" << endl;
	rc.Func1();
	cout << "testFuntion - calling c.Func1()" << endl;
	c.Func1();
	
	// Func2 invocations
	cout << "testFuntion - calling c.Func2()" << endl;
	c.Func2();
	
	// Func3 invocations
	cout << "testFuntion - calling c.Func3()" << endl;
	c.Func3();

	// Func4 invocations 		// 6)
	cout << "testFuntion - calling pa->Func4()" << endl;
	pa->Func4();
	cout << "testFuntion - calling pb->Func4()" << endl;
	pb->Func4();
	cout << "testFuntion - calling pc->Func4()" << endl;
	pc->Func4();
	cout << "testFuntion - calling c.Func4()" << endl;
	c.Func4();	
}

int main(int argc, char** argv)
{
	cout << "main - start" << endl;
	/*
	callVirtualFunctionWithPointerOrReferenceOfBaseClasses();
	callVirtualFunctionDirectlyViaDerivedObject();
	callNonVirtualFunctionDirectlyViaDerivedObject();
	callNonVirtualFunctionViaPointerOrReference();
	*/
	testFuntion();
	cout << "main - end" << endl;
	return 0;
}

