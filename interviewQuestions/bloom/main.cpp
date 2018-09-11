


#include <iostream>

#include "generalCppQuestions.h"

using namespace std;

int main(int argc, char** argv)
{
	cout << "bloom main - start" << endl;
	invokeFoo();
	int x = 16;
	int b = 2;
	modify(x, b);

	cout << "bloom main - end" << endl;
}
