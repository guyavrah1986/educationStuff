#include <iostream>
#include <string.h>
#include <stdio.h>

using namespace std;

char* implementStrpbrk(const char* str, const char* matchedStr)
{
	if (str == NULL || matchedStr == NULL)
	{
		return NULL;
	}

	char* tmpStr = (char*)str;
	char* tmpMatchedStr = (char*)matchedStr;
	printf("str is:%s and matchedStr is:%s\n", tmpStr, tmpMatchedStr);
	while (*tmpMatchedStr != '\0')
	{
		printf("about to check if char:%c is present in string:%s\n", *tmpMatchedStr, tmpStr);
		while (*tmpStr != '\0')
		{
			printf("comparing *tmpStr:%c and *tmpMatchedStr:%c \n", *tmpStr, *tmpMatchedStr);
			if (*tmpStr == *tmpMatchedStr)
			{
				return tmpStr;
			}
			
			tmpStr++;
		}

		tmpStr = (char*)str;
		tmpMatchedStr++;
	}

	return NULL;
}

int main(int argc, char** argv)
{
	string funcName = "main - ";
	cout << funcName + "start" << endl;

	// test case #0: NULL input test case
	const char* str = NULL;
	const char* matchedStr = "abc";
	char* locationOfFirstMatch = implementStrpbrk(str, matchedStr);
	if (NULL != locationOfFirstMatch)
	{
		cout << funcName + "expected to get NULL, but did not" << endl;
		return 1;
	}


	// test case #1: return first character
	const char str1[] = "aergb";
	const char* locationAddress = &str1[0];
	printf("the address of the expected return pointer should be:%p\n", locationAddress);
	locationOfFirstMatch = implementStrpbrk(str1, matchedStr);
	printf("the location of the first match is:%p\n", locationOfFirstMatch);
	if (locationOfFirstMatch != locationAddress)
	{
		cout << funcName + "expected to get the following string:" << locationAddress << ", but did not. Got instead:" << locationOfFirstMatch << endl;
		return 1;
	}

	// test case #2: return last character
	const char str2[] = "iopjkb";
	locationAddress = &str2[5];
	printf("the address of the expected return pointer should be:%p, which has the char:%c \n", locationAddress, *locationAddress);
	locationOfFirstMatch = implementStrpbrk(str2, matchedStr);
	printf("the location of the first match is:%p which has the char:%c \n", locationOfFirstMatch, *locationOfFirstMatch);
	if (locationOfFirstMatch != locationAddress)
	{
		cout << funcName + "expected to get the following string:" << locationAddress << ", but did not. Got instead:" << locationOfFirstMatch << endl;
		return 1;
	}


	cout << funcName + "end" << endl;
	return 0;
}
