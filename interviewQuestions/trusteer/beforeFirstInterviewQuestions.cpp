// #####################################################################################################
// #####################################################################################################
// Logistics: 
// ---------
// To compile this file into an executable (.exe on Windows):
// a) Navigate to the file's folder from the Developer Command Prompt for VS2017.
// b) Type the command: cl /EHsc fileName.cpp
// c) Run the fileName.exe for debugging.
//
//
// Questions:
// ----------
// 1) Given a string that holds 3 types of parantheses (opening and closing), find out whether it is 
//    legal, i.e.- every openning has a respective closing.
// 2) Reverse a string.
// 3) Givne a linked list, find the element in the middle of the list, i.e.- given 1-->2-->3-->4-->5
//    return element 3 (see solution under general questions on linked list topic).
// 4) You are given the following functions:
// a) void freeOs(void* ptr, size_t size);
// b) void* mallocOs(size_t size);
//    Implement the stadard malloc() and free() givne these two functions.
// 5) You have array with N numbers, remove all the elements in the array that have the vlaue M.
// 
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
	char* startStr = str;
	while (*startStr++ != '\0')
	{
		counter++;
	}
	
	startStr -= 2;
	char* endStr = startStr;
	startStr = str;
	unsigned int numIter = counter / 2;
	while (numIter-- > 0)
	{
		char currChar = *endStr;
		*endStr = *startStr;
		*startStr = currChar;
		startStr++;
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
	
	char str4 [] = "qwer";
}

// 4) this fuction "pretents" to replace the usual malloc
void* myMalloc(size_t size) 
{
	cout << "myMalloc - got size:" << size << ", sizeof(size_t):" << sizeof(size_t) << endl;
	// according to the question, this call should actually be to the provided fuction (see 4b)
	char* tmp = (char*)malloc(sizeof(size_t) + size);
	cout << "myMalloc - initially tmp is at address:" << static_cast<void*>(tmp) << endl;	
	*(size_t*)(tmp) = size;
	tmp += sizeof(size_t);
	cout << "myMalloc - after tmp += sizeof(size_t), tmp is at address:" << static_cast<void*>(tmp) << endl;
	return tmp;
}

void myFree(void* ptr)
{
	cout << "myFree - got ptr at address:" << static_cast<void*>(ptr) << endl;
	char* tmp = (char*)(ptr);
	tmp -= sizeof(size_t);	
	cout << "myFree - after (char*)(ptr) -= sizeof(size_t), ptr is at address:" << static_cast<void*>(tmp) << endl;
	// according to the question, this call should actually be to the provided fuction (see 4a)
	free(tmp);
}

void testQuestion4()
{
	cout << "testQuestion4 - start" << endl;
	void* ret = myMalloc(10);
	myFree(ret);
	cout << "testQuestion4 - end" << endl;
}

// 5)
size_t question5(int* arr, size_t arrLen, int numToRemove)
{
	cout << "question5 - start" << endl;
	size_t newArrIndex = 0;
	for (size_t i = 0; i < arrLen; ++i)
	{
		if (arr[i] != numToRemove)
		{
			arr[newArrIndex] = arr[i];
			newArrIndex++;	
		}
	}

	cout << "question5 - end" << endl;
	return newArrIndex;
}

void testQuestion5()
{
	cout << "testQuestion5 - start" << endl;
	int numToRemove = 3;
	size_t arrLen = 12;
	int arr [] = {1,3,4,2,3,5,6,3,1,2,9,89};
	cout << "testQuestion5 - BEFORE removing elements with value of:" << numToRemove << ", the original array is:" << endl;
	cout << "[";
	for (size_t i = 0; i < arrLen; ++i)
	{
		cout << arr[i] << " ";
	}

	cout << "]" << endl;
	size_t newArrLen = question5(arr, arrLen, numToRemove);
	cout << "testQuestion5 - AFTER removing elements with value of:" << numToRemove << ", the updated array is:" << endl;
	cout << "[";
	for (size_t i = 0; i < newArrLen; ++i)
	{
		cout << arr[i] << " ";
	}

	cout << "]" << endl;
	cout << "\n testQuestion5 - end" << endl;
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
	
	/*
	// 2) 
	testReverseString();
	*/

	/*
	// 4)
	testQuestion4();
	*/

	testQuestion5();
	
	cout << "main - end" << endl;
	return 0;
}
