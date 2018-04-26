#pragma once

#include "MyObj.h"
#include "MyObjNoDefualtCtor.h"
#include "MyObjsOperators.h"

class ObjWithVectorAsClassMember
{
public:
	ObjWithVectorAsClassMember()
		: m_vec()
	{
		std::cout << "ObjWithVectorAsClassMember::ObjWithVectorAsClassMember - size of"
			" vec is:" << m_vec.size() << " capacity is:" << m_vec.capacity() << std::endl;
	}

	~ObjWithVectorAsClassMember()
	{
		std::cout << "ObjWithVectorAsClassMember::~ObjWithVectorAsClassMember" << std::endl;
	}

	std::vector<MyObj> m_vec;
};

class ObjWithRefVectorAsClassMember
{
public:
	ObjWithRefVectorAsClassMember(std::vector<MyObj>& vec)
		: m_vec(vec)
	{
		std::cout << "ObjWithRefVectorAsClassMember::ObjWithRefVectorAsClassMember - size of"
			" vec is:" << m_vec.size() << " capacity is:" << m_vec.capacity() << std::endl;
	}

	~ObjWithRefVectorAsClassMember()
	{
		std::cout << "ObjWithRefVectorAsClassMember::~ObjWithRefVectorAsClassMember" << std::endl;
	}

	std::vector<MyObj>& m_vec;
};

void createObjWithVectorClassMember();
void createObjWithRefToVectorClassMember();


