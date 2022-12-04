#pragma once

#include "IHttpRequestSender.h"
#include "../../../../src/include/globalInternalInclude.h"

#include <map>
#include <random>


class SimpleHttpGetRequestClient : public IHttpGetRequestSender
{
	NO_COPY(SimpleHttpGetRequestClient);

// methods
public:
	SimpleHttpGetRequestClient();
	virtual ~SimpleHttpGetRequestClient();

	virtual void SendHttpGetRequest() override;
	void initWordsMap(const std::string& fileName);
	std::string GetRandomWordFromList();
private:

// members
private:
	uint64_t m_totalNumOfWords;
	std::map<uint64_t, std::string> m_wordIndexToWrodStrMap;
	std::random_device rd;     // only used once to initialize (seed) engine
	std::mt19937 rng;    // random-number engine used (Mersenne-Twister in this case)
};
