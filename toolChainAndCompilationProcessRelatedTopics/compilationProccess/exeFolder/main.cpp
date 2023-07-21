#include <iostream>

#include "lib1/lib1.h"
#include "lib2/lib2.h"

using namespace std;

int main(int argc, char** argv)
{
	cout << "main - Start" << endl;
	cout << "main - creating CLib1 object on the main function's stack" << endl;
	CLib1 lib1Obj(12);
	lib1Obj.func1();
	cout << "main - creating CLib2 object on the main function's stack" << endl;
	CLib2 lib2Obj(lib1Obj);
	lib2Obj.func2();
	cout << "main - End" << endl;
	return 0;
}

