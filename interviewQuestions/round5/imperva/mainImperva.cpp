#include <iostream>
#include <stdint.h>

#include "stringQuestion.h"
#include "structQuestion.h"
#include "stringQuestion2.h"
#include "decoratorExample.h"
#include "reverseString.h"

using namespace std;

void firstStringQuestion()
{
	string str = "abcd";
	cout << str << " returned:"  << findFirstCharThatAppearsOnlyOnce(str.c_str()) << endl;
	str = "aabcd";
	cout << str << " returned:"  << findFirstCharThatAppearsOnlyOnce(str.c_str()) << endl;
	str = "aabbcc";
	cout << str << " returned:"  << findFirstCharThatAppearsOnlyOnce(str.c_str()) << endl;
}

void secondStringQuestion()
{
	const char str1[] = "imperva security";
	const char str2[] = "iea";
	char* res = removeLettersFromString(str1, str2);
	cout << "main - removeLettersFromString(" << str1 << ", " << str2 << ") returned:" << res << endl;
	free(res);
}

void reverseStringQuestion()
{
	char str1[] = "abcde";
	reverseString(str1);
	cout << "main - after reversing string:" << str1 << endl;

	char str2[] = "guya";
	reverseString(str2);
	cout << "main - after reversing string:" << str2 << endl;
}

int main(int argc, char** argv)
{
	cout << "main - start \n \n" << endl;

	
	// 1) 
	firstStringQuestion();
	cout << "\n \n \n" << endl;

	// 2) 
	secondStringQuestion();
	cout << "\n \n \n" << endl;

	// 3)
	structExample();
	cout << "\n \n \n" << endl;
	
	// 4)
	decoratorExample();

	// 5) 
	reverseStringQuestion();


	cout << "\n \n main - end" << endl;
	return 0;
}
