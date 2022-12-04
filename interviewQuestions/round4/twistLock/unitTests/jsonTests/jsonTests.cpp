#include <iostream>

#include "gtest/gtest.h"
#include "jsonTests.h"

using namespace std;

JsonTests::JsonTests()
{
	cout << "JsonTests::JsonTests" << endl;
}

JsonTests::~JsonTests()
{
	cout << "JsonTests::~JsonTests" << endl;
}

void JsonTests::SetUp()
{
	cout << "JsonTests::SetUp" << endl;
}

void JsonTests::TearDown()
{
	cout << "JsonTests::TearDown" << endl;
}


// =====================================================================================================================
// GTests for this class
// =====================================================================================================================

TEST_F(JsonTests, createJsonObjectForTheStatsRequest)
{
	cout << "JsonTests::createJsonObject - creating a JSON object on the stack" << endl;
	uint64_t totalWords = 17;
	uint64_t totalRequests = 15;
	int64_t avgProcReqNs = 32465245;
}
