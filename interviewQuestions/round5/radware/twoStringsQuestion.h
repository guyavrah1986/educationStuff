// ============================================================================================================================================================================
/*
* Given two C style strings that contains any of the ASCII characters, return the total amount of appearences of each character
* in str2 minues the number of times it appears in str1.
* For example:
* str1= "aabbccde"
* str2= "abbbcc"
* --> the output will be: 1 (for a) + 2 (for b) 1 (for c) == 4	
*
*/
// ============================================================================================================================================================================

#include <iostream>

using namespace std;

void disaplyArr(const int* arr, size_t size)
{
	for (size_t i = 0; i < size; ++i)
	{
		if (arr[i] != 0)
		{
			cout << "arr[" << i << "]:" << arr[i] << " " << endl;
		}
	}
}

size_t numOfCharsAppearences(const char* str1, const char* str2)
{
	cout << "numOfCharsAppearences - got str1:" << str1 << " and str2:" << str2 << endl;
	const size_t arrSize = 256;
	int charsInStr2 [arrSize] = {0};

	// for each character in str2 --> increment the "respective" array cell by 1
	char* tmp = (char*)str2;
	while (*tmp != '\0')
	{
		charsInStr2[*tmp] += 1;
		++tmp;
	}

	cout << "numOfCharsAppearences - after incrementing according to the number of appearences in str2, the respective array is:" << endl;
	disaplyArr(charsInStr2, arrSize);

	// TODO: now, do the same for the seonds string, and decrement by 1 each "respective" cell untill it reaches zero
	

	// TODO: finally sum all cells of charsInStr2 array and return its value.
	size_t ret = 0;	
	for (size_t i = 0; i < arrSize; ++i)
	{
		ret += charsInStr2[i];
	} 
	
	return ret;
}

void twoStringsExample1()
{
	const char str1 [] = "aabbccde";
	const char str2 [] = "abbbcc";
	cout << "numOfCharsAppearences returned:" << numOfCharsAppearences(str1, str2) << endl;
}




