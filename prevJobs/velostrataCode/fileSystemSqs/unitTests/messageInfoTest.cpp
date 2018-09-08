#include <iostream>
#include <cstring>

#include "sqsService.h"
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

	const char buff [] = "sample_buff";
	uint64_t msgId = 17;
	MessageInfo msgInfo(msgId, buff, strlen(buff));

	EXPECT_EQ(msgInfo.msgId, msgId);
	EXPECT_EQ(memcmp(msgInfo.data, buff, strlen(buff)), 0);
}

TEST_F(MessageInfoTests, createMessageInfoOnTheHeap)
{
	cout << "MessageInfoTests::createMessageInfoOnTheHeap" << endl;

	const char buff [] = "sample_buff";
	uint64_t msgId = 17;
	MessageInfo* msgInfo = new MessageInfo(msgId, buff, strlen(buff));

	EXPECT_EQ(msgInfo->msgId, msgId);
	EXPECT_EQ(memcmp(msgInfo->data, buff, strlen(buff)), 0);
	delete msgInfo;
}

