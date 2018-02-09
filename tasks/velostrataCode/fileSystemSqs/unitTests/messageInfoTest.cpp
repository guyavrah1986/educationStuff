#include <iostream>

#include "messageInfoTest.h"

using namespace std;

MessageInfoTests::MessageInfoTests()
{
	cout << "MessageInfoTests::MessageInfoTests" << endl;
}

MessageInfoTests::~MessageInfoTests()
{
	cout << "MessageInfoTests::~MessageInfoTests" << endl;
}

void MessageInfoTests::SetUp()
{
	cout << "MessageInfoTests::SetUp" << endl;
}

void MessageInfoTests::TearDown()
{
	cout << "MessageInfoTests::TearDown" << endl;
}


// =====================================================================================================================
// GTests for this class
// =====================================================================================================================

TEST_F(MessageInfoTests, createMessageInfoOnTheStack)
{
	cout << "MessageInfoTests::createMessageInfoOnTheStack" << endl;

	EXPECT_EQ(1, 1);
}

