#pragma once

#include "../memoryLeakDetector/memoryLeakDetectorBase.h"

class SimilarWordsesolverTests : public ::testing::Test
{
protected:

	SimilarWordsesolverTests();
	virtual ~SimilarWordsesolverTests();
	virtual void SetUp();
	virtual void TearDown();

public:
	std::string m_fileNameFullPath;
	const std::string m_fileName = "words_clean_testing.txt";
	const std::string m_filesFolderName = "/textFiles/";
	const size_t m_numOfWordsInFile = 13;
};
