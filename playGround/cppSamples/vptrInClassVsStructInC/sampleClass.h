#pragma once
#include <iostream>


struct SampleStruct
{
	int id;
	char* str;
};

class SampleClass
{

	public:
		SampleClass(int id, const char* str);
		~SampleClass();

	private:
		int m_id;
		char* m_str;

		// some other members
};
