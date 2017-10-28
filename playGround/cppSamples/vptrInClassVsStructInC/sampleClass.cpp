#include "sampleClass.h"

using namespace std;

SampleClass::SampleClass(int id, const char* str)
	: m_id(id)
	, m_str(NULL)
{
	uint32_t strLen = 0;
	const char* tmp = str;
	while (*tmp != '\0')
	{
		++strLen;
		++tmp;
	}

	if (strLen != 0)
	{
		m_str = new char[strLen + 1];
		char* origMstr = m_str;		
		tmp = str;
		while (*tmp != '\0')
		{
			*m_str++ = *tmp++;
		}
		*m_str = '\0';
		m_str = origMstr;
	}
	cout << "SampleClass::SampleClass - set m_id to:" << m_id << " and m_str to:" << m_str  << " at location:" << &m_str << endl;
}


SampleClass::~SampleClass()
{
	if (m_str)
	{
		delete [] m_str;
	}
	cout << "SampleClass::~SampleClass" << endl;

}
