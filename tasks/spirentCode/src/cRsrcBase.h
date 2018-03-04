#pragma once

#include <string>

#include "adapRsrcValue.h"

class CRsrcBase
{
public:
		CRsrcBase(IN const char* rsrcUri, IN const EnRsrcType rsrcType, IN bool internalCreated);
		virtual ~CRsrcBase();
		virtual EnRsrcType AdapGetRsrcType() const;

private:
		const std::string m_rsrcUri;
		EnRsrcType m_rsrcType;
		bool m_internalCreated;
};
