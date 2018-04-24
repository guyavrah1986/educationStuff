// ========================================================================================================================================================================
/*
* Item 24:
* --------
* Virtual functions is a mechanism to implement inheritence.
* 
* 
* !! @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ !!
* !! @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ !!
* Key notes:
* 1) Each class that has at least one virtual function (either her's OR of its "parents") - will have a Virtual Table (vtbl).
*    The size of the v-table is according to the number of virtual functions it has multiple by pointer size.
* 2) Each object (instance) of a class with at least one virtual function, will have an additional "class data member" which is
*    the virtual-pointer (points to the first entry in the v-table).
* !! @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ !!
* !! @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ !!
*
*/
// ======================================================================================================================================================================

#include <iostream>

using namespace std;

void item24Usage()
{
	cout << "item24Usage - start" << endl;


	cout << "\n \n item24Usage - end" << endl;
}

int main(int argc, char** argv)
{
	cout << "main - start" << endl;
	item24Usage();
	
	char c;
	cout << "\n \n main - enter any key and press ENTER to terminate" << endl;
	cin >> c;
	return 0;
}
