#include "../include/simpleHttpGetRequestClient.h"

#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

SimpleHttpGetRequestClient::SimpleHttpGetRequestClient()
	: m_totalNumOfWords(0)
	, m_wordIndexToWrodStrMap()
	, rng(rd())
{
	cout << "SimpleHttpGetRequestClient::SimpleHttpGetRequestClient" << endl;
}

SimpleHttpGetRequestClient::~SimpleHttpGetRequestClient()
{
	cout << "SimpleHttpGetRequestClient::~SimpleHttpGetRequestClient" << endl;
}

void SimpleHttpGetRequestClient::SendHttpGetRequest()
{
	cout << "SimpleHttpGetRequestClient::SendHttpGetRequest" << endl;
}

void SimpleHttpGetRequestClient::initWordsMap(const string& dbFileName)
{
	// read the words from the file
	ifstream infile(dbFileName);
	string line;
	while (getline(infile, line))
	{
		m_wordIndexToWrodStrMap[m_totalNumOfWords] = line;
		++m_totalNumOfWords;
	}

	// add some additional words that does NOT exists
	// in original DB's words list
	vector<string> notInDbwordsList = {"buba", "fufa", "rotem", "silso"};
	for (size_t i = 0; i < notInDbwordsList.size(); ++i)
	{
		m_wordIndexToWrodStrMap[m_totalNumOfWords] = notInDbwordsList[i];
		++m_totalNumOfWords;
	}

	cout << "SimpleHttpGetRequestClient::initWordsMap - done initialize words map, which has:"
			<< m_totalNumOfWords << " words, of which " << notInDbwordsList.size() << " are not in the original list of words" << endl;
}

string SimpleHttpGetRequestClient::GetRandomWordFromList()
{
	uniform_int_distribution<uint64_t> uni(0, m_totalNumOfWords); // guaranteed unbiased
	uint64_t randInt = uni(rng);
	return m_wordIndexToWrodStrMap[randInt];
}
