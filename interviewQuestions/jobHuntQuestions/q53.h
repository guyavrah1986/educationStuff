#include <stdio.h>
#include <stdlib.h>

void* myMalloc(size_t size)
{
	unsigned char res = 16 - (size % 16);
	printf("myMalloc - ORIGINALLY got %lu bytes to allocate , ACTUALLY about to allocate %lu bytes using malloc \n", size, size + res);
	char* ret = (char*)malloc(sizeof(char) * (size + res));
	if (ret == NULL)
	{
		printf("myMalloc - was unable to allocate memory, returning NULL \n");
		return NULL;
	}

	printf("myMalloc - original address returned from malloc is:%p \n", ret);
	ret = ret + (res - 1);
	printf("myMalloc - forwarding ret to point to one byte before an alligned address:%p \n", ret);
	*ret = (res - 1);
	ret++;
	printf("myMalloc - FINALLY returning ret to point to:%p \n", ret);
	return (void*)ret;
}

void myFree(void* ptr)
{
	char* tmp = (char*)ptr;
	printf("myFree - ORIGNALLY got address:%p \n", tmp);
	tmp--;
	unsigned char res = *tmp;
	printf("myFree - extracted %d as the offest \n", res);
	tmp = tmp - res;
	printf("myFree - FINALLY ptr tmp points to:%p \n", tmp);
	free(tmp);
}


