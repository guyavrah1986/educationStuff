#ifndef NODE_H_
#define NODE_H_

#include <stdio.h>
#include <stdlib.h>

typedef struct Node Node;

struct Node 
{
	int data;
	Node* next;
};


Node* createNode(int data);
void deleteNode(Node* node);

#endif /*  NODE_H_ */
