#include <iostream>

#include "statsResolverTests.h"
#include "../../src/include/basicStatsRequestResolver.h"

using namespace std;

StatsResolverTests::StatsResolverTests()
	: m_totalNumOfWordsInDB(13)
{
	cout << "StatsResolverTests::StatsResolverTests" << endl;
}

StatsResolverTests::~StatsResolverTests()
{
	cout << "StatsResolverTests::~StatsResolverTests" << endl;
}

void StatsResolverTests::SetUp()
{
	cout << "StatsResolverTests::SetUp" << endl;
}

void StatsResolverTests::TearDown()
{
	cout << "StatsResolverTests::TearDown" << endl;
}


// =====================================================================================================================
// GTests for this class
// =====================================================================================================================

TEST_F(StatsResolverTests, verifyTotalRequestNumUpdate)
{
	cout << "StatsResolverTests::verifyTotalRequestNumUpdate" << endl;
	BasicStatsRequestResolver statsResolver(m_totalNumOfWordsInDB);

	uint64_t firstReqDuration = 200102;
	uint64_t numOfRequestsDone = 0;
	statsResolver.UpdateStatsUponServingRequest(firstReqDuration);
	++numOfRequestsDone;
	EXPECT_EQ(statsResolver.GetTotalNumOfRequests(), numOfRequestsDone);

	uint64_t secondReqDuration = 257890;
	statsResolver.UpdateStatsUponServingRequest(secondReqDuration);
	++numOfRequestsDone;
	EXPECT_EQ(statsResolver.GetTotalNumOfRequests(), numOfRequestsDone);
	EXPECT_EQ(statsResolver.GetAvgRequestDurationNanoSeconds(), (firstReqDuration + secondReqDuration) / numOfRequestsDone);
}

