// ===================================================================================================================================================================
// =================================================================================================================================================================== 
//  Name hiding:
// -------------
// In C++ every name (of an object/funciton/enumration) that is defined in some "inner" scope, hides (eliminate) a similar name that exsits in an "outer scope".
// So, here in this example, the fact that Derived class has a function called func1, which is NOT virtual, means that every function with the same name (not 
// entire signature) will be "hiden" --> not visible (we will get a compiler error when trying to call it).
// 
// 1) In this case, everything that needs to be known is known at compile time so the Derived's object func() will be invoked (also note that, no virtual "late
//    binding" takes place here).
// 2) Due to the fact that func1() is NOT virtual in the Base calss, then when pointing on any kind of object, i.e. - Base/Dervied with a Base*, all that we can "see"
//    is the Base section - so the func1() of Base will be called.
// 3) For virtual methods, namehiding does NOT apply.
//
// ===================================================================================================================================================================
// =================================================================================================================================================================== 
#include <iostream>

using namespace std;

class Base
{
public:
	Base() 
	{
		cout << "Base::Base" << endl;
	}

	virtual ~Base() 
	{
		cout << "Base::~Base" << endl;
	}

	void func1()
	{
		cout << "Base::func1()" << endl;
	}

	void func1(int i)
	{
		cout << "Base::func1(int) - got:" << i << endl;
	}
	
	virtual void func2(int i)
	{
		cout << "Base::func2(int) - got:" << i << endl;
	}
};

class Derived : public Base
{
public:
	Derived()
	{
		cout << "Derived::Derived" << endl;
	}

	virtual ~Derived()
	{
		cout << "Derived::Derived" << endl;
	}

	void func1()
	{
		cout << "Derived::func1()" << endl;
	}
	
	virtual void func2(int i)
	{
		cout << "Derived::func2(int) - got:" << i << endl;
	}
};

int main(int argc, char** argv)
{
	cout << "main - start" << endl;
	cout << "main - creating Derived object on the stack" << endl;
	Derived d;
	Base* bp = &d;

	cout << "main - calling func1 with a derived object" << endl;
	d.func1(); // 1)

	cout << "main - calling func1 with a derived object pointed by a Base pointer" << endl;
	bp->func1(); // 2)

	// Uncomment in order to see the compilation error.
	// trying to call the func1(int) version of the Base class won't work -- cause it is being hidden by the func1(void) of 
	// the Derived class. 
	//d.func1(16);
	
	cout << "main - calling func2(int) with a derived object" << endl;
	d.func2(17); //3)
	cout << "main - calling func2(int) for a derived object pointed by Base class pointer" << endl;
	bp->func2(18);// 3)
	cout << "\n \n nameHidingExample - end" << endl;
	return 0;
}

