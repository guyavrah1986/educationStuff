#pragma once

#include "globalInternalInclude.h"
#include "hashDbManager.h"

class ISimilarWordsResolver
{

public:
	virtual Result GetListOfSimilarWords(IN const HashDbManager& dbManager, IN const std::string& word, INOUT std::list<std::string>& matchedWordsList) = 0;
	virtual ~ISimilarWordsResolver() {}
};

