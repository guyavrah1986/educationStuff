#include <iostream>

#include "lib1.h"

using namespace std;

CLib1::CLib1(int a) : m_a(a)
{
	cout << "CLib1::CLib1 - setting m_a to:" << m_a << endl;
}

CLib1::~CLib1()
{
	cout << "CLib1::~CLib1" << endl;
}

void CLib1::func1() const
{
	cout << "CLib1::func1" << endl;
}
