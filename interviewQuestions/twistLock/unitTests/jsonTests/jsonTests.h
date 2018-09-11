#pragma once

#include "../memoryLeakDetector/memoryLeakDetectorBase.h"

class JsonTests : public MemoryLeakDetectorBase
{
protected:

	JsonTests();
	virtual ~JsonTests();
	virtual void SetUp();
	virtual void TearDown();
};



