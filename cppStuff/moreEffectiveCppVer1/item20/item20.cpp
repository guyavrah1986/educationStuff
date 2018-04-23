// ========================================================================================================================================================================
/*
* Item 20:
* --------
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
	
	char c;
	cout << "main - enter any key to terminate and hit ENTER" << endl;
	cin >> c;
	return 0;
}

