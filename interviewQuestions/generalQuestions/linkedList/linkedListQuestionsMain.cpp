// ===================================================================================================
// ===================================================================================================
// This file contains questions in the "area" of linked lists from different interviewes 
//    that either:
// a) I have been to and was asked (and they are not part of the 150 job-hunt famous questions list.
// b) I have prepeared to before a praticular interview I went to (and not neccessarly was asked 
//    this question throughout the interview).
// c) Saw on some forum or site and wanted to document it.
//
// 1) Given a uni-directional linked list find the element in the middle of the list.
// 
// ===================================================================================================
// ===================================================================================================
#include<iostream>

#include "linkedList.h"

using namespace std;

// 1)
void question1(struct node* head)
{
	cout << "question1 - start" << endl;
	if (head == NULL)
	{
		cout << "question1 - got an empty list" << endl;
		return;
	}

	if (head->next == NULL)
	{
		cout << "question1 - got a single element list" << endl;
		return;
	}

	if (head->next->next == NULL)
	{
		cout << "question1 - got a two elements list" << endl;
		return;
	}

	node* tmp1 = head;
	node* tmp2 = head;
	while (tmp2->next != NULL)
	{
		tmp1 = tmp1->next;
		tmp2 = tmp2->next;
		tmp2 = tmp2->next;
		// for debug		
		cout << "question1 - after forwarding, tmp1:" << tmp1->val << ", tmp2:" << tmp2->val << endl;
	}

	cout << "question1 - the node in the middle of the list is:" << tmp1->val << endl;
	cout << "question1 - end" << endl;
}

void testQuestion1()
{
	cout << "testQuestion1 - start" << endl;

	struct node* head = createList();
	displayList(head);
	clearListLinear(head);
	cout << "testQuestion1 - end" << endl;
}


struct ListNode
{
	int val;
	struct ListNode *next;
};

int removeNthFromEndRecursive(struct ListNode* head, int n)
{
    // stop condition:
    if (NULL == head->next)
    {
        //printf("head->next == NULL and head->val is:%d\n", head->val);
        return n - 1;
    }

    int ret = removeNthFromEndRecursive(head->next, n);
    //printf("ret is:%d and head->val is:%d\n", ret, head->val);

    if (0 == ret)
    {
        //printf("about to remove the n-th element from the end of the list when head points to:%d\n", head->val);
        head->next = head->next->next;
    }

    return ret - 1;
}

struct ListNode* removeNthFromEnd(struct ListNode* head, int n)
{
    // edge cases: 
    // single element in the list
    if (NULL == head->next)
    {
        return NULL;
    }

    // two elements in the list
    if (NULL == head->next->next)
    {
        if (1 == n)
        {
            head->next = NULL;
            return head;
        }

        return head->next;
    }

    int ret = removeNthFromEndRecursive(head, n);
    if (0 == ret)
    {
        head = head->next;
    }
    return head;
}

int main(int argc, char** argv)
{
	cout << "main - start \n" << endl;

	// 1)
	testQuestion1();


	cout << "\n \n main - end \n" << endl;
	return 0;
}
