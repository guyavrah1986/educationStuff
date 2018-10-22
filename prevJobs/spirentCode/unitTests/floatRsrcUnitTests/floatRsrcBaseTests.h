#pragma once

#include "gtest/gtest.h"

class CFloatRsrcBaseTests :  public ::testing::Test
{
protected:

	CFloatRsrcBaseTests();
	virtual ~CFloatRsrcBaseTests();
	virtual void SetUp();
	virtual void TearDown();
};
