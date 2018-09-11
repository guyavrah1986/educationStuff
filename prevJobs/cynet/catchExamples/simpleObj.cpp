#include <iostream>
#include <string>

#include "simpleObj.h"

using namespace std;

SimpleObj::SimpleObj(int i)
	: m_i(i)
{
	cout << "SimpleObj::SimpleObj - setting m_i to:" << m_i << endl;
}

SimpleObj::SimpleObj()
{
	cout << "SimpleObj::SimpleObj - setting m_i to:" << m_i << endl;
}

SimpleObj::SimpleObj(const SimpleObj& other)
{
	this->m_i = other.m_i;
	cout << "SimpleObj::SimpleObj(copy) - setting m_i to:" << m_i << endl;
}

SimpleObj::~SimpleObj()
{
	cout << "SimpleObj::~SimpleObj" << endl;
}

int SimpleObj::Getm_i() const
{
	return this->m_i;
}