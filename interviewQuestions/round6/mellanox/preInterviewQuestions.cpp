/*
List of potential questions:
============================
1) Find loop in a list.
2) Sort an array of integers such that all zeros will be on the right side of the array, for example:
{1, 2, 0, 3, 0, 4, 5, 6} --> {1, 2, 3, 4, 5, 6, 0, 0}

*/
#include <iostream>

#include "common/linkedList.h"
#include "common/node.h"

using namespace std;

/*
1)

1-->2--3-->4-->5-->3
*/
bool findLoopInLinkedList(struct node* head)
{
	string funcName = "findLoopInLinkedList - ";
	if (NULL == head || NULL == head->next)
	{
		cout << funcName + "head is NULL, head->next is NULL" << endl;
		return false;
	}

	struct node* tmp1 = head;
	struct node* tmp2 = head->next;
	while (NULL != tmp1 && NULL != tmp2)
	{
		if (tmp1 == tmp2)
		{
			cout << funcName + "found a loop" << endl;
			return true;
		}
		
		tmp1 = tmp1->next;
		tmp2 = tmp2->next->next;
	}
	
	return false;
}

/*
2) Re-order array with zeros.
*/
void reorderArrayWithZeros(int* arr, size_t arrSize)
{
	string funcName = "reorderArrayWithZeros - ";
	if (NULL == arr || 0 == arrSize)
	{
		cout << funcName + "arr is NULL or the array size is zero" << endl;
		return;
	}

	/*

	size_t leftIndex = 0;
	size_t rightIndex = arrSize - 1;
	while (leftIndex < rightIndex)
	{
		if (arr[leftIndex] != 0)
		{
			++leftIndex;
			continue;
		}

		while (0 == rightIndex)
		{
			--rightIndex;
		}

		// rightIndex points to the array location in which the "current" zero is 
		// to be inserted
		int tmp = arr[rightIndex];
		arr[rightIndex] = arr[leftIndex];
		arr[leftIndex] = tmp;
		--rightIndex;
	}
	*/

	 // endOfNonZero stores index of next available position
	size_t endOfNonZero = 0;
	size_t i;
	for (i = 0; i < arrSize; i++)
	{
		// if current element is non-zero, put the element at
		// next free position in the array
		if (arr[i] != 0)
		{
		    arr[endOfNonZero++] = arr[i];
		}
	}
	
	// move all 0's to the end of the array
        for (i = endOfNonZero; i < arrSize; i++)
	{
		arr[i] = 0;
	}
}

int main(int argc, char** argv)
{

	cout << "main - start" << endl;
	struct node* head = createList();
	cout << "main - original list is:" << endl;
	displayList(head);
	struct node* n3 = head->next->next;
	cout << "main - n3 points to:" << n3->val << endl;
	struct node* n5 = head->next->next->next->next;
	cout << "main - n5 points to:" << n5->val << endl;
	bool res = findLoopInLinkedList(head);
	if (true == res)
	{
		cout << "main - there is a loop in the original list" << endl;
	}
	else
	{	
		cout << "main - there is NO loop in the original list" << endl;
	}

	n5->next = n3;	
	cout << "main - now n5->next points to:" << n5->next->val << endl;
	res = findLoopInLinkedList(head);
	if (true == res)
	{
		cout << "main - there is a loop in the modified list" << endl;
	}
	else
	{	
		cout << "main - there is NO loop in the modified list" << endl;
	}	


	// 2)
	int arr [] = {1, 2, 0, 3, 0, 4, 5, 6};
	size_t arrSize = sizeof(arr) / sizeof(arr[0]);
	reorderArrayWithZeros(arr, arrSize);
	cout << "main - after re-ordering the array is:" << endl;
	for (size_t i = 0; i < arrSize; ++i)
	{
		cout << arr[i] << "|";
	}

	cout << "main - end" << endl;
	return 0;
}
