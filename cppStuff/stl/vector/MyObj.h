#pragma once
#include <ostream>

class MyObj
{

public:
	explicit MyObj(int a);
	MyObj();
	MyObj(const MyObj& other);
	MyObj(MyObj&& other);
	~MyObj();
	MyObj& operator=(const MyObj& rhs);

	friend std::ostream& operator<<(const std::ostream& out, const MyObj& obj);
	
	int m_a;
};