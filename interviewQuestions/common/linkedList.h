#pragma once

#include "node.h"

struct node* createList();
void displayList(struct node* head);
void clearListRecursive(struct node* head);
void clearListLinear(struct node* head);
struct node* reverseLinkedListRecursive(struct node* head);
