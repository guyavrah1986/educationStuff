#pragma once

#include "../memoryLeakDetector/memoryLeakDetectorBase.h"
#include "../../common/include/fileSystemUtils.h"

class HashDbManagerTests : public ::testing::Test
{
protected:

	HashDbManagerTests();
	virtual ~HashDbManagerTests();
	virtual void SetUp();
	virtual void TearDown();

public:
	std::string m_rootFolder;
	const std::string m_validDbFile = "textFiles/words_clean_testing.txt";
	const std::string m_sameHashCodeWordsFile = "textFiles/words_clean_same_hash_code_words.txt";
	const std::string m_sameHashCodeTwiceAndNoHashCodeOnceFile = "textFiles/words_clean_same_hash_code_twice_and_no_hash_code_once_words.txt";
	const std::string m_origDbFile = "textFiles/words_clean.txt";
	const size_t m_numOfWordsInFile = 13;
};



