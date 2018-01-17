/*
* Given an input string, return the index of the first character that DOES not show up more than one time in the entire string. 
* If no such character excists --> the function shall return -1.
*
*/

#include <stdio.h>
#include <string.h>

struct charInfo
{
	size_t numOfAppearences;
	size_t firstAppearIndex;
};

int findFirstCharThatAppearsOnlyOnce(const char* str)
{
	size_t strLen = 0;
	if (str == NULL)
	{
		printf("findFirstCharThatAppearsOnlyOnce - NULL string \n ");
		return -1;
	}

	strLen = strlen(str);
	printf("findFirstCharThatAppearsOnlyOnce - got str:%s \n",str);
	if (strLen == 1)
	{
		printf("findFirstCharThatAppearsOnlyOnce - single character string, returning 0...");
		return 0;
	}

	// a -z [97 - 122]
	// A- Z [65 - 90]
	// define an array in the size of the ABC (capital and small leterrs) in a way that 
	// each cell will hold the amount of times the "respective" letter appeared in the 
	// original string and the index of that first appearence
	charInfo charArr [26];
	for (size_t i = 0; i < 26; ++i)
	{
		charArr[i].numOfAppearences = 0;
		charArr[i].firstAppearIndex = -1;
	}

	// for each character in the string, update its respective cell in the array of chars
	for (size_t i = 0; i < strLen; ++i)
	{
		uint8_t currCharVal = str[i];
		printf("findFirstCharThatAppearsOnlyOnce - current char value is:%d \n ", currCharVal);
		if (currCharVal >= 65 && currCharVal <= 90)
		{		
			currCharVal += 32;
			printf("findFirstCharThatAppearsOnlyOnce - normalazing it to:%d \n ", currCharVal);
		}
	
		// this way we ensure that only the first appearence of the character will	
		// be noted.
		charArr[currCharVal - 97].numOfAppearences++;
		if (charArr[currCharVal - 97].numOfAppearences == 1 && charArr[currCharVal - 97].firstAppearIndex == -1)
		{
			printf("findFirstCharThatAppearsOnlyOnce - current char value is:%d appeared for the first time\n ", currCharVal);
			charArr[currCharVal - 97].firstAppearIndex = i;		
		}
	}
	
	// due to the fact that we need to provide the FIRST (!!) character that appears only once, 
	// we will return the index of a cell that has the minimum value (which is not -1)
	int min = charArr[0].firstAppearIndex;	
	for (size_t i = 1; i < strLen; ++i)
	{
		if (charArr[i].firstAppearIndex < min && charArr[i].numOfAppearences == 1)
		{
			charArr[i].firstAppearIndex = min;
		}
	}

	return min;
}


