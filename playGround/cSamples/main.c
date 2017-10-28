
#include "common/include/linkedList.h"
#include "jobHuntQuestion51.h"
#include "jobHuntQuestion53.h"
#include "pointersSummary.h"

// =============================================================================================================================================================



void linkedListUsageExample()
{
	int rootData = 1;
	Node* root = createNode(rootData);
	printf("linkedListUsageExample - created the root of the linked list with value:%d \n", root->data);

	// add nodes
	bool added = false;	
	int secondNode = 2;
	Node* nodeToAdd = createNode(secondNode);
	added = addNode(nodeToAdd, root);

	int thirdNode = 3;
	nodeToAdd = createNode(thirdNode);
	added = addNode(nodeToAdd, root);

	// display linked list
	displayList(root);

	printf("linkedListUsageExample - deleting the the linked list \n");
	destroyList(root);
}

// =============================================================================================================================================================

void pointersExample()
{
	printf("pointersExample - start\n");
	checkBigOrLittleEndian();

	accessingViaCharPointer();

	structureExample();

	functionPointerExample();

	printf("pointersExample - end\n");
}

// =============================================================================================================================================================

void main()
{
	printf("main -start \n \n");

	linkedListUsageExample();
	jobHuntQuestion51Usage();


	question53UsageExample();

	pointersExample();
	

	printf("\n \n main - end \n");
}
