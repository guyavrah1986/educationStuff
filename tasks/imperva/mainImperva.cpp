

#include <iostream>

using namespace std;

#include "stringQuestion.h"

int main(int argc, char** argv)
{
	cout << "main - start \n \n" << endl;
	string str = "abcd";
	cout << str << " returned:"  << findFirstCharThatAppearsOnlyOnce(str.c_str()) << endl;
	str = "aabcd";
	cout << str << " returned:"  << findFirstCharThatAppearsOnlyOnce(str.c_str()) << endl;


	cout << "\n \n main - end" << endl;
	return 0;
}
