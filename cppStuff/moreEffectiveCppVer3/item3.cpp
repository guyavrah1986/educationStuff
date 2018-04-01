// ====================================================================================================================================================================
/*
* const pointer and pointer to const:
* ----------------------------------- 
* 1) When declaring a pointer we have two options: 
* a) Non const ppinter to non const data.
* ) Declaring the pointer as a const, meaning we can NOT modify the location we are pointing to --> the const keyword is on the LEFT side of the astrik (*).
* ) Declraing the pointer to point to a const "object", meaning we can NOT modifiy the content that the pointer is pointing to.
*
*/
// ====================================================================================================================================================================

#include <iostream>

using namespace std;

void pointerToPrimitiveTypeUsageExample()
{
	cout << "pointerToPrimitiveTypeUsageExample - start" << endl;
	// a) In both cases (p1 & p2) we can modify the content of the 
	//    pointer and also the location it points to.
	char p1 [] = "Hello"; 
	char* p2 = p1;
	*p2 = 'h';
	
	cout << "pointerToPrimitiveTypeUsageExample - p1 points to:" << p1 << endl;
	cout << "pointerToPrimitiveTypeUsageExample - p2 points to:" << p2 << endl;

	char* p3 = "Hello world"; 
	//*p3 = 'h';
	
	cout << "\n \n pointerToPrimitiveTypeUsageExample - end" << endl;
}

void item3Usage()
{
	pointerToPrimitiveTypeUsageExample();
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
