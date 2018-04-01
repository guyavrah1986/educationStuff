// ====================================================================================================================================================================
/*
* const pointer and pointer to const:
* ----------------------------------- 
* 1) When declaring a pointer we have two options: 
* a) Non const pointer to non const data.
* b) In this specific case, although it seems that the pointer is both data and location non const -- this is NOT the case. In this type of declration, the content
*    that the pointer is poiting to is located in the TEXT segment of the process - thus it is invalid operation modifying (writing) to this location. 
* c) Declaring the pointer as a const, meaning we can NOT modify the location we are pointing to --> the const keyword is on the RIGHT side of the astrik (*).
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
	char p1 [] = "string1"; 
	char* p2 = p1;
	*p2 = 'h';
	
	cout << "pointerToPrimitiveTypeUsageExample - p1 points to:" << p1 << endl;
	cout << "pointerToPrimitiveTypeUsageExample - p2 points to:" << p2 << endl;

	// b) 
	char* p3 = "string3"; 
	//*p3 = 'h'; --> Watch out, this line will crash the code !!
	
	// c) 
	char str4 [] = "string4";
	char str5 [] = "string5";
	char* const p4  = str4;
	cout << "pointerToPrimitiveTypeUsageExample - BEFORE modifying the first char that p4 points to:" << p4 << endl;
	*p4 = 'H';
	cout << "pointerToPrimitiveTypeUsageExample - AFTER modifying the first char that p4 points to:" << p4 << endl;
	// p4 = str5; --> This line will NOT compile 
	
	
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
