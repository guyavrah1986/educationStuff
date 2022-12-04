#pragma once

#include "../memoryLeakDetector/memoryLeakDetectorBase.h"

class StatsResolverTests : public ::testing::Test
{
protected:

	StatsResolverTests();
	virtual ~StatsResolverTests();
	virtual void SetUp();
	virtual void TearDown();

public:
	size_t m_totalNumOfWordsInDB;

};
