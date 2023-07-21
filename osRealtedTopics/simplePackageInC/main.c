// main.c
include "include/myPackageObj.h"

int main(int argc, char** argv)
{
	printf("main - start\n");
	createFileWithTime();
	printf("File created successfully.\n");
	printf("main - end\n");
	return 0;
}
