#include <stdio.h>
#include <stdint.h>

#include "linkedList.h"
#include "atoiQuestion.h"
#include "findLoopInALinkedList.h"
#include "iotaQuestion.h"
#include "findDoubleOccurencesInString.h"
#include "findNthElementFromEndOfList.h"
#include "removeWhiteSpacesFromStr.h"
#include "reachEndOfTwoDimMatrix.h"

// ===========================================================================================================================
// ===========================================================================================================================
/*
* What does this function do ? What is the bug  and how can we fix it ?
* 
* Some context: In a proper usage of this function, the same mask should be called in consucutives calls over and over again. 
*/
// ===========================================================================================================================
// ===========================================================================================================================

static int function(uint64_t make)
{ 
	int inst, position, items, i;
	uint64_t temp_mask = make;
	static int curr;

	while (temp_mask)
	{
		if (temp_mask & 0x1)
		{
			items++;
		}
	
		temp_mask = temp_mask >> 1;
	}

	position = curr;
	position = position % items;
	position++;
	curr++;
	inst = 0;
	temp_mask = make;
	while (temp_mask)
	{
		if (temp_mask & 0x1)
		{
			position--;
			if (!position)
			{
				break;
			}
			
			temp_mask = temp_mask >> 1;
			inst++;
	}

	return inst; 
} 

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

void callReverseLinkedListIterative()
{
	printf("callReverseLinkedListIterative - start \n");
	struct node* head = createList();
	printf("callReverseLinkedListIterative - before reversing the linked list \n");
	displayList(head);
	reverseLinkedListIterative(&head);
	printf("callReverseLinkedListIterative - after reversing the linked list \n");
	displayList(head);
	clearListLinear(head);
}

void callFindAllOccurencesForEachChar()
{
	printf("callFindAllOccurencesForEachChar - start \n");
	findAllOccurencesForEachChar("");
	findAllOccurencesForEachChar(NULL);
	findAllOccurencesForEachChar("abcdef");
	findAllOccurencesForEachChar("abcdefabcde");
	findAllOccurencesForEachChar("abcdefEW#@../");
}

void callFindNthElementFromTheEndOfTheList()
{
	printf("callFindNthElementFromTheEndOfTheList - start \n");
	struct node* head = createList();
	printf("callFindNthElementFromTheEndOfTheList - before the given linked list is: \n");
	displayList(head);
	struct node* ret = findNthElementFromTheEndOfTheList(head, 2);
	if (ret != NULL)
	{
		printf("callFindNthElementFromTheEndOfTheList - node's value that was returned from function is:%d \n", ret->val);
	}

	clearListLinear(head);
}

void callRemoveWhiteSpacesFromString()
{
	char str [] = "abc  abc";
	printf("callRemoveWhiteSpacesFromString - original string:%s \n", str);
	removeSpaces(str);
	
	printf("callRemoveWhiteSpacesFromString - after removing white spaces the string is:%s \n", str);
}

void callNumOfPathsToEndOfTwoDimMatrix()
{
	printf("callNumOfPathToEndOfTwoDimMatrix - start \n");
	int n = 3;
	int m = 3;
	printf("numOfPathsToEndOfTwoDimMatrix(0,0, %d, %d) returned:%d \n",n, m, numOfPathsToEndOfTwoDimMatrix(0,0, n,m));
}

// ===================================================================================================================
int main(int argc, char** argv)
{
	printf("main - start \n");

	//callItoaFunc();
	//callReverseLinkedListIterative();
	//callFindAllOccurencesForEachChar();
	//callFindNthElementFromTheEndOfTheList();
	//callRemoveWhiteSpacesFromString();


	callNumOfPathsToEndOfTwoDimMatrix();


	printf("main - end \n");
	return 0;
}
