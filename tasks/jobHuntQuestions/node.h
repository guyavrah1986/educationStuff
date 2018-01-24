#pragma once

struct node
{
	int val;
	struct node* next;
};

node* createNode(int val);

