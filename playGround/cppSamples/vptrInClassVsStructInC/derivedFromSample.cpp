#include <iostream>
#include "derivedFromSample.h"

using namespace std;

DerivedFromSample::DerivedFromSample(double d, int id, const char* str)
	: SampleClass(id, str)
	, m_d(d)
{
	cout << "DerivedFromSample::DerivedFromSample - set m_d to:" << m_d << endl;
}

DerivedFromSample::~DerivedFromSample()
{
	cout << "DerivedFromSample::~DerivedFromSample" << endl;
}
