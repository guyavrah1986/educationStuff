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

int verifyParantheses(const char* str)
{
	if (str == NULL)
	{
		printf("verifyParantheses - invalid pointer\n");
		return 1;
	}
	
	const char* tmp = str;
	unsigned int len = 0;
	while (tmp != '\0')
	{
		len++;
		tmp++;
	}
	
	if ((len % 2) != 0)
	{
			printf("verifyParantheses - odd number of characters in the input string, no need to further check\n");
			return 1;
	}
	
	printf("verifyParantheses - got the original string:%s \n", str);
	
	// if we got here the string is valid
	printf("verifyParantheses - valid input string\n");
	return 0;
}

// ===============================
// main
// ===============================

int main(int argc, char** argv)
{
	cout << "main - start" << endl;
	
	const char paranthesses1 [] = "{()}";
	verifyParantheses(paranthesses1);
	
	
	cout << "main - end" << endl;
	return 0;
}