#include <stdint.h>
#include <stdlib.h>

#include "linkedList.h"

void q2()
{
	printf("q2 - start\n");
	struct node* head1 = createList();
	printf("q2 - display list originaly\n");
	displayList(head1);
	printf("q2 - display list after reversing it\n");
	reverseLinkedListIterative(&head1);
	displayList(head1);
	clearListLinear(head1);
	printf("\n \nq2 - end\n");	
}

int main(int argc, char** argv)
{
	printf("main - start\n");
	q2();
	printf("main - end\n");
	return 0;
}
