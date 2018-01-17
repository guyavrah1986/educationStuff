/*
* Given an input string, return the index of the first character that DOES not show up more than one time in the entire string. 
* If no such character excists --> the function shall return -1.
*
*/

#include <stdio.h>


int findFirstCharThatAppearsOnlyOnce(const char* str)
{
	size_t strLen = 0;
	if (str == NULL)
	{
		printf("findFirstCharThatAppearsOnlyOnce - NULL string \n ");
		return -1;
	}

	char* tmp = (char*)str;	// eliminate constness...
	while (*tmp != NULL)
	{
		++strLen;
	}

	if (strLen == 1)
	{
		printf("findFirstCharThatAppearsOnlyOnce - single character string, returning 0...");
		return 0;
	}
	
	printf("findFirstCharThatAppearsOnlyOnce - got str:%s ",str);
}
