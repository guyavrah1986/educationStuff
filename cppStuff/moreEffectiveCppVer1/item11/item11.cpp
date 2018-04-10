// ========================================================================================================================================================================
/*
* Item 11:
* --------
*
*
*/
// ======================================================================================================================================================================

#define _CRTDBG_MAP_ALLOC  // NOTE: the order of the includes that FOLLOWS this define is important !!!
#include <stdlib.h>  
#include <crtdbg.h> 

#include <iostream>
#include <memory>

using namespace std;

void item11Usage()
{
	cout << "item11Usage - start" << endl;
	
	cout << "\n \n item11Usage - end" << endl;
}

int main(int argc, char** argv)
{
	cout << "main - start" << endl;

	item11Usage();

	char c = 0;
	cout << "main - enter any key to terminate (and press enter)" << endl;
	cin >> c;
	cout << "\n \n main - end" << endl;
	_CrtDumpMemoryLeaks();
	return 0;
}
