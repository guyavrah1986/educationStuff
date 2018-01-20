/*
*  Given a string str (C-style string), write a function that reverse it (no extra memory is allowed).
*/


#include <iostream>

using namespace std;


void reverseString(char* str)
{
	cout << "reverseString - got original string:" << str << endl;
	char* end = str;	
	while(*end != '\0')
	{
		end++;
	}

	end--;
	char* start = str;
	
	printf("reverseString - before starting to reverse, start points to:%c , at address:%p \n", start[0], start);
	printf("reverseString - before starting to reverse, end points to:%c , at address:%p \n", end[0], end);

	// in case of an odd number of characters end & start will reach the same char
	// in the case of even number of charcters end & start will differ exactly by 1
	while (end - start > 1)
	{	
		printf("reverseString - start:%p , end:%p \n", start[0], end[0]);
		char tmp = *end;
		*end = *start;
		*start = tmp;
		end--;
		start++;
	}

	if (end == start)
	{
		return;
	}

	char tmp = *end;
	*end = *start;
	*start = tmp;
	return;
}


