// 
//
//
//
//


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


};

int main(int argc, char** argv)
{
	cout << "nameHidingExample - start" << endl;

	
	

	cout << "\n \n nameHidingExample - end" << endl;
	return 0;
}

