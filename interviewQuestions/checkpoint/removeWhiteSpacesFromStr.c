#include <stdio.h>

#include "removeWhiteSpacesFromStr.h"

void removeSpaces(char *str) 
{ 
	unsigned int i, count = 0;
	for (i = 0; str[i]; ++i) 
	{
        	if (str[i] != ' ') 
            	{	
			str[count++] = str[i]; 
		}
	}

	str[count] = '\0'; 
} 
