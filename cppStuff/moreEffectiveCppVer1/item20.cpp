// ========================================================================================================================================================================
/*
* Return value optimization:
* --------------------------
* 
*
*/
// ======================================================================================================================================================================

#include <iostream>

using namespace std;



void item20Usage()
{
	cout << "item20Usage - start" << endl;

	cout << "\n \n item20Usage - end" << endl;
}

int main(int argc, char** argv)
{
	cout << "main - start" << endl;
	item20Usage();
	
	cout << "\n \n main - end" << endl;
	return 0;
}
