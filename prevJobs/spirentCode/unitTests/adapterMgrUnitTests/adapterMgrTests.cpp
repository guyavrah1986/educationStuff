#include <iostream>

#include "adapterMgrTests.h"
#include "../../src/adapter/adapterMgr.h"
#include "mallocAndFreeWrappers.c"

using namespace std;

int g_mallocAndFreeInitialized = 0;

CAdapterMgrTests::CAdapterMgrTests()
{
	cout << "CAdapterMgrTests::CAdapterMgrTests" << endl;
	if (g_mallocAndFreeInitialized == 0)
	{
		cout << "CAdapterMgrTests::CAdapterMgrTests - initializing malloc and free hooks"
				" for unit testing memory leak detection" << endl;
		g_mallocAndFreeInitialized++;
		my_init_hook();
	}
}

CAdapterMgrTests::~CAdapterMgrTests()
{
	cout << "CAdapterMgrTests::~CAdapterMgrTests" << endl;
}

void CAdapterMgrTests::SetUp()
{
	cout << "CAdapterMgrTests::SetUp" << endl;
}

void CAdapterMgrTests::TearDown()
{
	cout << "CAdapterMgrTests::TearDown" << endl;
}

// =====================================================================================================================
// GTests for this class
// =====================================================================================================================
TEST_F(CAdapterMgrTests,test1)
{
	cout << "CAdapterMgrTests::test1" << endl;
	CAdapterMgr adapterMgr;
}

