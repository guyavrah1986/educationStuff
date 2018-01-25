#include "../include/linkedList.h"


bool addNode(Node* toAdd, Node* root)
{
	if (toAdd == NULL)
	{
		return false;
	}

	if (root == NULL)
	{
		root = toAdd;
		toAdd->next = NULL;
		return true;	
	};

	while (root != NULL)
	{
		if (root->next == NULL)
		{
			root->next = toAdd;
			toAdd->next = NULL;
			return true;
		}

		root = root->next;
	}

	// if we got here is an invalid situation
	return false;	
}

bool removeNode(Node* toRemove)
{
	if (toRemove == NULL)
	{
		return false;
	}	
}

void displayList(Node* root)
{
	if (root == NULL)
	{
		return;
	}


	printf("displaying list: \n");
	printf("---------------- \n");
	
	while (root != NULL)
	{	
		printf("%d-->", root->data);
		root = root->next;
	}

	printf("NULL \n \n");	
}

void destroyList(Node* root)
{
	if (root == NULL)
	{
		return;
	}

	while (root != NULL)
	{
		Node* next = root->next;
		free(root);
		root = next;
	}
}



