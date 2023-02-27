#include <iostream>

#include "lib1/lib1.h"

using namespace std;

int main(int argc, char** argv)
{
	cout << "main - Start" << endl;
	cout << "main - creating CLib1 object on the main function's stack" << endl;
	CLib1 lib1Obj(12);
	cout << "main - End" << endl;
	return 0;
}

