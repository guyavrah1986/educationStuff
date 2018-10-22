#pragma once

#include <string>

#include "adapRsrcValue.h"

class CRsrcBase : public IAdapAppRsrcFunc
{
public:
		CRsrcBase(IN const char* rsrcUri, IN const SpEnRsrcType rsrcType, IN bool internalCreated);
		virtual ~CRsrcBase();
		virtual SpEnRsrcType AdapGetRsrcType() const;
	    static CRsrcBase* Create(IN const char* rsrcUri, IN bool isInternalCreated, IN const SpEnRsrcType rsrcType);

private:
		const std::string m_rsrcUri;
		SpEnRsrcType m_rsrcType;
		bool m_internalCreated;
};
