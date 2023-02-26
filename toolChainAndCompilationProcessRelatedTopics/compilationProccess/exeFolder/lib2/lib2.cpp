#include <iostream>

#include "lib2.h"

using namespace std;

CLib2::CLib2(CLib1& lib1Obj) : m_lib1Obj(lib1Obj)
{
	cout << "CLib2::CLib2" << endl;
}

CLib2::~CLib2()
{
	cout << "CLib2::~CLib2" << endl;
}
