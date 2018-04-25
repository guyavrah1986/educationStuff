#include <iostream>

#include "MyObjsOperators.h"

using namespace std;

ostream& operator<<(ostream& out, const MyObjNoDefualtCtor& obj)
{
	cout << "MyObjNoDefualtCtor (" << &obj << "," << obj.m_a << ")" << endl;
	return out;
}

ostream& operator<<(ostream& out, const MyObj& obj)
{
	cout << "MyObj (" << &obj << "," << obj.m_a << ")" << endl;
	return out;
}
