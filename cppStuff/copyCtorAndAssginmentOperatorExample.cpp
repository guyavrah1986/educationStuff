// ===================================================================================================================================================================
// ===================================================================================================================================================================
// copy Ctor and assignment operator:
// ---------------------------------
//
//
//
// ===================================================================================================================================================================
// ===================================================================================================================================================================


#include <iostream>
#include <cstring>

using namespace std;

class A 
{

	public:
	A(int a, const char* str)
		: m_a(a)
		, m_cstr(nullptr)
	{
		if (str != nullptr)
		{
			// get the given str length
			size_t len = 0;
			char* tmp = const_cast<char*>(str);
			while (*tmp != '\0')
			{
				++len;
				++tmp;
			}

			if (len > 0)
			{
				m_cstr = new char [len + 1];
				strcpy(m_cstr, str);
			}

		}
		cout << "A::A - init m_a:" << m_a << " and m_cstr:" << m_cstr << endl;
	}

	A() : A(17, nullptr)
	{
		cout << "A::A()" << endl;
	}

	~A()
	{

		if (m_cstr != nullptr)
		{
			delete [] m_cstr;
		}
		cout << "A::~A" << endl; 
	}


	private:
	int m_a;
	char* m_cstr;
}; 




int main(int argc, char** argv)
{
	cout << "main - start" << endl;


	A a(12, "buba");


	cout << "main - end" << endl;
	return 0;
}
