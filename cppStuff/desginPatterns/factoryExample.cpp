#include <iostream>

using namespace std;

class Base
{
	virtual void foo() = 0;
	static Base* CreateInstance(int type);
};

Base* Base::CreateInstance(int type)
{
	switch(type)
	{
	case 1: return new Dervied1();
		
	case 2: return new Dervied2();

	case 3: return new Dervied3();

	default: return nullptr;
	}
}

class Dervied1 : public Base
{
	Dervied1() 
	{
		cout << "Dervied1::Dervied1" << endl;
	}

	virtual ~Dervied1()
	{
		cout << "Dervied1::~Dervied1" << endl;
	}

	virtual void foo() 
	{
		cout << "Dervied1::foo" << endl;
	}

};

class Dervied2 : public Base
{
	Dervied2() 
	{
		cout << "Dervied2::Dervied2" << endl;
	}

	virtual ~Dervied2()
	{
		cout << "Dervied2::~Dervied2" << endl;
	}

	virtual void foo() 
	{
		cout << "Dervied2::foo" << endl;
	}

};

class Dervied3 : public Base
{
	Dervied3() 
	{
		cout << "Dervied3::Dervied3" << endl;
	}

	virtual ~Dervied3()
	{
		cout << "Dervied3::~Dervied3" << endl;
	}

	virtual void foo() 
	{
		cout << "Dervied3::foo" << endl;
	}

};


// =============================================================================================================================
// =============================================================================================================================

int main(int argc, char** argv)
{	
	cout << "main - start" << endl;

	cout << "main - end" << endl;
	return 0;
}
