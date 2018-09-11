#include "../include/hashDbManager.h"

#include <iostream>
#include <fstream>
#include <algorithm>

using namespace std;

HashDbManager::HashDbManager()
	: m_totalNumOfWordsInDb(0)
{
	cout << "HashDbManager::HashDbManager" << endl;
}

HashDbManager::~HashDbManager()
{
	cout << "HashDbManager::~HashDbManager" << endl;
}

Result HashDbManager::InitDB(IN const string& dbFileName)
{
	cout << "HashDbManager::InitDB - got file name:" << dbFileName << endl;
	ifstream infile(dbFileName);			// DesginNote: not handling exception due to assumption that the file exists and valid

	string line;
	list<string> wordsList;
	while (getline(infile, line))
	{
		wordsList.emplace_back(line);
	}
	m_totalNumOfWordsInDb = wordsList.size();
	map<string, uint64_t> wordsToHashCodeMap;

	// construct the maps
	constructWordToHashCodeMap(wordsList);
	constructHashCodeToWordsListMap();

	return (Result(ErrorCode::TS_SUCCESS));
}

uint64_t HashDbManager::GetPermutationNumberForWord(IN const string& word) const
{
	cout << "HashDbManager::GetPermutationNumberForWord - got word:" << word << endl;
	map<string, size_t>::const_iterator it = m_wordToPermutationNumberMap.find(word);

	if (it != m_wordToPermutationNumberMap.end())
	{
		return it->second;
	}
	else
	{
		return 0;
	}
}

list<string> HashDbManager::GetListOfMatchedWordsForPermutationNumber(IN size_t wordPermutationNumber) const
{
	cout << "HashDbManager::GetListOfMatchedWordsForPermutationNumber - got wordPermutationNumber:" << wordPermutationNumber << endl;
	list<string> ret;

	map<size_t, list<string>>::const_iterator it = m_permutationNumberToPermutationsListMap.find(wordPermutationNumber);
	if (it != m_permutationNumberToPermutationsListMap.end())
	{
		return it->second;
	}

	return ret;
}


void HashDbManager::constructWordToHashCodeMap(IN list<string>& wordsList)
{
	cout << "HashDbManager::constructWordToHashCodeMap" << endl;

	for (list<string>::iterator it = wordsList.begin(); it != wordsList.end(); ++it)
	{
		// DesginNote: In order for every words which is composed from the same "permutation"
		// will have the same hash code, before generating the hash code, sort the word
		string origWord = *it;
		sort((*it).begin(), (*it).end());
		uint64_t hashCode = hash<string>()(*it);
		m_wordToPermutationNumberMap[origWord] = hashCode;
	}
}

void HashDbManager::constructHashCodeToWordsListMap()
{
	cout << "HashDbManager::constructHashCodeToWordsListMap" << endl;

	// for each key (hash code) in the map "accumulate" all the words
	// with the same key into a "single" list
	map<string, uint64_t>::const_iterator it = m_wordToPermutationNumberMap.begin();
	while (it != m_wordToPermutationNumberMap.end())
	{
		// if the hash code (key) is already in the map, than
		// add the word (value) into this key's list of words
		auto search = m_permutationNumberToPermutationsListMap.find(it->second);
		if (search != m_permutationNumberToPermutationsListMap.end())
		{
			// key not found -- create a new list and insert the first
			// word with this hash code. Do so by adding a respective pair
			m_permutationNumberToPermutationsListMap.insert(pair<uint64_t, list<string>>(it->second, list<string>()));
			m_permutationNumberToPermutationsListMap[it->second].emplace_back(it->first);
		}
		else
		{
			// key is already in the map -- simply add the word to the list
			// of this hash code's words.
			m_permutationNumberToPermutationsListMap[it->second].emplace_back(it->first);
		}
		++it;
	}
}

void HashDbManager::printWordToHashCodeMap() const
{
	cout << "HashDbManager::printWordToHashCodeMap" << endl;
	map<string, uint64_t>::const_iterator it = m_wordToPermutationNumberMap.begin();
	while (it != m_wordToPermutationNumberMap.end())
	{
		string word = it->first;
		uint64_t hashCode = it->second;
		cout << "[" << word << " :: " << hashCode << "]" << std::endl;
		++it;
	}
}

void HashDbManager::printHashCodeToWordsListMap() const
{
	cout << "HashDbManager::printHashCodeToWordsListMap" << endl;
	for (map<size_t, list<string>>::const_iterator it = m_permutationNumberToPermutationsListMap.begin(); it != m_permutationNumberToPermutationsListMap.end(); ++it)
	{
		cout << "permutation number " << it->first << " has the following list: [";
		for (list<string>::const_iterator it2 = it->second.begin(); it2 != it->second.end(); ++it2)
		{
			cout << *it2 << ", ";
		}
		cout << "]" << endl;
	}
}

size_t HashDbManager::GetTotalNumOfWordsInDb() const
{
	return m_totalNumOfWordsInDb;
}

map<string, size_t> HashDbManager::GetWordToPermutationNumberMap() const
{
	return m_wordToPermutationNumberMap;
}

map<uint64_t, list<string>> HashDbManager::GetHashCodeToWordsList() const
{
	return m_permutationNumberToPermutationsListMap;
}

