#include <iostream>
#include <cstring>

#include "floatRsrcBaseTests.h"
#include "../src/rsrc/floatRsrc.h"
#include "mallocAndFreeWrappers.c"

using namespace std;

int g_mallocAndFreeInitialized = 0;

CFloatRsrcBaseTests::CFloatRsrcBaseTests()
{
	cout << "CFloatRsrcBaseTests::CFloatRsrcBaseTests" << endl;
	if (g_mallocAndFreeInitialized == 0)
	{
		cout << "CFloatRsrcBaseTests::CFloatRsrcBaseTests - initializing malloc and free hooks"
				" for unit testing memory leak detection" << endl;
		g_mallocAndFreeInitialized++;
		my_init_hook();
	}
}

CFloatRsrcBaseTests::~CFloatRsrcBaseTests()
{
	cout << "CFloatRsrcBaseTests::~CFloatRsrcBaseTests" << endl;
}

void CFloatRsrcBaseTests::SetUp()
{
	cout << "CFloatRsrcBaseTests::SetUp" << endl;
}

void CFloatRsrcBaseTests::TearDown()
{
	cout << "CFloatRsrcBaseTests::TearDown" << endl;
}

// =====================================================================================================================
// GTests for this class
// =====================================================================================================================
TEST_F(CFloatRsrcBaseTests, createRsrcBaseOnTheStack)
{
	cout << "CFloatRsrcBaseTests::createRsrcBaseOnTheStack - start" << endl;
	const char rsrcUri [] = "floatRsrcName";
	bool internalCreated = false;

	CFloatRsrc floatRsrc(rsrcUri, internalCreated);
	EXPECT_EQ(0, 0);
}

TEST_F(CFloatRsrcBaseTests, sendInvalidPointerToGetValue)
{
	cout << "CFloatRsrcBaseTests::sendInvalidPointerToGetValue" << endl;
	const char rsrcUri [] = "floatRsrcName";
	bool internalCreated = false;
	CFloatRsrc floatRsrc(rsrcUri, internalCreated);

	SpM2mRsrcValue* rsrcVal = nullptr;
	Result res = floatRsrc.AdapGetRsrcValue(rsrcVal);
	EXPECT_EQ(res.IsSuccess(), false);
}

TEST_F(CFloatRsrcBaseTests, verifyProprtGetRsrcVal)
{
	cout << "CFloatRsrcBaseTests::verifyProprtGetRsrcVal" << endl;
	const char rsrcUri [] = "floatRsrcName";
	bool internalCreated = false;
	double initVal = 0.0;
	CFloatRsrc floatRsrc(rsrcUri, internalCreated);

	SpM2mRsrcValue rsrcVal = {};
	rsrcVal.value = new double;
	cout << "CFloatRsrcBaseTests::verifyProprtGetRsrcVal - rsrcVal.value is at address:" << rsrcVal.value << endl;
	Result res = floatRsrc.AdapGetRsrcValue(&rsrcVal);
	EXPECT_EQ(res.IsSuccess(), true);
	EXPECT_EQ(rsrcVal.type, SP_M2M_RSRC_TYPE_FLOAT);
	EXPECT_EQ(*(static_cast<double*>(rsrcVal.value)), initVal);

	delete static_cast<double*>(rsrcVal.value);
}

