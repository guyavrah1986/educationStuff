#include <stdio.h>
#include <stdlib.h>

#include "iotaQuestion.h"

char* my_iota(int num)
{
	printf("my_iota - got num:%d \n", num);
	char* ret = (char*)malloc(sizeof(char) * MAX_DIGITS_INT);
	if (ret == NULL)
	{
		return NULL;
	}

	int isNegative = 0;
	if (num < 0)
	{
		num *= -1;
		isNegative = 1;
	}

	static const char arr [] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
	char tmp [MAX_DIGITS_INT] = {0};
	int index = 0;
	while ((num / 10) > 0)
	{
		printf("num:%d, num % 10 is:%d \n", num, num % 10);
		int residue = num % 10;
		tmp[index++] = arr[residue];
		num /= 10;
	}

	//num /= 10;
	printf("my_iota - num is:%d , index is:%d\n", num, index);
	tmp[index] = arr[num];
	char* p = ret;
	while (index >= 0)
	{
		printf("my_iota - tmp[%u]:%c \n", index, tmp[index]);
		*p = tmp[index];
		++p;
		--index;
	}
	
	*p = '\0';
	return ret;
}
