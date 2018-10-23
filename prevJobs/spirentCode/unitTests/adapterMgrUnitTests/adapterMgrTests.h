#pragma once

#include "gtest/gtest.h"

class CAdapterMgrTests :  public ::testing::Test
{
protected:

	CAdapterMgrTests();
	virtual ~CAdapterMgrTests();
	virtual void SetUp();
	virtual void TearDown();
};
