#pragma once

class SimpleObj
{
	public:
	SimpleObj(int i);
	SimpleObj();
	SimpleObj(const SimpleObj& other);
	virtual ~SimpleObj();

	int Getm_i() const;
	
	private:
	int m_i;
};