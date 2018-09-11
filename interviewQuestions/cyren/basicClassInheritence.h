

#include <iostream>
#include <string.h>

using namespace std;


class Base
{
	public:
	Base(const char* str)
	{
		if (str != nullptr)
		{
			int len = strlen(str);
			m_cstr = new char[len + 1];
			strcpy(m_cstr, str);
			cout << "Base::Base - set m_cstr to:" << m_cstr << endl;
		}
		else
		{
			m_cstr = nullptr;
			cout << "Base::Base - set m_cstr nullptr:" << endl;
		}	

		// If we try to call the PureVirtualFunction --> we will get a compiler error
		// PureVirtualFunc();
	}

	virtual ~Base()
	{
		cout << "Base::~Base" << endl;
		if (m_cstr != nullptr)
		{
			delete [] m_cstr;
		} 
	}

	virtual void PureVirtualFunc() = 0;

	virtual void VirtualFunc()
	{
		cout << "Base::VirtualFunc" << endl;
	}

	void NotVirtualFunc()
	{
		cout << "Base::NotVirtualFunc" << endl;
	}

	const char* GetCstr() const 
	{
		return this->m_cstr;
	}

	private:
	char* m_cstr;
};	


class Derived : public Base
{
	public:
	Derived(const char* str) : Base(str)
	{
		cout << "Derived::Derived" << endl;
	} 
	
	virtual ~Derived()
	{	
		cout << "Derived::~Derived" << endl;
	}

	virtual void PureVirtualFunc()
	{
		cout << "Derived::PureVirtualFunc" << endl;
	}

	virtual void VirtualFunc()
	{
		cout << "Derived::VirtualFunc" << endl;
	}

	void NotVirtualFunc()
	{
		cout << "Derived::NotVirtualFunc" << endl;
	}
	
};	
