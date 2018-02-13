#include <iostream>

#include "cRsrcMgr.h"

using namespace std;

CRsrcMgr::CRsrcMgr()
	: m_rsrcNameToCollectedObjMap()
{
	cout << "CRsrcMgr::CRsrcMgr" << endl;
}

CRsrcMgr::~CRsrcMgr()
{
	cout << "CRsrcMgr::~CRsrcMgr" << endl;
}
