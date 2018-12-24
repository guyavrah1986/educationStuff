// ########################################################################################################
// ########################################################################################################
//
// Questions:
// ----------
// 1) Given a C-Style string, verify if all characters from a given set are within it. In this case we
//    make sure that at least a one charater from the range [a-d] (inclusive) are present in the string.
// 
// 2) Implement the C library function char* strcpy(char* dst, const char* src);
// Assumptions:
// a) The length of the src string is not more than SIZE_T_MAX.
// 
// 3) Given a "picutre" that is being hold by a two-dimenssional array, implement a "crop" function that
//    cropes a cetain part of that picture.
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

// 2)
char* myStrcpy(char* dst, const char* src)
{
	if (src == NULL || dst == NULL)
	{
		cout << "myStrcpy - got src and/or dst as NULL pointer, returning original dst" << endl;
		return dst;
	}

	size_t srcLen = 0;
	char* tmp = (char*)src;
	while (*src++ != '\0')
	{
		srcLen++;
	}

	// verify there is no "lapping" between the begining of dst 
	// to the begining of src
	return NULL;
}

void testQuestion2()
{
	cout << "testQuestion2 - start" << endl;

	cout << "testQuestion2 - end" << endl;
}

void crop(int* origArr, size_t origRows, size_t origCols, int* cropedArr, size_t startRow, size_t startCol,size_t numRowsToCrop, size_t numColsToCrop)
{
	if (cropedArr == NULL || origArr == NULL || origRows == 0 || origCols == 0  || numRowsToCrop == 0 || numColsToCrop == 0)
	{
		cout << "crop - invalid argument(s)" << endl;
		return;	
	}

	if (startRow + numColsToCrop > origCols)
	{
		cout << "crop - the desired croped array is out of bounds in the cols" << endl;
		return;
	}

	if (startCol + numRowsToCrop > origRows)
	{
		cout << "crop - the desired croped array is out of bounds in the rows" << endl;
		return;
	}

	size_t index = 0;
	for (size_t i = startRow, counterRow = 0; counterRow < numColsToCrop; ++i, ++counterRow)
	{
		for (size_t j = startCol, counterCol = 0; counterCol < numRowsToCrop; ++j, ++counterCol)
		{
			cropedArr[index++] = origArr[i][j];
		}
	}
}

void testQuestion3()
{
	cout << "testQuestion3 - start" << endl;
	const size_t rows = 5, cols = 5;	
	int arr [rows][cols];
	int counter = 1;
	for (size_t i = 0; i < rows; ++i)
	{
		for (size_t j = 0; j < cols; ++j)
		{
			arr[i][j] = counter++;	
		}
	}

	cout << "testQuestion3 - original array is:" << endl;
	for (size_t i = 0; i < rows; ++i)
	{
		for (size_t j = 0; j < cols; ++j)
		{
			cout << arr[i][j] << " ";	
		}
		
		cout << endl;
	}

	cout << "\n " << endl;
	int cropedArr[2][2] = {0};
	crop(&(arr[0][0]), rows, cols, &(cropedArr[0][0]), 1, 1, 2, 2);
	cout << "testQuestion3 - after croping the original array we get:" << endl;
	for (size_t i = 0; i < 2; ++i)
	{
		for (size_t j = 0; j < 2; ++j)
		{
			cout << cropedArr[i][j] << " ";	
		}
	}

	cout << "\n " << endl;
	cout << "testQuestion3 - end" << endl;
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
	testQuestion3();

	cout << "=============" << endl;
	cout << "main - end" << endl;
	cout << "=============" << endl;	
	return 0;
}
