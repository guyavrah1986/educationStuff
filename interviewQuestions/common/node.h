#pragma once

struct node
{
	int val;
	struct node* next;
};

struct node* createNode(int val);
void deleteNode(struct node* n);
