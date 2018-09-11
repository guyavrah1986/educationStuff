#pragma once

#include "../memoryLeakDetector/memoryLeakDetectorBase.h"

class RequestsNavigatorTests : public ::testing::Test
{
protected:

	RequestsNavigatorTests();
	virtual ~RequestsNavigatorTests();
	virtual void SetUp();
	virtual void TearDown();

public:
	const std::string m_apiPrefix = "/api/v1/";
};
