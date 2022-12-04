#include <iostream>

#include "requestNavigatorTests.h"
#include "../../src/include/basicRequestNavigator.h"

using namespace std;

RequestsNavigatorTests::RequestsNavigatorTests()
{
	cout << "RequestsNavigatorTests::RequestsNavigatorTests" << endl;
}

RequestsNavigatorTests::~RequestsNavigatorTests()
{
	cout << "RequestsNavigatorTests::~RequestsNavigatorTests" << endl;
}

void RequestsNavigatorTests::SetUp()
{
	cout << "RequestsNavigatorTests::SetUp" << endl;
}

void RequestsNavigatorTests::TearDown()
{
	cout << "RequestsNavigatorTests::TearDown" << endl;
}


// =====================================================================================================================
// GTests for this class
// =====================================================================================================================


TEST_F(RequestsNavigatorTests, handleEmptyURIAndEmptyQuery)
{
	cout << "RequestsNavigatorTests::handleEmptyURIAndEmptyQuery" << endl;
	BasicRequestNavigator reqNavigator(m_apiPrefix);

	const string emptyUri = "";
	const string emptyQuery = "";
	string extractedWord;
	RequestType type = reqNavigator.GetRequestTypeFromURI(emptyUri, emptyQuery, extractedWord);
	EXPECT_EQ(type, RequestType::TS_REQUEST_TYPE_UNKNOWN);
	EXPECT_EQ(extractedWord.length(), 0);
}


TEST_F(RequestsNavigatorTests, handleNotCompleteStatsURIPrefixWithoutQuery)
{
	cout << "RequestsNavigatorTests::handleNotCompleteStatsURIPrefixWithoutQuery" << endl;
	BasicRequestNavigator reqNavigator(m_apiPrefix);

	const string notEntireApiPrefixStr = "/api/v1";	// NOTE: missing terminating / after the v1
	const string emptyQuery = "";
	string extractedWord;
	RequestType type = reqNavigator.GetRequestTypeFromURI(notEntireApiPrefixStr, emptyQuery, extractedWord);
	EXPECT_EQ(type, RequestType::TS_REQUEST_TYPE_UNKNOWN);
	EXPECT_EQ(extractedWord.length(), 0);
}


TEST_F(RequestsNavigatorTests, handleCompleteURIPrefixWithNoFurtherCharacters)
{
	cout << "RequestsNavigatorTests::handleCompleteURIPrefixWithNoFurtherCharacters" << endl;
	BasicRequestNavigator reqNavigator(m_apiPrefix);

	const string notEntireApiPrefixStr = "/api/v1/";
	const string emptyQuery = "";
	string extractedWord;
	RequestType type = reqNavigator.GetRequestTypeFromURI(notEntireApiPrefixStr, emptyQuery, extractedWord);
	EXPECT_EQ(type, RequestType::TS_REQUEST_TYPE_UNKNOWN);
	EXPECT_EQ(extractedWord.length(), 0);
}


TEST_F(RequestsNavigatorTests, handleCorrectStatsRequest)
{
	cout << "RequestsNavigatorTests::handleCorrectStatsRequest" << endl;
	BasicRequestNavigator reqNavigator(m_apiPrefix);

	const string statsRequestURI = "/api/v1/stats";
	const string emptyQuery = "";
	string extractedWord;
	RequestType type = reqNavigator.GetRequestTypeFromURI(statsRequestURI, emptyQuery, extractedWord);
	EXPECT_EQ(type, RequestType::TS_REQUEST_TYPE_STATS);
	EXPECT_EQ(extractedWord.length(), 0);
}


TEST_F(RequestsNavigatorTests, handleCorrectStatsRequestWithMoreCharacters)
{
	cout << "RequestsNavigatorTests::handleCorrectStatsRequestWithMoreCharacters" << endl;
	BasicRequestNavigator reqNavigator(m_apiPrefix);

	const string statsRequestURI = "/api/v1/stats more chars";
	const string emptyQuery = "";
	string extractedWord;
	RequestType type = reqNavigator.GetRequestTypeFromURI(statsRequestURI, emptyQuery, extractedWord);
	EXPECT_EQ(type, RequestType::TS_REQUEST_TYPE_UNKNOWN);
	EXPECT_EQ(extractedWord.length(), 0);
}

TEST_F(RequestsNavigatorTests, handleCorrectStatsRequestWithInvalidApiPrefix)
{
	cout << "RequestsNavigatorTests::handleCorrectStatsRequestWithInvalidApiPrefix" << endl;
	BasicRequestNavigator reqNavigator(m_apiPrefix);

	const string statsRequestURI = "/pi/v1/stats";
	const string emptyQuery = "";
	string extractedWord;
	RequestType type = reqNavigator.GetRequestTypeFromURI(statsRequestURI, emptyQuery, extractedWord);
	EXPECT_EQ(type, RequestType::TS_REQUEST_TYPE_UNKNOWN);
	EXPECT_EQ(extractedWord.length(), 0);
}


TEST_F(RequestsNavigatorTests, handleStatsRequestWithSingleCharDefected)
{
	cout << "RequestsNavigatorTests::handleStatsRequestWithSingleCharDefected" << endl;
	BasicRequestNavigator reqNavigator(m_apiPrefix);

	const string statsRequestURIWithOneMoreChar = "/api/v1/stwts";	// NOTE: the fault w character !!
	const string emptyQuery = "";
	string extractedWord;
	RequestType type = reqNavigator.GetRequestTypeFromURI(statsRequestURIWithOneMoreChar, emptyQuery, extractedWord);
	EXPECT_EQ(type, RequestType::TS_REQUEST_TYPE_UNKNOWN);
	EXPECT_EQ(extractedWord.length(), 0);
}

TEST_F(RequestsNavigatorTests, handleEmptyWordSimilarWordRequest)
{
	cout << "RequestsNavigatorTests::handleEmptyWordSimilarWordRequest" << endl;
	BasicRequestNavigator reqNavigator(m_apiPrefix);

	const string emptyStatsStr = "";
	const string emptyWord = "";
	const string validQuery = "word=" + emptyWord;
	string extractedWord;
	RequestType type = reqNavigator.GetRequestTypeFromURI(emptyStatsStr, validQuery, extractedWord);
	EXPECT_EQ(type, RequestType::TS_REQUEST_TYPE_SIMILAR_WORDS);
	EXPECT_EQ(extractedWord.length(), 0);
}

TEST_F(RequestsNavigatorTests, handleSimilarWordRequest)
{
	cout << "RequestsNavigatorTests::handleSimilarWordRequest" << endl;
	BasicRequestNavigator reqNavigator(m_apiPrefix);

	const string emptyStatsStr = "";
	const string word = "some_word";
	const string validQuery = "word=" + word;
	string extractedWord;
	RequestType type = reqNavigator.GetRequestTypeFromURI(emptyStatsStr, validQuery, extractedWord);
	EXPECT_EQ(type, RequestType::TS_REQUEST_TYPE_SIMILAR_WORDS);
	EXPECT_EQ(extractedWord.length(), word.length());
	ASSERT_STREQ(word.c_str(), extractedWord.c_str());
}


TEST_F(RequestsNavigatorTests, handleSimilarWordRequestWithoutTheEqualSign)
{
	cout << "RequestsNavigatorTests::handleSimilarWordRequestWithoutTheEqualSing" << endl;
	BasicRequestNavigator reqNavigator(m_apiPrefix);

	const string emptyStatsStr = "";
	const string word = "some_word";
	const string missingEqualSigQuery = "word" + word;
	string extractedWord;
	RequestType type = reqNavigator.GetRequestTypeFromURI(emptyStatsStr, missingEqualSigQuery, extractedWord);
	EXPECT_EQ(type, RequestType::TS_REQUEST_TYPE_UNKNOWN);
	EXPECT_EQ(extractedWord.length(), 0);
}


TEST_F(RequestsNavigatorTests, handleInCorrectSimilarWordRequestBySingleCharacter)
{
	cout << "RequestsNavigatorTests::handleInCorrectSimilarWordRequestBySingleCharacter" << endl;
	BasicRequestNavigator reqNavigator(m_apiPrefix);

	const string emptyStatsStr = "";
	const string someWord = "some_word";
	const string invalidSimilarWordRequest = "ward=" + someWord;
	string extractedWord;
	RequestType type = reqNavigator.GetRequestTypeFromURI(emptyStatsStr, invalidSimilarWordRequest, extractedWord);
	EXPECT_EQ(type, RequestType::TS_REQUEST_TYPE_UNKNOWN);
	EXPECT_EQ(extractedWord.length(), 0);
}

TEST_F(RequestsNavigatorTests, handleTooLongURIRequest)
{
	cout << "RequestsNavigatorTests::handleInCorrectSimilarWordRequestBySingleCharacter" << endl;
	BasicRequestNavigator reqNavigator(m_apiPrefix);
}
