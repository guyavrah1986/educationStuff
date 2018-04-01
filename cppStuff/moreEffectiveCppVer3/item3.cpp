// ====================================================================================================================================================================
/*
* const pointer and pointer to const:
* ----------------------------------- 
* 
*
*/
// ====================================================================================================================================================================

#include <iostream>

using namespace std;

void pointerUsageExample()
{
	
}

void item3Usage()
{
	pointerUsageExample();
	cout << "\n \n item3Usage - end" << endl;
}

int main(int argc, char** argv)
{
	cout << "main - start" << endl;
	item3Usage();
	
	cout << "main - enter any key to terminate..." << endl;
	char c = 0;
	cin >> c;
	cout << "\n \n main - end" << endl;
	return 0;
}
