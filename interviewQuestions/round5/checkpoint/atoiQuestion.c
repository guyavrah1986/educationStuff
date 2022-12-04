#include <stdio.h>
#include <limits.h>

#include "atoiQuestion.h"

/*
* Assuming the numbers contains only decimal digits and a negative number is represented with a minus sign
* as the first character of the number and a positive number MIGHT be prefixed with a plus sign.
* In any other case, the function will return the LONG_MAX value to indicate an error.
* str - C style string (NULL terminated).
*/ 
int my_atoi1(const char* str)
{
	int sign = 1;
	const int multiplier = 10;
	int res = 0;
	if(str == NULL)
	{
		return INT_MAX;
	}

	// remove constnesses
	char* tmp = (char*)str;
	if (*tmp == '-')
	{
		printf("my_atoi1 - we got a negative number \n");
		sign = -1;
		++tmp;
	}

	if (*tmp == '+')
	{
		printf("my_atoi1 - we got a positive number \n");
		++tmp;
	}

	// first digit is "out of the loop" yet we must perform
	// all validation tests
	if (*tmp == '\0')
	{
		return INT_MAX;
	}

	unsigned char currChar = *tmp;
	if (currChar < '0' || currChar > '9')
	{
		printf("my_atoi1 - got an invalid character %c, returning an error \n", currChar);
		return 	INT_MAX;
	}

	res += currChar - '0';
	++tmp;

	// now we continue to "parse" the number with "constant multipiler" with
	// the value of 10 as long as it contains only valid decimal values
	while(*tmp != '\0')
	{
		currChar = *tmp;
		if (currChar < '0' || currChar > '9')
		{
			printf("my_atoi1 - got an invalid character %c, returning an error \n", currChar);
			return 	INT_MAX;
		}

		// for debug:
		printf("my_atoi1 - current character is:%c with its decimal value of:%d, res is:%d, multiplier is:%d \n", currChar, currChar - '0', res, multiplier);
		int tmpVal = (res * multiplier) + (currChar - '0');
		if (tmpVal > INT_MAX)
		{
			printf("my_atoi - we are about to cause overflow, returning an error \n");
			return INT_MAX;
		}

		res = tmpVal;
		++tmp;
	}

	return res * sign;
}

int my_atoi2(const char* c)
{
	int value = 0;
	int sign = 1;

	if (c == NULL)
	{
		printf("my_atoi2 - got NULL string, returning error \n");
		return INT_MAX;
	}
	
	if(*c == '+' || *c == '-')
	{
		if(*c == '-') 
		{
			sign = -1;
		}

		c++;
	}

	while ((*c >= '0' && *c <= '9'))
	{
		// check for overflow
		long long int tmpVal = (value * 10) + (int)(*c-'0');
		if(tmpVal > INT_MAX)
		{
			break;
		}

		value *= 10;
		value += (int) (*c-'0');
		c++;
	}

	if (*c == '\0')
	{
 		return (value * sign);
	}

	return INT_MAX;
}
