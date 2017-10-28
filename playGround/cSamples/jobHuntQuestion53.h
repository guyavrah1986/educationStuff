
#include <stdio.h>
 #include <stdint.h>

// 1) Assuming size <= 512
// 2) Assuming malloc always success
void* OS_small_malloc(size_t size)
{
	void* ret = malloc(sizeof(char) * size);
	printf("OS_small_malloc - allocated %lu bytes \n",size);
	return ret;
}

// 1) Assuming size > 512
// 2) Assuming malloc always success
void* OS_large_malloc(size_t size)
{
	void* ret = malloc(sizeof(char) * size);
	printf("OS_large_malloc - allocated %lu bytes \n",size);
	return ret;
}


// a) Implement a new version of malloc that allocates size bytes, using the small and large 
//    malloc functions. Also, this malloc should always allocate memory in chuncks which are
//    multiple of 16.
//    Assumptions regarding the solution:
//    # after the addition of (base - residue) to the total size, we assume that the new size wont 
//   exceed the maximum value of size_t. 

// Notes about the solution:
// 1) In case residue is zero - than we add 16 bytes which are technically not needed.
//    This can be avoided by adding an if before the addition.
void* my_malloc(size_t size)
{
	void* ret = 0;
	static uint8_t base = 16;
	printf("my_malloc - got size:%lu \n",size);
	if (size == 0)
	{	
		return ret;
	}


	uint8_t residue = size % base;

	printf("my_malloc - residue is:%u \n", residue);	
	size += base - residue;	//1)

	if (size <= 512)
	{
		ret = OS_small_malloc(size);
	}
	else 
	{
		ret = OS_large_malloc(size);
	}

	return ret;
}

// b) implement the free method
void mY_free(void* p)
{
	if (p == 0)
	{
		printf("my_free - got NULL pointer\n");
		return;
	}

	free(p);
}

void question53UsageExample()
{
	size_t sizeToAllocate = 0;
	printf("question53UsageExample - try allocate 0 bytes \n");
	void* ret = my_malloc(sizeToAllocate);

	if (ret == 0)
	{
		printf("question53UsageExample - Got NULL pointer back from my_malloc() \n");
	}

	sizeToAllocate = 490;
	printf("question53UsageExample - try allocate %lu bytes \n", sizeToAllocate);
	ret = my_malloc(sizeToAllocate);

	sizeToAllocate = 512;
	printf("question53UsageExample - try allocate %lu bytes \n", sizeToAllocate);
	ret = my_malloc(sizeToAllocate);
	
}

