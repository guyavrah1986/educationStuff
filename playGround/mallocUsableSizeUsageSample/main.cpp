#include <malloc.h>	// for malloc_usable_size function
#include <iostream>

using namespace std;

int main(int argc, char** argv)
{
	cout << "main - start" << endl;

	char* p = new char[10];
	size_t totalNumOfBytesAllocated = malloc_usable_size(p);
	cout << "main - totalNumOfBytesAllocated is:" << totalNumOfBytesAllocated << endl;
	delete [] p;


	p = (char*)malloc(sizeof(char) * 10);
	totalNumOfBytesAllocated = malloc_usable_size(p);
	cout << "main - totalNumOfBytesAllocated is:" << totalNumOfBytesAllocated << endl;
	free(p);
	
	cout << "main - end" << endl;
	return 0;
}
