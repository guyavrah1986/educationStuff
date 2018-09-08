#pragma once

#include "memoryLeakDetector/memoryLeakDetectorBase.h"

class CRsrcMgrTests : public ::testing::Test
{
protected:

	CRsrcMgrTests();
	virtual ~CRsrcMgrTests();
	virtual void SetUp();
	virtual void TearDown();
};
