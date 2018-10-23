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
TEST_F(CAdapterMgrTests,addingSingleAdapter)
{
	cout << "CAdapterMgrTests::addingSingleAdapter" << endl;
	SpStatus res = SP_M2M_STATUS_GENERAL_FAUILRE;
	MEM_CHECK_BEFORE_TEST(g_numBytesAllocated);
	{
		CAdapterMgr adapterMgr;
		res = adapterMgr.AddProtocolAdapter(SP_M2M_PROTOCOL_TYPE_LWM2M);
		EXPECT_EQ(res, SP_M2M_STATUS_SUCCESS);
	}
	MEM_CHECK_AFTER_TEST(g_numBytesAllocated);
}

TEST_F(CAdapterMgrTests,addingSameAdapterTwice)
{
	cout << "CAdapterMgrTests::addingSameAdapterTwice" << endl;
	SpStatus res = SP_M2M_STATUS_GENERAL_FAUILRE;
	MEM_CHECK_BEFORE_TEST(g_numBytesAllocated);
	{
		CAdapterMgr adapterMgr;
		res = adapterMgr.AddProtocolAdapter(SP_M2M_PROTOCOL_TYPE_LWM2M);
		EXPECT_EQ(res, SP_M2M_STATUS_SUCCESS);
		res = adapterMgr.AddProtocolAdapter(SP_M2M_PROTOCOL_TYPE_LWM2M);
		EXPECT_EQ(res, SP_M2M_STATUS_SUCCESS);
	}
	MEM_CHECK_AFTER_TEST(g_numBytesAllocated);
}
