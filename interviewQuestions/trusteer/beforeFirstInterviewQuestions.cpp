// #####################################################################################################
// #####################################################################################################
// Logistics: 
// ---------
// To compile this file into an executable (.exe on Windows):
// a) Navigate to the file's folder from the Developer Command Prompt for VS2017.
// b) Type the command: cl /EHsc fileName.cpp
// c) Run the fileName.exe for debugging.

// #####################################################################################################
// #####################################################################################################
#include <iostream>
#include <stdio.h>

using namespace std;

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

// ===============================
// main
// ===============================

int main(int argc, char** argv)
{
	cout << "main - start" << endl;
	
	const char paranthesses1 [] = "{()}";
	testParanthesesSolutionVer1();
	verifyParanthesesVer1(paranthesses1);
	
	
	cout << "main - end" << endl;
	return 0;
}
