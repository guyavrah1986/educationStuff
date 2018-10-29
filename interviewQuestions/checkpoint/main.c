#include <stdio.h>
#include <limits.h>

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
	// the value of 10 as long as it contains only valid  decimal values
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

int main(int argc, char** argv)
{
	printf("main - start \n");

	const char arg1 [] = "123";
	int res = my_atoi1(arg1);
	printf("main - got back %d for the argument:%s \n", res, arg1);
	
	printf("main - end \n");
	return 0;
}
