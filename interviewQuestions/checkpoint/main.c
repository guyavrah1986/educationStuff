#include <stdio.h>

#include "linkedList.h"
#include "atoiQuestion.h"
#include "findLoopInALinkedList.h"
#include "iotaQuestion.h"

void callAtoiFunc()
{
	printf("callAtoiFunc - start \n");
	const char arg1 [] = "123";
	printf("main - my_atoi1 returned %d for the argument:%s \n", my_atoi1(arg1), arg1);
	printf("main - my_atoi2 returned %d for the argument:%s \n", my_atoi2(arg1), arg1);
	printf("main - my_atoi2 returned %d for the argument:%s \n", my_atoi2(NULL), "null string");
}

void callFindLoopInLinkedList()
{
	printf("callFindLoopInLinkedList - start \n");
	struct node* head = createLinkedListWithInnerLoop();
	struct node* loopedNode = findLoopInLinkedList(head);
	if (loopedNode == NULL)	
	{
		printf("main - no loops were detected in linked list \n");
	}
	else
	{
		printf("main - loop was detected in node with val:%d \n", loopedNode->val);
	}
}

void callItoaFunc()
{
	printf("callItoaFunc - start \n");
	int num = 1234;
	char* ret = my_iota(num);
	printf("callItoaFunc - for num:%d, got the string:%s \n",num, ret);
}

int main(int argc, char** argv)
{
	printf("main - start \n");

	callItoaFunc();
	printf("main - end \n");
	return 0;
}
