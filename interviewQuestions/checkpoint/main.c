#include <stdio.h>

#include "linkedList.h"
#include "atoiQuestion.h"

int main(int argc, char** argv)
{
	printf("main - start \n");

	const char arg1 [] = "123";
	printf("main - my_atoi1 returned %d for the argument:%s \n", my_atoi1(arg1), arg1);
	printf("main - my_atoi2 returned %d for the argument:%s \n", my_atoi2(arg1), arg1);
	printf("main - my_atoi2 returned %d for the argument:%s \n", my_atoi2(NULL), "null string");


	struct node* n = createList();
	printf("main - end \n");
	return 0;
}
