#pragma once

#include "similarWordResolver.h"

class BasicSimilarWordsResolver : public ISimilarWordsResolver
{
	NO_COPY(BasicSimilarWordsResolver);

public:
	BasicSimilarWordsResolver();
	virtual ~BasicSimilarWordsResolver();

	/*
	 * In this specific implementation we need to pay attention that the DB will return us
	 * a list of all the matched words ALONG with the given word (this is the format in which
	 * permutations words are stored) --> so the "extra job" of the resolver is to remove the
	 * given word from the list and then simply return it.
	 * For example: given the words (among other) ["appel", "apple", "pelpa"] in the DB, upon
	 * a GET similar?word=appel request, the dbManager, first will return us a list containing
	 * all 3 words ("appel", "apple", "pelpa") and the resolver will simply remove the word in
	 * the request (i.e.- appel) thus eventually returning ["apple", "pelpa"].
	 */
	virtual Result GetListOfSimilarWords(IN const HashDbManager& dbManager,
										 IN const std::string& word,
										 INOUT std::list<std::string>& matchedWordsList) override;
};
