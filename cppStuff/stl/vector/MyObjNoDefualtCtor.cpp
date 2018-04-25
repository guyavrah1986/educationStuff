#include <iostream>

#include "MyObjNoDefualtCtor.h"

using namespace std;

MyObjNoDefualtCtor::MyObjNoDefualtCtor(int a)
	: m_a(a)
{
	cout << "MyObjNoDefualtCtor::MyObjNoDefualtCtor - setting m_a to:" << m_a << " at address:" << this << endl;
}

MyObjNoDefualtCtor::MyObjNoDefualtCtor(const MyObjNoDefualtCtor& other)
	: m_a(other.m_a)
{
	cout << "MyObjNoDefualtCtor::copy_ctor - setting m_a to:" << m_a << " at address:" << this << endl;
}

MyObjNoDefualtCtor::~MyObjNoDefualtCtor()
{
	cout << "MyObjNoDefualtCtor::~MyObjNoDefualtCtor -  m_a to:" << m_a << " at address:" << this << endl;
}

