#pragma once

#include "cStatsCollectedBase.h"


class CStatsCollectedCounter : public CStatsCollectedBase
{
	public:
	CStatsCollectedCounter(const char* pName, bool bIsEnabled, bool isOutputEnabled);
	virtual ~CStatsCollectedCounter();

	virtual bool Update();
	virtual bool output();

	private:
	unsigned int m_counter;
};
