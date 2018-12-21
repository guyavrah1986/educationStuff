// #####################################################################################################
// #####################################################################################################
// Logistics: 
// ---------
// To compile this file into an executable (.exe on Windows):
// a) Navigate to the file's folder from the Developer Command Prompt for VS2017.
// b) Type the command: cl /EHsc fileName.cpp
// c) Run the fileName.exe for debugging.


// Questions:
// ----------
// 1) Given a string that holds 3 types of parantheses (opening and closing), find out whether it is 
//    legal, i.e.- every openning has a respective closing.
// 2) Reverse a string.

// #####################################################################################################
// #####################################################################################################
#include <iostream>
#include <stdio.h>

using namespace std;

// 1)
int verifyParanthesesVer1(const char* str)
{
	if (str == NULL)
	{
		printf("verifyParanthesesVer1 - invalid pointer, aborting\n");
		return 1;
	}
	
	const char* tmp = str;
	unsigned int len = 0;
	while (*tmp != '\0')
	{
		len++;
		tmp++;
	}
	
	if ((len % 2) != 0)
	{
		printf("verifyParanthesesVer1 - odd number of characters in the input string, no need to further check, aborting\n");
		return 1;
	}
	
	printf("verifyParanthesesVer1 - got the original string:%s \n", str);

	// we excpet to have exactly len/2 "opennings" paranthesses (i.e.- '{','(' or '[')
	// so allocate exactly this amount of memory in the "stack data structure" that will 
	// help us keep track of them.
	int stackLen = len / 2;
	int stackPointer = -1;
	unsigned int iterNum = 0;
	char* stack = (char*)malloc(sizeof(char) * stackLen);

	tmp = str;
	tmp--;	
	while (*(++tmp) != '\0')
	{
		// for debug
		printf("===================================== \n");
		printf("verifyParanthesesVer1 - iteration %u \n", ++iterNum);
		if (stackPointer > stackLen)
		{
			printf("verifyParanthesesVer1 - we encountered too many openning paranthses, aborting \n");
			break;
		}
			
		printf("verifyParanthesesVer1 - currently processing element:%c \n", *tmp);
		if (*tmp == '{' || *tmp == '[' || *tmp == '(')
		{
			stackPointer++;
			stack[stackPointer] = *tmp;
			continue;
		}

		if (stackPointer < 0)
		{
			printf("verifyParanthesesVer1 - invalid situation, not enough openning parantheses\n");
			break;
		}

		if (*tmp == '}')
		{
			if (stack[stackPointer] == '{')
			{
				printf("verifyParanthesesVer1 - encountered with }, and the last opening was {, keep on verifying the string \n");
				stackPointer--;
				continue;
			}

			printf("verifyParanthesesVer1 - encountered with }, and the last opening was NOT {, aborting \n");
			break;
		}
		else if (*tmp == ')')
		{
			if (stack[stackPointer] == '(')
			{
				printf("verifyParanthesesVer1 - encountered with ), and the last opening was (, keep on verifying the string \n");
				stackPointer--;
				continue;
			}

			printf("verifyParanthesesVer1 - encountered with ), and the last opening was NOT (, aborting \n");
			break;
		}
		else if (*tmp == ']')
		{
			if (stack[stackPointer] == '[')
			{
				printf("verifyParanthesesVer1 - encountered with ], and the last opening was [, keep on verifying the string \n");
				stackPointer--;
				continue;
			}

			printf("verifyParanthesesVer1 - encountered with ], and the last opening was NOT [, aborting \n");
			break;
		}
		else
		{
			printf("verifyParanthesesVer1 - invalid character, aborting \n");
			break;
		}

		printf("===================================== \n");
		printf(" \n \n");
	}

	// de-allocate the memory that was used for the stack
	free(stack);
	if (*tmp != '\0' || stackPointer != -1)
	{
		printf("verifyParanthesesVer1 - the string is invalid !!\n");
		return 1;
	}
	
	// if we got here the string is valid
	printf("verifyParanthesesVer1 - valid input string\n");
	return 0;
}

void testParanthesesSolutionVer1()
{
	const char* str = NULL;
	int res = verifyParanthesesVer1(str);
	if (res == 0)
	{
		printf("testParanthesesSolutionVer1 - got invalid result for string:%s \n", str);
		return;
	}

	const char str1 [] = "{[]}(";
	res = verifyParanthesesVer1(str1);
	if (res == 0)
	{
		printf("testParanthesesSolutionVer1 - got invalid result for string:%s \n", str1);
		return;
	}

	const char str2 [] = "{{%}";
	res = verifyParanthesesVer1(str2);
	if (res == 0)
	{
		printf("testParanthesesSolutionVer1 - got invalid result for string:%s \n", str2);
		return;
	}

	const char str3 [] = ")()(";
	verifyParanthesesVer1(str3);
	if (res == 0)
	{
		printf("testParanthesesSolutionVer1 - got invalid result for string:%s \n", str3);
		return;
	}
	
	printf("testParanthesesSolutionVer1 - ALL test cases went well !! \n");
}

// 2)
void reverseString(char* str)
{
	if (str == NULL)
	{
			printf("reverseString - got NULL pointer \n");
			return;
	}
	
	printf("reverseString - got the original string:%s \n", str);
	// abc --> cba
	unsigned int counter = 0;
	char* tmp = str;
	while (*tmp++ != '\0')
	{
		counter++;
	}
	
	char* endStr = --tmp;
	tmp = str;
	printf("reverseString - after counting num of characters, tmp points to:%s \n", tmp);
	
	// for debug
	unsigned int numIter = counter / 2;
	while (numIter-- > 0)
	{
		char currChar = *endStr;
		*endStr = *tmp;
		*tmp = currChar;
		tmp++;
		endStr--;
	}
	
	printf("reverseString - done reversing the string which is now:%s \n", str);
}

void testReverseString()
{
	printf("testReverseString - start \n");
	char* str1 = 0;
	
	char str2 [] = "abc";
	reverseString(str2);
	printf("testReverseString - after str2 is:%s \n", str2);
	
	char str3 [] = "bnmk";
	reverseString(str3);
	printf("testReverseString - after str3 is:%s \n", str3);
}


// ===============================
// main
// ===============================

int main(int argc, char** argv)
{
	cout << "main - start" << endl;
	
	/*	// 1)
	const char paranthesses1 [] = "{()}";
	testParanthesesSolutionVer1();
	verifyParanthesesVer1(paranthesses1);
	*/
	
	// 2) 
	testReverseString();
	
	cout << "main - end" << endl;
	return 0;
}
