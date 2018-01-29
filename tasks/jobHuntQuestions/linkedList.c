#include "node.h"

#include <stdlib.h>

struct node* createList()
{
	printf("createList - start \n");
	
	int v1 = 1;
	struct node* node1 = (struct node*)malloc(sizeof(struct node));
	struct node* origHead = node1;
	node1->val = v1;
		
	int v2 = 2;
	struct node* node2 = (struct node*)malloc(sizeof(struct node));
	node2->val = v2;
	node1->next = node2;

	int v3 = 3;
	struct node* node3 = (struct node*)malloc(sizeof(struct node));
	node3->val = v3;
	node2->next = node3;

	int v4 = 4;
	struct node* node4 = (struct node*)malloc(sizeof(struct node));
	node4->val = v4;
	node3->next = node4;
		
	int v5 = 5;
	struct node* node5 = (struct node*)malloc(sizeof(struct node));
	node5->val = v5;
	node4->next = node5;

	node5->next = NULL;
	return origHead;
}

void displayList(const struct node* head)
{
	printf("displayList - start \n");
	while (head != NULL)
	{
		printf("%d-->",head->val);
		head = head->next;
	}

	printf("NULL \n");
}

void clearListRecursive(const struct node* head)
{
	printf("clearListRecursive - start \n");
	
	if (head == NULL)
	{
		return;
	}
	
	if (head->next == NULL)
	{
		printf("clearListRecursive - freeing node with val:%d \n",head->val);
		free(head);
		return;
	}

	if (head->next != NULL)
	{
		clearListRecursive(head->next);
		printf("clearListRecursive - freeing node with val:%d \n",head->val);
		free(head);
		return;
	}
}

void clearListLinear(const struct node* head)
{
	printf("clearListLinear - start \n");

	struct node* tmp;
	while (head != NULL)
	{
		tmp = head->next;
		free(head);
		head = tmp;
	}
}

// for debug: 1-->2-->3-->4-->5-->NULL
//				NULL<--5
struct node* reverseLinkedListRecursive(const struct node* head)
{
	printf("reverseLinkedListRecursive - start \n");
	if (head == NULL)
	{
		return NULL;
	}
	
	if (head->next == NULL)
	{	
		printf("reverseLinkedListRecursive - got to the end of the list with head->val:%d \n", head->val);
		// head->next = head;
		return head->next;
	}

	// still have elements in the list
	struct node* ret = reverseLinkedListRecursive(head->next);
	ret->next = head;
	ret->next->next = NULL;
	return ret;
}



