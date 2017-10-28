// =========================================================================================================================================================
// Question 51:
// ------------
// Given a linked list and a pointer to a node in the list, write a fucntion that removes the node using only the pointer to that node.
// 
// =========================================================================================================================================================

#include "common/include/linkedList.h"

Node* prepareLinkedList()
{
	// create a linked list

	int rootData = 1;
	Node* root = createNode(rootData);
	printf("prepareLinkedList - created the root of the linked list with value:%d \n", root->data);

	// add nodes
	bool added = false;	
	int secondNode = 2;
	Node* nodeToAdd = createNode(secondNode);
	added = addNode(nodeToAdd, root);

	int thirdNode = 3;
	nodeToAdd = createNode(thirdNode);
	added = addNode(nodeToAdd, root);

	int fourthNode = 4;
	nodeToAdd = createNode(fourthNode);
	added = addNode(nodeToAdd, root);

	int fifthNode = 5;
	nodeToAdd = createNode(fifthNode);
	added = addNode(nodeToAdd, root);

	displayList(root);

	return root;
}

void removeNodeWhichIsNotLast(Node* toRemove)
{
	Node* tmp = toRemove->next;
	toRemove->data = toRemove->next->data;
	toRemove->next = toRemove->next->next;
	free(tmp);
}

void jobHuntQuestion51Usage()
{
	printf("jobHuntQuestion51Usage - start \n");
	Node* root = prepareLinkedList();

	Node* nodeToRemove = root->next->next;
	printf("jobHuntQuestion51Usage - about to remove node with data:%d \n", nodeToRemove->data);
	removeNodeWhichIsNotLast(nodeToRemove);

	printf("after removal the list \n");
	displayList(root);

	printf("jobHuntQuestion51Usage - destroying list\n");
	destroyList(root);
	printf("jobHuntQuestion51Usage - start \n");
}


