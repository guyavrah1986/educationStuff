#include <iostream>

#include "cRsrcBase.h"
#include "floatRsrc.h"

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

// Factory method to create resources of different types.
// Change is required only in this function to add a creation option for
// a new resource type
CRsrcBase* CRsrcBase::Create(IN const char* rsrcUri,
							 IN bool isInternalCreated,
							 IN const SpEnRsrcType rsrcType)
{
	switch (rsrcType)
	{
	case SP_M2M_RSRC_TYPE_FLOAT:cout << "CRsrcBase::Create - creating FLOAT resource type" << endl;
								return new CFloatRsrc(rsrcUri, isInternalCreated);

	default:cout << "CRsrcBase::Create - got an invalid resource type, return NULL" << endl;
			return NULL;
	}
}
