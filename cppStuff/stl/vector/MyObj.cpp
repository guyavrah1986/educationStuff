#include <iostream>
#include "MyObj.h"

using namespace std;

MyObj::MyObj(int a)
	: m_a(a)
{
	cout <<"MyObj::MyObj - setting m_a to:" << m_a << " at address:" << this << endl;
}

MyObj::MyObj()
	: m_a(17)
{
	cout << "MyObj::MyObj(default) - setting m_a to:" << m_a << " at address:" << this << endl;
}

MyObj::MyObj(const MyObj& other)
	: m_a(other.m_a)
{
	cout << "MyObj::MyObj(copy) - setting m_a to:" << m_a << " at address:" << this << endl;
}

MyObj::MyObj(MyObj&& other)
	: m_a(0)
{
	this->m_a = other.m_a;
	cout << "MyObj::(MyObj&&) - setting m_a to:" << m_a << " at address:" << this << endl;
}

MyObj::~MyObj()
{
	cout << "MyObj::~MyObj - m_a:" << m_a << " at address:" << this << endl;
}

MyObj& MyObj::operator=(const MyObj& rhs)
{
	cout << "MyObj::operator=" << endl; 
	if (this == &rhs)
	{
		cout << "MyObj::operator= - self assginment, returnign *this" << endl;
		return *this;
	}

	cout << "setting m_a to:" << rhs.m_a << endl;
	this->m_a = rhs.m_a;
	return *this;
}

