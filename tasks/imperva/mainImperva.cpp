

#include <iostream>
#include <stdint.h>

using namespace std;

#include "stringQuestion.h"
#include "structQuestion.h"
#include "stringQuestion2.h"

int main(int argc, char** argv)
{
	cout << "main - start \n \n" << endl;
	string str = "abcd";
	cout << str << " returned:"  << findFirstCharThatAppearsOnlyOnce(str.c_str()) << endl;
	str = "aabcd";
	cout << str << " returned:"  << findFirstCharThatAppearsOnlyOnce(str.c_str()) << endl;

	cout << "\n \n \n" << endl;
	structExample();

	cout << "\n \n \n" << endl;
	const char str1[] = "imperva security";
	const char str2[] = "iea";
	char* res = removeLettersFromString(str1, str2);
	cout << "main - removeLettersFromString(" << str1 << ", " << str2 << ") returned:" << res << endl;
	free(res);
	cout << "\n \n main - end" << endl;
	return 0;
}
