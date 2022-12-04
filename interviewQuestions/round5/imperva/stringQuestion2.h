/*
* You are given two strings:
* str1 - holds a very large word.
* str2 - holds a list of letters (as a word). Each letter in str2 has to be remoed from str1.
* For example:
* str1 = "imperva security";
* str2 = "iea";
* output(modified str1): "mprv scurty"
* 
*
*/

#include <stdio.h>
#include <string.h>


char* removeLettersFromString(const char* str1, const char* str2)
{
	printf("removeLettersFromString - got str1:%s, str2:%s \n",str1, str2);
	
	// we need to allocate at most str1 length - cause we dont know in advance how many 
	// characters we are about to remove
	size_t lenStr1 = strlen(str1);
	char* res = (char*)malloc(lenStr1);
	memset((void *)res, 0, lenStr1);

	printf("removeLettersFromString - allocated:%d bytes for the result string \n", lenStr1);

	// Note 1: We are assuming only small letters in both strings

	// fill an array that indicates which letters are present
	// in str2.
	unsigned char lettersToRemove [26] = {0};
	size_t i, len = strlen(str2);	
	for (i = 0; i < len; ++i)
	{
		lettersToRemove[str2[i] - 'a'] = 1;
	}

	// for debug
	for (i = 0; i < 26; ++i)
	{
		if (lettersToRemove[i] == 1)
		{
			printf("removeLettersFromString - removing letter number:%d \n", i);
		}
	}

	// go over all the characters in the original str1 and "add" only
	// the characters which their corresponding entry in the indicator
	// array is not 1
	i = 0;
	while (*str1 != '\0')
	{
		if (lettersToRemove[*str1 - 'a'] != 1)
		{	
			printf("adding %c \n", *str1);
			res[i] = *str1;
			i++; 
		}
		str1++;
	}

	return res;
}



