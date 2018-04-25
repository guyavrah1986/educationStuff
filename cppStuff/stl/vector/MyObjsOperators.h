#pragma once

#include <ostream>
#include <iostream>

#include "MyObj.h"
#include "MyObjNoDefualtCtor.h"

std::ostream& operator<<(std::ostream& out, const MyObjNoDefualtCtor& obj)
{
	std::cout << "MyObjNoDefualtCtor (" << &obj << "," << obj.m_a << ")" << std::endl;
	return out;
}

std::ostream& operator<<(std::ostream& out, const MyObj& obj)
{
	std::cout << "MyObj (" << &obj << "," << obj.m_a << ")" << std::endl;
	return out;
}
