#include <stdio.h>

#include "findLoopInALinkedList.h"

// https://www.ideserve.co.in/learn/detect-a-loop-in-a-linked-list

struct node* findLoopInLinkedList(struct node* head)
{
	printf("findLoopInLinkedList - start \n");

	if (head == NULL)
	{
		printf("findLoopInLinkedList - got a NULL pointer \n");
		return NULL;
	}

	struct node* p1 = head;
	struct node* p2 = head;
	do
	{
		printf("findLoopInLinkedList - first loop, p1->val:%d , p2->val:%d \n", p1->val, p2->val);
		p1 = p1->next;
		p2 = p2->next;
		p2 = p2->next;
	}
	while (p1 != NULL && p2 != NULL && p1 != p2);

	// no loop
	if (p1 == NULL || p2 == NULL)
	{
		printf("findLoopInLinkedList - no loop was found in list - returning a NULL pointer \n");
		return NULL;
	}

	// there is a loop
	p1 = head;
	while (p1 != p2)
	{
		printf("findLoopInLinkedList - second loop, p1->val:%d , p2->val:%d \n", p1->val, p2->val);
		p1 = p1->next;
		p2 = p2->next;
	}

	return p1;
}
