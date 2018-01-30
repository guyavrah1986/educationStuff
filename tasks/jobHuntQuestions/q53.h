



void* myMalloc(size_t size)
{
	unsigned char res = 16 - (size % 16);
	printf("myMalloc - about to allocate %lu bytes using malloc \n", size + res);
	char* ret = (char*)malloc(sizeof(char) * (size + res));
	printf("myMalloc - original address returned from mallco is:%p \n", ret);
	ret = ret + (res - 1);
	printf("myMalloc - forwarding ret to point to one byte before an alligned address:%p \n", ret);
	
}
