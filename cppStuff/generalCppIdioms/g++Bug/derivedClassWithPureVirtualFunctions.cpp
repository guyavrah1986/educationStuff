#include <iostream>

#include "derivedClassWithPureVirtualFunctions.h"

using namespace std;

Derived::Derived()
{
	cout << "Derived::Derived" << endl;
}

Derived::~Derived()
{
	cout << "Derived::~Derived" << endl;
}

void Derived::pureVirtualFunc1()
{
	cout << "Derived::pureVirtualFunc1" << endl;
}

bool Derived::pureVirtualFunc2() const
{
	cout << "Derived::pureVirtualFunc2" << endl;
	return true;
}