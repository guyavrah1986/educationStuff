#include <iostream>

#include "hashDbManagerTests.h"
#include "../../src/include/hashDbManager.h"
#include "../../src/include/basicSimilarWordsResolver.h"
#include "../../common/include/fileSystemUtils.h"

using namespace std;

HashDbManagerTests::HashDbManagerTests()
{
	cout << "HashDbManagerTests::HashDbManagerTests - current working directory is:" << FileSystemUtils::GetCurrentWorkingDirectory() << endl;
	m_rootFolder = FileSystemUtils::GetCurrentWorkingDirectory();
}

HashDbManagerTests::~HashDbManagerTests()
{
	cout << "HashDbManagerTests::~HashDbManagerTests" << endl;
}

void HashDbManagerTests::SetUp()
{
	cout << "HashDbManagerTests::SetUp" << endl;
}

void HashDbManagerTests::TearDown()
{
	cout << "HashDbManagerTests::TearDown" << endl;
}


// =====================================================================================================================
// GTests for this class
// =====================================================================================================================

TEST_F(HashDbManagerTests, verifySameHashCodeForWordsOfTheSamePermutation)
{
	cout << "HashDbManagerTests::verifySameHashCodeForWordsOfTheSamePermutation" << endl;
	HashDbManager dbManager;

	dbManager.InitDB(m_rootFolder + "/" + m_sameHashCodeWordsFile);
	map<string, size_t> wordsToHashCodeMap = dbManager.GetWordToPermutationNumberMap();

	map<string, size_t>::const_iterator it = wordsToHashCodeMap.begin();
	size_t hashCode = it->second;
	cout << "HashDbManagerTests::verifySameHashCodeForWordsOfTheSamePermutation - hash code is:" << hashCode << endl;
	bool sameHashCode = true;
	while (it != wordsToHashCodeMap.end())
	{
		if (it->second != hashCode)
		{
			sameHashCode = false;
			break;
		}
		++it;
	}
	EXPECT_EQ(true, sameHashCode);

	map<uint64_t, list<string>> hashCodeToWordsListMap = dbManager.GetHashCodeToWordsList();
	EXPECT_EQ(1,hashCodeToWordsListMap.size());

	dbManager.printWordToHashCodeMap();
	dbManager.printHashCodeToWordsListMap();
}

TEST_F(HashDbManagerTests, verifySameHashCodeForWordsOfTheSamePermutationVersion2)
{
	cout << "HashDbManagerTests::verifySameHashCodeForWordsOfTheSamePermutationVersion2" << endl;
	HashDbManager dbManager;

	dbManager.InitDB(m_rootFolder + "/" + m_sameHashCodeTwiceAndNoHashCodeOnceFile);

	dbManager.printWordToHashCodeMap();
	dbManager.printHashCodeToWordsListMap();
}

TEST_F(HashDbManagerTests, verifyProperColaborationWithSimilarWordsRequestResolver)
{
	cout << "HashDbManagerTests::verifyProperColaborationWithSimilarWordsRequestResolver" << endl;
	HashDbManager dbManager;
	BasicSimilarWordsResolver similarWordsResolver;
	dbManager.InitDB(m_rootFolder + "/" + m_validDbFile);
	list<string> resList;

	// a) word that does not exists in the DB at all
	resList.clear();
	string word = "raul";
	Result res = similarWordsResolver.GetListOfSimilarWords(dbManager, word, resList);
	EXPECT_EQ(true, res.IsSuccess());
	EXPECT_EQ(resList.size(), 0);

	// b) word that exists in the DB with no similar words
	word = "bgt";
	res = similarWordsResolver.GetListOfSimilarWords(dbManager, word, resList);
	EXPECT_EQ(true, res.IsSuccess());
	EXPECT_EQ(resList.size(), 0);

	// c) word that exists in the DB with one similar word
	word = "cgb";
	string matchedWord1 = "bgc";
	resList.clear();
	res = similarWordsResolver.GetListOfSimilarWords(dbManager, word, resList);
	EXPECT_EQ(true, res.IsSuccess());
	EXPECT_EQ(resList.size(), 1);
	string retWord = resList.front();
	EXPECT_STREQ(retWord.c_str(), matchedWord1.c_str());

	// d) word that exists in the DB with two similar words
	word = "apple";
	matchedWord1 = "appel";
	string matchedWord2 = "pelpa";
	resList.clear();
	res = similarWordsResolver.GetListOfSimilarWords(dbManager, word, resList);
	EXPECT_EQ(true, res.IsSuccess());
	EXPECT_EQ(resList.size(), 2);

	retWord = resList.front();
	resList.pop_front();
	EXPECT_STREQ(retWord.c_str(), matchedWord1.c_str());

	retWord = resList.front();
	EXPECT_STREQ(retWord.c_str(), matchedWord2.c_str());
}

TEST_F(HashDbManagerTests, verifyProperLoadOfTheOriginalDBFile)
{
	cout << "HashDbManagerTests::verifyProperLoadOfTheOriginalDBFile" << endl;
	HashDbManager dbManager;
	BasicSimilarWordsResolver similarWordsResolver;
	Result res = dbManager.InitDB(m_rootFolder + "/" + m_origDbFile);
	EXPECT_EQ(true, res.IsSuccess());
}

