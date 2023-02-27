#pragma once

class CLib1
{
public:
	explicit CLib1(int a);
	~CLib1();
	
	void func1() const;

private:
	int m_a;
};
