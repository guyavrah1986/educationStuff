#include <iostream>

#include "../common/linkedList.h"
#include "../common/node.h"

using namespace std;


/*
  1-->2-->3-->4-->5-->NULL
*/
void removeNodeFromList(struct node* nodeToRemove)
{
	cout << "removeNodeFromList - about to remove node with val:" << nodeToRemove->val << endl;
	nodeToRemove->val = nodeToRemove->next->val;
	struct node* nodeToDelete = nodeToRemove->next;

	nodeToRemove->next = nodeToRemove->next->next; 
	deleteNode(nodeToDelete);
}

int main(int argc, char**argv)
{
	string funcName = "main - ";
	cout << funcName + "start" << endl;

	struct node* head = createList();
	cout << funcName + " created the following list:" << endl;
	displayList(head);
	struct node* nodeToRemove = head->next->next;
	removeNodeFromList(nodeToRemove);
	cout << funcName + "remove nodem updated list is:" << endl;
	displayList(head);
	cout << funcName + "end" << endl;
	return 0;
}

