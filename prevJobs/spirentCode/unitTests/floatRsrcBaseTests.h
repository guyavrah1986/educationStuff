#pragma once

#include "memoryLeakDetector/memoryLeakDetectorBase.h"

class CFloatRsrcBaseTests : public MemoryLeakDetectorBase
{
protected:

	CFloatRsrcBaseTests();
	virtual ~CFloatRsrcBaseTests();
	virtual void SetUp();
	virtual void TearDown();
};
