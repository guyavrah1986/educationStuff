#pragma once
#include <ostream>

class MyObjNoDefualtCtor
{
public:
	MyObjNoDefualtCtor(int a); 
	MyObjNoDefualtCtor(const MyObjNoDefualtCtor& other);
	~MyObjNoDefualtCtor();
	MyObjNoDefualtCtor() = delete;
	friend std::ostream& operator<<(std::ostream& out, const MyObjNoDefualtCtor& obj);
	int m_a;
};

