// ########################################################################################################
// ########################################################################################################
//
// Questions:
// ----------
// 1) Given a C-Style string, verify if all characters from a given set are within it. In this case we
//    make sure that at least a one charater from the range [a-d] (inclusive) are present in the string.
// 
// ########################################################################################################
// ########################################################################################################
#include <iostream>
#include <stdio.h>

using namespace std;

// 1)
bool verifyAllCharactersAreInString(const char* str)
{
	cout << "verifyAllCharactersAreInString - start" << endl;
	if (str == NULL)
	{
		cout << "verifyAllCharactersAreInString - got NULL pointer" << endl;
		return false;
	}

	char* tmp = (char*)str;
	size_t counter = 0;	
	const size_t numOfCharsInRange = 4;
	const char range [numOfCharsInRange] = {'a','b','c','d'};
	char indicators [numOfCharsInRange] = {0};
	while (*tmp++ != '\0')
	{
		counter++;
	}

	if (counter < numOfCharsInRange)
	{
		cout << "verifyAllCharactersAreInString - string is too short to contain ALL possible characters in the range" << endl;
		return false;
	}

	cout << "verifyAllCharactersAreInString - got original string:" << str << endl;



	while (*str != '\0')
	{
		char currCharVal = *str - 'a';
		if (currCharVal >= 0 && currCharVal < numOfCharsInRange)
		{
			indicators[currCharVal] = 1;
		}	
		
		str++;
	}

	for (size_t i = 0; i < numOfCharsInRange; ++i)
	{
		if (indicators[i] != 1)
		{
			char nonExist = 'a' + i;
			cout << "verifyAllCharactersAreInString - character:" << nonExist << " does not exist in the string" << endl; 
			return false;
		}
	}

	return true;
	cout << "verifyAllCharactersAreInString - end" << endl;
}

void testQuestion1()
{
	cout << "testQuestion1 - start" << endl;
	bool res = verifyAllCharactersAreInString(0);
	if (res == true)
	{
		cout << "testQuestion1 - got an invalid return value" << endl;
		return;
	}

	const char str1 [] = "abcd";
	res = verifyAllCharactersAreInString(str1);
	if (res == false)
	{
		cout << "testQuestion1 - got an invalid return value" << endl;
		return;
	}

	const char str2 [] = "abc";
	res = verifyAllCharactersAreInString(str2);
	if (res == true)
	{
		cout << "testQuestion1 - got an invalid return value" << endl;
		return;
	}

	const char str3 [] = "abcc";
	res = verifyAllCharactersAreInString(str3);
	if (res == true)
	{
		cout << "testQuestion1 - got an invalid return value" << endl;
		return;
	}

	const char str4 [] = "aacd";
	res = verifyAllCharactersAreInString(str4);
	if (res == true)
	{
		cout << "testQuestion1 - got an invalid return value" << endl;
		return;
	}


	cout << "testQuestion1 - end" << endl;
}

// ===============================
// main
// ===============================

int main(int argc, char** argv)
{
	cout << "=============" << endl;
	cout << "main - start" << endl;
	cout << "=============" << endl;
	
	testQuestion1();

	cout << "=============" << endl;
	cout << "main - end" << endl;
	cout << "=============" << endl;	
	return 0;
}
