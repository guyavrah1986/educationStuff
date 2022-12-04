#pragma once

#include <string>
#include <list>
#include <map>

#include "globalInternalInclude.h"

class HashDbManager
{
	NO_COPY(HashDbManager);

// methods
public:
	HashDbManager();
	~HashDbManager();

	Result InitDB(IN const std::string& dbFileName);
	uint64_t GetPermutationNumberForWord(IN const std::string& word) const;
	std::list<std::string> GetListOfMatchedWordsForPermutationNumber(IN uint64_t wordPermutationNumber) const;
	size_t GetTotalNumOfWordsInDb() const;

	// for debug:
	void printWordToHashCodeMap() const;
	void printHashCodeToWordsListMap() const;
	std::map<std::string, uint64_t> GetWordToPermutationNumberMap() const;
	std::map<uint64_t, std::list<std::string>> GetHashCodeToWordsList() const;

private:
	void constructWordToHashCodeMap(IN std::list<std::string>& wordsList);
	void constructHashCodeToWordsListMap();

// members
private:
	size_t m_totalNumOfWordsInDb;	// DesginNote: It is assumed that the total number of words will fit into size_t
	std::map<std::string, uint64_t> m_wordToPermutationNumberMap;
	std::map<uint64_t, std::list<std::string>> m_permutationNumberToPermutationsListMap;
};
