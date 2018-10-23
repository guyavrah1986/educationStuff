#include <iostream>

#include "rsrcMgrUnitTests.h"
#include "mallocAndFreeWrappers.c"
#include "../../src/rsrc/cRsrcMgr.h"

using namespace std;

int g_mallocAndFreeInitialized = 0;

CRsrcMgrUnitTests::CRsrcMgrUnitTests()
{
	cout << "CRsrcMgrUnitTests::CRsrcMgrUnitTests" << endl;
	if (g_mallocAndFreeInitialized == 0)
	{
		cout << "CRsrcMgrUnitTests::CRsrcMgrUnitTests - initializing malloc and free hooks"
				" for unit testing memory leak detection" << endl;
		g_mallocAndFreeInitialized++;
		my_init_hook();
	}
}

CRsrcMgrUnitTests::~CRsrcMgrUnitTests()
{
	cout << "CRsrcMgrUnitTests::~CRsrcMgrUnitTests" << endl;
}

void CRsrcMgrUnitTests::SetUp()
{
	cout << "CRsrcMgrUnitTests::SetUp" << endl;
}

void CRsrcMgrUnitTests::TearDown()
{
	cout << "CRsrcMgrUnitTests::TearDown" << endl;
}

// =====================================================================================================================
// GTests for this class
// =====================================================================================================================
TEST_F(CRsrcMgrUnitTests, test)
{
	cout << "CFloatRsrcBaseTests:: - start" << endl;
	CRsrcMgr rsrcMgr;
	EXPECT_EQ(0, 0);
}


