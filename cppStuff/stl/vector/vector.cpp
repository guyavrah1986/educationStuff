// ===================================================================================================================================================================
// ===================================================================================================================================================================
//
// std::vector of the STL:
// ----------------------
// This short tutorial describes some important aspects that needs to be considered when using the STL containers. In this specific case the examples
// will be depicts with the std::vector container.
// 
// ===================================================================================================================================================================
// ===================================================================================================================================================================

#define _CRTDBG_MAP_ALLOC  // NOTE: the order of the includes that FOLLOWS this define is important !!!
#include <stdlib.h>  
#include <crtdbg.h> 

#include <iostream>

#include "vector1Exaplained.h"
#include "vector2Exaplained.h"
#include "MyObj.h"
#include "MyObjNoDefualtCtor.h"

using namespace std;

// ===================================================================================================================================================================
// ===================================================================================================================================================================
// main
// ===================================================================================================================================================================
// ===================================================================================================================================================================
int main(int argc, char** argv)
{
	cout << "vectorExplained - start" << endl;

	// -------------------
	// vector1Exaplained.h
	// -------------------
	// 1)
	//illustrateVectorDeclerationAndElementsAccess();

	// 2)
	//illustrateFillVectorWithObjects();

	// 3)
	//illustrateVectorGrowth();

	// -------------------
	// vector2Exaplained.h
	// -------------------
	// 4) 
	//illustrateVectorIterator();
	
	// 5) 
	illustrateErasingElementFromVector();

	char c;
	cout << "vectorExplained - press any key and hit ENTER to terminate..." << endl;
	cin >> c;
	_CrtDumpMemoryLeaks();
	return 0;
}

