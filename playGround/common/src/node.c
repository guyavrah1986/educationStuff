#include "../include/node.h"


Node* createNode(int d)
{
	Node* node = (Node*)malloc(sizeof(Node));
	node->data = d;
	node->next = NULL;
}

void deleteNode(Node* node)
{
	if (node == NULL)
	{
		return;
	}

	free(node);
}
