#include <iostream>
#include <vector>
#include <algorithm>

#include "vector3Exaplained.h"

using namespace std;

// ===================================================================================================================================================================
// ===================================================================================================================================================================
// 1) 
// Key note:In either case of the two different object the initial size and capacity of the m_vec class member will be 0.
//          That means, no ctor of the contained class will be invoked.
// ===================================================================================================================================================================
// ===================================================================================================================================================================
void createObjWithVectorClassMember()
{
	cout << "createObjWithVectorClassMember - start" << endl;
	ObjWithVectorAsClassMember obj;
}

void createObjWithRefToVectorClassMember()
{
	cout << "createObjWithRefToVectorClassMember - start" << endl;
	vector<MyObj> vecArg;
	ObjWithRefVectorAsClassMember obj(vecArg);
}
