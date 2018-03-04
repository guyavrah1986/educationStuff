#pragma once

#include "memoryLeakDetector/memoryLeakDetectorBase.h"

class CRsrcMgrTests : public MemoryLeakDetectorBase
{
protected:

	CRsrcMgrTests();
	virtual ~CRsrcMgrTests();
	virtual void SetUp();
	virtual void TearDown();
};
