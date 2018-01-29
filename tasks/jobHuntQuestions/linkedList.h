#pragma once

#include "node.h"

struct node* createList();
void displayList(const struct node* head);
void clearListRecursive(const struct node* head);
void clearListLinear(const struct node* head);
