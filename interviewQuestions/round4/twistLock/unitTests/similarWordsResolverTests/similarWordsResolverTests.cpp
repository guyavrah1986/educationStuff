#include <iostream>

#include "similarWordsResolverTests.h"
#include "../../src/include/basicSimilarWordsResolver.h"
#include "../../common/include/fileSystemUtils.h"

using namespace std;

SimilarWordsesolverTests::SimilarWordsesolverTests()
{
	string baseFoler = FileSystemUtils::GetCurrentWorkingDirectory();
	m_fileNameFullPath = baseFoler + m_filesFolderName + m_fileName;
	cout << "SimilarWordsesolverTests::SimilarWordsesolverTests - m_fileNameFullPath:" << m_fileNameFullPath << endl;
}

SimilarWordsesolverTests::~SimilarWordsesolverTests()
{
	cout << "SimilarWordsesolverTests::~SimilarWordsesolverTests" << endl;
}

void SimilarWordsesolverTests::SetUp()
{
	cout << "SimilarWordsesolverTests::SetUp" << endl;
}

void SimilarWordsesolverTests::TearDown()
{
	cout << "SimilarWordsesolverTests::TearDown" << endl;
}


// =====================================================================================================================
// GTests for this class
// =====================================================================================================================

TEST_F(SimilarWordsesolverTests, resolveWordThatDoesNotExsistAtAllInDB)
{
	cout << "SimilarWordsesolverTests::resolveWordThatDoesNotExsistAtAllInDB" << endl;

	// create a DB
	HashDbManager dbManager;
	dbManager.InitDB(m_fileNameFullPath);
	const string wordNotInDB = "Raul";

	BasicSimilarWordsResolver resolver;
	list<string> matchedWordsList;
	Result res = resolver.GetListOfSimilarWords(dbManager, wordNotInDB, matchedWordsList);

	EXPECT_EQ(res.IsSuccess(), true);
	EXPECT_EQ(matchedWordsList.size(), 0);
}

TEST_F(SimilarWordsesolverTests, resolveWordThatExsitsButDoesNotHaveMatchedWords)
{
	cout << "SimilarWordsesolverTests::resolveWordThatExsitsButDoesNotHaveMatchedWords" << endl;

	// create a DB
	HashDbManager dbManager;
	dbManager.InitDB(m_fileNameFullPath);
	const string wordInDBThatDoesNotHaveMatchedWords = "bgu";

	BasicSimilarWordsResolver resolver;
	list<string> matchedWordsList;
	Result res = resolver.GetListOfSimilarWords(dbManager, wordInDBThatDoesNotHaveMatchedWords, matchedWordsList);

	EXPECT_EQ(res.IsSuccess(), true);
	EXPECT_EQ(matchedWordsList.size(), 0);
}

TEST_F(SimilarWordsesolverTests, resolveWordThatHaveOneMatchedWords)
{
	cout << "SimilarWordsesolverTests::resolveWordThatHaveOneMatchedWords" << endl;

	// create a DB
	HashDbManager dbManager;
	dbManager.InitDB(m_fileNameFullPath);
	const string wordInDBThaHaveOneMatchedWords = "cgb";
	const string matchedWord = "bgc";

	BasicSimilarWordsResolver resolver;
	list<string> matchedWordsList;
	Result res = resolver.GetListOfSimilarWords(dbManager, wordInDBThaHaveOneMatchedWords, matchedWordsList);

	EXPECT_EQ(res.IsSuccess(), true);
	EXPECT_EQ(matchedWordsList.size(), 1);
	string retVal = matchedWordsList.front();
	EXPECT_STREQ(retVal.c_str(), matchedWord.c_str());
}

TEST_F(SimilarWordsesolverTests, resolveWordThatHaveTwoMatchedWords)
{
	cout << "SimilarWordsesolverTests::resolveWordThatHaveTwoMatchedWords" << endl;

	// create a DB
	HashDbManager dbManager;
	dbManager.InitDB(m_fileNameFullPath);
	const string wordInDBThaHaveTwoMatchedWords = "appel";
	const string matchedWord1 = "apple";
	const string matchedWord2 = "pelpa";

	BasicSimilarWordsResolver resolver;
	list<string> matchedWordsList;
	Result res = resolver.GetListOfSimilarWords(dbManager, wordInDBThaHaveTwoMatchedWords, matchedWordsList);

	EXPECT_EQ(res.IsSuccess(), true);
	EXPECT_EQ(matchedWordsList.size(), 2);
	string retVal1 = matchedWordsList.front();

	cout << "SimilarWordsesolverTests::resolveWordThatHaveTwoMatchedWords - displaying matched list:" << endl;
	for (list<string>::const_iterator it = matchedWordsList.begin(); it != matchedWordsList.end(); ++it)
	{
		cout << *it << endl;
	}
}
