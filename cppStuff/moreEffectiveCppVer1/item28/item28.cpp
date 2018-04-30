// ========================================================================================================================================================================
/*
* Item 28:
* --------
* 1) When implementing the "unique_ptr" with the notion of "ownership transfer" we need to keep in mind that:
* 1a) In the assginment operator we delete the current "pointee" before setting it with the rhs.
* 1b) In both the assginment operator and the copy ctor we set the "old" owner of the pointee to NULL (other/rhs)
*     thus preserving that only a SINGLE "unique_ptr" holds the actual pointer at every moment.
*
* !! @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ !!
* !! @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ !!
* Key notes: - Almost NEVER pass a smart pointer by value (unless you are sure you know what you are doing !!).
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
#include "MySimpleUniquePointer.h"

using namespace std;

void basicUsageInMyBasicSmartPointerClass()
{
	cout << "basicUsageInMyBasicSmartPointerClass - start" << endl;
	
	cout << "basicUsageInMyBasicSmartPointerClass - about to create a MyBasicSmartPointer<int> type"
		" within a dummy scope on the stack" << endl;
	{
		MyBasicSmartPointer<int> sp(new int);
		cout << "basicUsageInMyBasicSmartPointerClass - about to exit dummy scope" << endl;
	}
	
}

void basicUsageInMySimpleUniquePointerClass()
{
	cout << "basicUsageInMySimpleUniquePointerClass -start" << endl;

	{
		cout << "basicUsageInMySimpleUniquePointerClass - creating a MySimpleUniquePointer"
			" on the stack within a dummy scope" << endl;
		MySimpleUniquePointer<int> sp(new int);
		cout << "basicUsageInMySimpleUniquePointerClass - about to exit dummy scope" << endl;
	}
}


void item28Usage()
{
	cout << "item28Usage - start" << endl;
	basicUsageInMyBasicSmartPointerClass();
	basicUsageInMySimpleUniquePointerClass();
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
