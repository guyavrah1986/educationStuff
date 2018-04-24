// ========================================================================================================================================================================
/*
* Item 24:
* --------
* Virtual functions is a mechanism to implement inheritence.
* 1) All virtual functions of a class have a corresponding entry in the v-table of that class's v-table.
* a) Non virtual functions, DOES NOT have these entries. 
* 2) The size of each class that has a v-table increases by pointer size (4/8 bytes) due to the "penalty" of the vptr.
* 3) The "most derived class" wont add its "own" vptr - so its total size will be:
*    the size of her parents data members + the size of its own data members + the vptr's of all its parents.
* 4) When invoking a VIRTUAL function via a Base's class pointer, "all" it takes (extra) is two offset calculation + one 
*    pointer indirection to "reach" the desired function pointer in the class v-table. 
*    NOTE: Usually, this is NOT a big concern "run time wise".
* 5) In addition to the vptrs & v-tables, another "entry" we can add to each class v-table (!!) is an entry for a RTTI
*    information so we can figure out information about a certain object during run time.
*    Again, the "only" cost we pay, is an additional entry in the v-table (once per class) and the type_info object per object.
* 
* !! @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ !!
* !! @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ !!
* Key notes:
* 1) Each class that has at least one virtual function (either her's OR of its "parents") - will have a Virtual Table (vtbl).
*    The size of the v-table is according to the number of virtual functions it has multiple by pointer size.
* 2) Each object (instance) of a class with at least one virtual function, will have an additional "class data member" which is
*    the virtual-pointer (points to the first entry in the v-table).
* 3) The real cost of virtual functions regarding "run time" overhead - is the fact that virtual function, WHEN CALLED VIA 
*    REFERENCES OR POINTERS (NOT OBJECTS), can not be INLINED !!
* 4) For summary, it is important to understand these features, but more important, is to understand their overhead.
* 
* !! @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ !!
* !! @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ !!
*
*/
// ======================================================================================================================================================================

#include <iostream>
#include <typeinfo>

using namespace std;

class Base1
{
public:
	Base1(int b1)
		: m_b1(b1)
	{
		cout << "Base1::Base1 - setting m_b1 to:" << m_b1 << " at address:" << this << endl;
	}

	Base1()
		: m_b1(0)
	{
		cout << "Base1::Base1(default) - setting m_b1 to:" << m_b1 << " at address:" << this << endl;
	}

	virtual ~Base1()
	{
		cout << "Base1::~Base1 - m_b1:" << m_b1 << " at address:" << this << endl;
	}

	virtual void f1()
	{
		cout << "Base1::f1" << endl;
	}

	void f2()	// 1a)
	{
		cout << "Base1::f2" << endl;
	}

	int m_b1;
};

class Base2 : public Base1
{
public:
	Base2(int b1, int b2)
		: Base1(b1)
		, m_b2(b2)
	{
		cout << "Base2::Base2 - setting m_b2 to:" << m_b2 << " at address:" << this << endl;
	}

	Base2()
		: m_b2(0)
	{
		cout << "Base2::Base2(default) - setting m_b2 to:" << m_b2 << " at address:" << this << endl;
	}

	virtual ~Base2()
	{
		cout << "Base2::~Base2 - m_b2:" << m_b2 << " at address:" << this << endl;
	}

	virtual void f1()
	{
		cout << "Base2::f2" << endl;
	}

	virtual void f3()
	{
		cout << "Base2::f3" << endl;
	}

	int m_b2;
};

class Derived : public Base2
{
public:
	Derived(int b1, int b2, int d)
		: Base2(b1, b2)
		, m_d(d)
	{
		cout << "Derived::Derived - setting m_d to:" << m_d << " at address:" << this << endl;
	}

	Derived()
		: m_d(0)
	{
		cout << "Derived::Derived(default) - setting m_d to:" << m_d << " at address:" << this << endl;
	}

	virtual ~Derived()
	{
		cout << "Derived::Derived - m_d :" << m_d << " at address:" << this << endl;
	}

	virtual void f1()
	{
		cout << "Derived::f1" << endl;
	}

	virtual void f2()
	{
		cout << "Derived::f2" << endl;
	}

	virtual void f3()
	{
		cout << "Derived::f3" << endl;
	}

	int m_d;
};

void checkClassesSize()
{
	cout << "checkClassesSize - size of Base1 is:" << sizeof(Base1) << " size of Base2 is:" << sizeof(Base2) << endl;	// 2)
	cout << "checkClassesSize size of Derived is:" << sizeof(Derived) << endl;	// 3) 
}

void makeACall(Base1* pb1)	// 4)
{
	cout << "makeACall" << endl;
	pb1->f1();
	/*
	(*pC1->vptr[i])(pC1); 
	call the function pointed to by the
	i-th entry in the vtbl pointed to
	by pC1->vptr; pC1 is passed to the
	function as the "this" pointer			  
	*/
}

void illustrateRTTI()	// 5)
{
	cout << "\n \n illustrateRTTI - start" << endl;
	Base2 b2;
	const type_info& typeInfo = typeid(Base2);
	cout << "illustrateRTTI - typeInfo.name for Base2 is:" << typeInfo.name() << endl;
}

void item24Usage()
{
	cout << "item24Usage - start" << endl;
	checkClassesSize();
	Derived d;
	makeACall(&d);
	illustrateRTTI();

	cout << "\n \n item24Usage - end" << endl;
}

int main(int argc, char** argv)
{
	cout << "main - start" << endl;
	item24Usage();
	
	char c;
	cout << "\n \n main - enter any key and press ENTER to terminate" << endl;
	cin >> c;
	return 0;
}
