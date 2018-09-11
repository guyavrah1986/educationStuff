#pragma once

#include "requestNavigator.h"

class BasicRequestNavigator : public IRequestNavigator
{
	NO_COPY(BasicRequestNavigator);

// methods
public:
	BasicRequestNavigator(IN const std::string& prefixApi);
	virtual ~BasicRequestNavigator();

	virtual	RequestType GetRequestTypeFromURI(IN const std::string& uri, IN const std::string& query, INOUT std::string& extractedWord) override;

private:
	bool isStatsURI(IN const std::string& uri) const;
	std::string extractWordOrStatsFromEntireURI(IN const std::string& uri) const;

// members
private:
	const std::string m_prefixApiString;			// DesginNote: will hold, in our case - "/api/v1/" (length == 8)
	static const std::string m_statsApiPrefix;		// DesinNote: Will hold, in our case - "stats" (length == 5)
	static const std::string m_similarWordApiPrefix;// DesginNote: Will hold, in our case - "word=" (length == 5)
};
