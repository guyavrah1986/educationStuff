// =============================================================================================================================================
/*
* main source file:
* -----------------
* This file holds the code for the application itself. It is the "main" input that will produce our .exe file
* This exe, among integral libraries, will be linked to
*
*/
// =============================================================================================================================================
#include <iostream>
#include <string>

#include "classA.h"
#include "classB.h"

void funcFromASrcFile();
void funcFromBSrcFile();

using namespace std;

int main(int , char**)
{
	cout << "main - start" << endl;
	cout << "main - creating an A object on the stack" << endl;	
	A a;
	a.FooA();
	funcFromASrcFile();

	cout << "main - creating an B object on the stack" << endl;	
	B b;
	b.FooB();
	funcFromBSrcFile();

	char c = 0;
	cout << "main - enter any key to terminate (and press enter)" << endl;
	cin >> c;
	cout << "\n \n main - end" << endl;
	cout << "\n \n main - end" << endl;
	return 0;
}
