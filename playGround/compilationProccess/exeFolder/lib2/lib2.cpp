#include "stdafx.h"

#include "lib2.h"

#include <iostream>

using namespace std;

CLib2::CLib2(const CLib1& lib1Obj)
	: m_clib1Obj(lib1Obj)
{
	cout << "CLib2::CLib2" << m_a << endl;
}

CLib2::~CLib2()
{
	cout << "CLib2::~CLib2" << endl;
}
