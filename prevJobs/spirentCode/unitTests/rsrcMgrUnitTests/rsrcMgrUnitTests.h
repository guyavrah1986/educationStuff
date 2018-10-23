#pragma once

#include "gtest/gtest.h"

class CRsrcMgrUnitTests :  public ::testing::Test
{
protected:

	CRsrcMgrUnitTests();
	virtual ~CRsrcMgrUnitTests();
	virtual void SetUp();
	virtual void TearDown();
};
