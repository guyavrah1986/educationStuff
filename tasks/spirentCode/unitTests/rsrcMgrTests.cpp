#include <iostream>

#include "rsrcMgrTests.h"
#include "../src/cRsrcMgr.h"
#include "../src/floatRsrc.h"

using namespace std;

CRsrcMgrTests::CRsrcMgrTests()
{
	cout << "CRsrcMgrTests::CRsrcMgrTests" << endl;
}

CRsrcMgrTests::~CRsrcMgrTests()
{
	cout << "CRsrcMgrTests::~CRsrcMgrTests" << endl;
}

void CRsrcMgrTests::SetUp()
{
	cout << "CRsrcMgrTests::SetUp" << endl;
}

void CRsrcMgrTests::TearDown()
{
	cout << "CRsrcMgrTests::TearDown" << endl;
}

// =====================================================================================================================
// GTests for this class
// =====================================================================================================================

TEST_F(CRsrcMgrTests, createNULLLwm2mResource)
{
	cout << "CRsrcMgrTests::createEmptyLwm2mResource - start" << endl;
	const char* uri = NULL;
	CRsrcMgr rsrcMgr;

	CFloatRsrc rsrc(NULL, false);
	CRsrcBase* pRsrc = &rsrc;
	Result res = rsrcMgr.CreateRsrc(uri, SP_M2M_RSRC_TYPE_FLOAT, SP_M2M_PROTOCOL_TYPE_LWM2M, false, pRsrc);

	EXPECT_EQ(res.IsSuccess(), false);
}

TEST_F(CRsrcMgrTests, createOneLevelLwm2mResource)
{
	cout << "CRsrcMgrTests::createOneLevelLwm2mResource - start" << endl;
	const char uri [] = "/home";
	CRsrcMgr rsrcMgr;

	CFloatRsrc rsrc(NULL, false);
	CRsrcBase* pRsrc = &rsrc;
	Result res = rsrcMgr.CreateRsrc(uri, SP_M2M_RSRC_TYPE_FLOAT, SP_M2M_PROTOCOL_TYPE_LWM2M, false, pRsrc);

	EXPECT_EQ(res.IsSuccess(), false);
}

TEST_F(CRsrcMgrTests, createTwoLevelLwm2mResource)
{
	cout << "CRsrcMgrTests::createTwoLevelLwm2mResource - start" << endl;
	const char uri [] = "/home/kitchen";
	CRsrcMgr rsrcMgr;

	CFloatRsrc rsrc(NULL, false);
	CRsrcBase* pRsrc = &rsrc;
	Result res = rsrcMgr.CreateRsrc(uri, SP_M2M_RSRC_TYPE_FLOAT, SP_M2M_PROTOCOL_TYPE_LWM2M, false, pRsrc);

	EXPECT_EQ(res.IsSuccess(), false);
}

TEST_F(CRsrcMgrTests, createThreeLevelLwm2mResource)
{
	cout << "CRsrcMgrTests::createThreeLevelLwm2mResource - start" << endl;
	const char uri [] = "/home/kitchen/tmp1";
	CRsrcMgr rsrcMgr;
	const size_t numOfRsrcLevel = 3;

	CFloatRsrc rsrc(NULL, false);
	CRsrcBase* pRsrc = &rsrc;
	Result res = rsrcMgr.CreateRsrc(uri, SP_M2M_RSRC_TYPE_FLOAT, SP_M2M_PROTOCOL_TYPE_LWM2M, false, pRsrc);

	EXPECT_EQ(res.IsSuccess(), true);
	EXPECT_EQ(rsrcMgr.GetRsrcMap().size(), numOfRsrcLevel);
}
