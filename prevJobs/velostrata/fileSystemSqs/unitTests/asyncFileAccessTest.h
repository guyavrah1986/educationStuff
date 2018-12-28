#pragma once

#include "asyncFileAccess.h"

#include "memoryLeakDetector/memoryLeakDetectorBase.h"

class AsyncFileAccessTest : public MemoryLeakDetectorBase
{
protected:

	AsyncFileAccessTest();
	virtual ~AsyncFileAccessTest();
	virtual void SetUp();
	virtual void TearDown();

public:

	// tested object
	AsyncFileAccess tested;

	std::string m_workingDir;
	const std::string FILES_FOLDER = "/build/testFiles";
};
