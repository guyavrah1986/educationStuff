#include <iostream>

#include "cRsrcBase.h"

using namespace std;

CRsrcBase::CRsrcBase(IN const char* rsrcUri, IN const SpEnRsrcType rsrcType, IN bool internalCreated)
	: m_rsrcUri(rsrcUri ? rsrcUri : string())
	, m_rsrcType(rsrcType)
	, m_internalCreated(internalCreated)
{
	cout << "CRsrsBase::CRsrcBase - created resource with m_rsrcUri:" << m_rsrcUri << " of type:" << static_cast<int>(m_rsrcType)
			 << " with internalCreated:" << m_internalCreated << endl;
}

CRsrcBase::~CRsrcBase()
{
	cout << "CRsrcBase::~CRsrcBase" << endl;
}

SpEnRsrcType CRsrcBase::AdapGetRsrcType() const
{
	cout << "CRsrcBase::AdapGetRsrcType" << endl;
	return m_rsrcType;
}
