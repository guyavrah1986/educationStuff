// ========================================================================================================================================================================
/*
* Item 28:
* --------
* 
*
* !! @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ !!
* !! @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ !!
* Key notes:
* 
* !! @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ !!
* !! @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ !!
*
*/
// ======================================================================================================================================================================
#define _CRTDBG_MAP_ALLOC  // NOTE: the order of the includes that FOLLOWS this define is important !!!
#include <stdlib.h>  
#include <crtdbg.h> 

#include <iostream>

#include "MyBasicSmartPointer.h"

using namespace std;

void basicUsageInMyBasicSmartPointerClass()
{
	cout << "basicUsageInMyBasicSmartPointerClass - start" << endl;
	MyBasicSmartPointer<int> sp(new int);
}

void item28Usage()
{
	cout << "item28Usage - start" << endl;

	cout << "\n \n item28Usage - end" << endl;
}

int main(int argc, char** argv)
{
	cout << "main - start" << endl;
	item28Usage();
	
	char c;
	cout << "\n \n main - enter any key and press ENTER to terminate" << endl;
	cin >> c;
	_CrtDumpMemoryLeaks();
	return 0;
}
