#include <iostream>

using namespace std;

void reverseString(char* str, size_t strLen)
{
	string funcName = "reverseString - ";
	cout << funcName + "got original string:" << str << endl;
	size_t numIterations = (strLen / 2);
	cout << funcName + "about to iterate for:" << numIterations << " in order to reverse it" << endl;
	for (size_t i = 0; i < numIterations; ++i)
	{
		char tmp = str[i];
		str[i] = str[strLen -1 - i];
		str[strLen -1 - i] = tmp;
	}
}

int main(int argc, char** argv)
{
	string funcName = "main - ";
	cout << funcName + "start" << endl;
	char str [] = "abcde";
	char reversedStr [] = "edcba";
	size_t strLen = sizeof(reversedStr) / sizeof(char) - 1;
	cout << funcName + "length of reversedStr is:" << strLen << " bytes" << endl;
	reverseString(str, strLen);
	cout << funcName + "after reversing it, str is:" << str << endl;
	for (size_t i = 0; i < strLen; ++i)
	{
		if (str[i] != reversedStr[i])
		{
			cout << funcName + "str[" << i << "] after reversing it, is invalid" << endl;
			return 1;
		}
	}


	cout << funcName + "reversed string correctly, it is now:" << str << endl;
	return 0;
}

