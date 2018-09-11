#include "../include/basicSimilarWordsResolver.h"

#include <iostream>

using namespace std;

BasicSimilarWordsResolver::BasicSimilarWordsResolver()
{
	cout << "BasicSimilarWordsResolver::BasicSimilarWordsResolver" << endl;
}

BasicSimilarWordsResolver::~BasicSimilarWordsResolver()
{
	cout << "BasicSimilarWordsResolver::~BasicSimilarWordsResolver" << endl;
}

Result BasicSimilarWordsResolver::GetListOfSimilarWords(IN const HashDbManager& dbManager,
									 	 	 	 	 	IN const string& word,
									 	 	 	 	 	INOUT list<string>& matchedWordsList)
{
	cout << "BasicSimilarWordsResolver::GetListOfSimilarWords - got word:" << word << endl;
	// just in case - clear the list provided
	matchedWordsList.clear();

	size_t wordPermutationNumber = dbManager.GetPermutationNumberForWord(word);
	if (wordPermutationNumber != 0)
	{
		matchedWordsList = dbManager.GetListOfMatchedWordsForPermutationNumber(wordPermutationNumber);
		matchedWordsList.remove(word);
	}
	return Result(ErrorCode::TS_SUCCESS);
}
