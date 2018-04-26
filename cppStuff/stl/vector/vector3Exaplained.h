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
		std::cout << "ObjWithVectorAsClassMember::ObjWithVectorAsClassMember" << std::endl;
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
	ObjWithRefVectorAsClassMember()
		: m_vec()
	{
		std::cout << "ObjWithRefVectorAsClassMember::ObjWithRefVectorAsClassMember" << std::endl;
	}

	~ObjWithRefVectorAsClassMember()
	{
		std::cout << "ObjWithRefVectorAsClassMember::~ObjWithRefVectorAsClassMember" << std::endl;
	}

	std::vector<MyObj> m_vec;
};

void objWithVectorClassMember();
void objWithRefToVectorClassMember();


