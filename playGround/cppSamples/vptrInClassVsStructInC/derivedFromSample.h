#pragma once

#include "sampleClass.h"

class DerivedFromSample : public SampleClass
{
public:
	DerivedFromSample(double d, int id, const char* str);
	~DerivedFromSample();

private:
	double m_d;
};
