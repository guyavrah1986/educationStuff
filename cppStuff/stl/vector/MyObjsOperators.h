#pragma once

#include <ostream>
#include <vector>

#include "MyObj.h"
#include "MyObjNoDefualtCtor.h"

template <typename T> void printVec(const std::vector<T>& vec)
{
	for (size_t i = 0; i < vec.size(); ++i)
	{
		std::cout << vec[i] << " ";
	}
	std::cout << std::endl;
}
std::ostream& operator<<(std::ostream& out, const MyObjNoDefualtCtor& obj);
std::ostream& operator<<(std::ostream& out, const MyObj& obj);
