#ifndef LINKED_LIST_H_
#define LINKED_LIST_H_

#include <stdio.h>
#include <stdbool.h>

#include "node.h"

bool addNode(Node* toAdd, Node* root);
bool removeNode(Node* toRemove);
void displayList(Node* root);
void destroyList(Node* root);


#endif /* LINKED_LIST_H_ */
