#include <stdio.h>
#include <stdlib.h>

#include "node.h"


struct node* createNode(int a)
{
	struct node* newNode = (struct node*)malloc(sizeof(struct node));
	newNode->val = a;
	newNode->next = NULL;
}

void deleteNode(struct node* n)
{
	if (n != NULL)
	{
		free(n);
	}
}

