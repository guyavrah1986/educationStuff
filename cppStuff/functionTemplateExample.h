// ======================================================================================================================================================================================
/*
*  Function templates:
*  -------------------
* 1) When we define a function template we define a "blue print" for a potential function instantiation. Nothing is being "created" (compiled) yet.
*
*
*
*/
// ======================================================================================================================================================================================

#pragma once

#include <iostream>

class A
{
	public:
	A(int a) : m_a(a)
	{
		std::cout << "A::A - setting m_a to:" << m_a << std::endl;
	}

	friend bool operator>(const A& lhs, const A& rhs)
	{
		return lhs.m_a > rhs.m_a;
	}
	
	private:
	int m_a;
};


// 1)
template <typename T> void mySwap(T& a, T& b)
{
	T tmp = a;
	a = b;
	b = tmp;
}

//2)
template <typename T> bool myComapre(const T& lhs, const T& rhs)
{
	return lhs > rhs;
}



