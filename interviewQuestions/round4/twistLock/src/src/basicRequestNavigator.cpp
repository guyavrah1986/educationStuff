#include "../include/basicRequestNavigator.h"

#include <iostream>

using namespace std;

BasicRequestNavigator::BasicRequestNavigator(IN const string& prefixApi)
	: m_prefixApiString(prefixApi)
{
	cout << "BasicRequestNavigator::BasicRequestNavigator - set m_prefixApiString to:" << m_prefixApiString << endl;
}

BasicRequestNavigator::~BasicRequestNavigator()
{
	cout << "BasicRequestNavigator::~BasicRequestNavigator" << endl;
}

RequestType BasicRequestNavigator::GetRequestTypeFromURI(IN const string& uri, IN const string& query, INOUT string& extractedWord)
{
	cout << "BasicRequestNavigator::GetRequestTypeFromURI - got URI:" << uri << " and query:" << query << endl;

	// first - test whether the URI contains EXACTLY the stats request URI: /api/v1/stats
	if (isStatsURI(uri) == true)
	{
		extractedWord.clear();
		return RequestType::TS_REQUEST_TYPE_STATS;
	}

	// now test whether is is a similar word request
	// which should be composed as follows:
	// 	 GET /api/v1/similar?word=some_word_to_match
	//       |    uri       |  query_string        |
	// Note that the ? mark is not in neither of the
	// uri nor the query_string

	// make sure the query string is "long enough"
	if (query.length() < m_similarWordApiPrefix.length())
	{
		extractedWord.clear();
		return RequestType::TS_REQUEST_TYPE_UNKNOWN;
	}

	// verify the api prefix is valid, meaning the first 5 characters are exactly: word=
	if (0 != query.substr(0, m_similarWordApiPrefix.length()).compare(m_similarWordApiPrefix))
	{
		extractedWord.clear();
		return RequestType::TS_REQUEST_TYPE_UNKNOWN;
	}

	// extract the word and return success
	extractedWord = query.substr(m_similarWordApiPrefix.length());
	return RequestType::TS_REQUEST_TYPE_SIMILAR_WORDS;
}

/*
 * This function returns true if the uri argument equals /api/v1/stats
 * Otherwise it returns false.
 */
bool BasicRequestNavigator::isStatsURI(IN const string& uri) const
{
	if (0 == uri.compare(m_prefixApiString + m_statsApiPrefix))
	{
		return true;
	}

	return false;
}

string BasicRequestNavigator::extractWordOrStatsFromEntireURI(IN const string& uri) const
{
	string ret;
	if (uri.length() <= m_prefixApiString.length())
	{
		return ret;
	}

	string prefix = uri.substr(m_prefixApiString.length());
	if (0 != prefix.compare(m_prefixApiString))
	{
		return ret;
	}

	ret = uri.substr(m_prefixApiString.length());
	return ret;
}

const string BasicRequestNavigator::m_statsApiPrefix = "stats";
const string BasicRequestNavigator::m_similarWordApiPrefix = "word=";


