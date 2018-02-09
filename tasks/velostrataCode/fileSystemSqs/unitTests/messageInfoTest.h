#pragma once

#include "memoryLeakDetector/memoryLeakDetectorBase.h"

class MessageInfoTests : public MemoryLeakDetectorBase
{
protected:

	MessageInfoTests();
	virtual ~MessageInfoTests();
	virtual void SetUp();
	virtual void TearDown();
};
