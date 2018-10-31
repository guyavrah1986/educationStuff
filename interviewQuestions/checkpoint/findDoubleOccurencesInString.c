#include <stdio.h>

#include "findDoubleOccurencesInString.h"
#define NUM_OF_DIGITS 26

void findAllOccurencesForEachChar(const char* str)
{
	if (str == NULL)
	{
		printf("findAllOccurencesForEachChar - got a NULL string: \n");
		return;
	}


	printf("findAllOccurencesForEachChar - got the string:%s \n", str);
	unsigned int occurences [NUM_OF_DIGITS] = {0};
	// ASCII value for 'a' is 97
	while (*str != '\0')
	{
		char currChar = *str;
		char currIndex = currChar - 'a';
		if (currIndex <= NUM_OF_DIGITS && currIndex >= 0)
		{
			occurences[currIndex]++;
		}
		else
		{
			printf("findAllOccurencesForEachChar - character:%c is not in the valid range of characters \n", currChar);
		}

		str++;
	}

	size_t i;
	for (i = 0; i < NUM_OF_DIGITS; ++i)
	{
		printf("occurences[%u]:%u \n", i, occurences[i]);
	}
}
