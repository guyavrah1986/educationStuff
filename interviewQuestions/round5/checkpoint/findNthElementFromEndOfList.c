#include <stdio.h>

#include "findNthElementFromEndOfList.h"


/*
* An important assumption here is that the list has indeed at least K+1 elements in total
*/
struct node* findNthElementFromTheEndOfTheList(const struct node* head, int k)
{
	printf("findNthElementFromTheEndOfTheList - start \n");

	if (head == NULL)
	{
		printf("findNthElementFromTheEndOfTheList - got a NULL pointer \n");
		return NULL;
	}

	struct node* p1 = head;
	struct node* p2 = head;

	// first move p1 k nodes from the head
	int tmp = k;
	while (tmp > 0)
	{
		p1 = p1->next;
		--tmp;
	}

	while (p1->next != NULL)
	{
		p1 = p1->next;
		p2 = p2->next;
	}

	return p2;
}
