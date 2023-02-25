// =================================================================================================================
// =================================================================================================================
// Questions before interview:
// ---------------------------
//
// 3. Implement stack with two queues and queue with two stacks
// 4. Implement polymorphism in C
// =================================================================================================================
// =================================================================================================================

#include <iostream>
#include <unordered_map>
#include <chrono>
#include <thread>

#include "evv_svc_base.h"

using namespace std;

struct Node
{
	int val;
	struct Node* next;
};

struct UrlNode
{
	double timeDelta;
	string url;
	struct UrlNode* next;
};

void displayList(const struct Node* node)
{
	while (NULL != node)
	{
		cout << node->val << "-->";
		node = node->next;
	}
	
	cout << "NULL" << endl;
}

struct Node* createList(const unsigned char numOfNodesInList)
{
	cout << "createList - about to create " << numOfNodesInList << " in the list" << endl;
	struct Node* listHead = new Node;
	struct Node* prev = listHead;
	listHead->val = 1;
	
	for (unsigned char i = 2; i < numOfNodesInList + 1; ++i)
	{
		cout << "createList - creating Node with val:" << +i << endl;
		struct Node* currNodeToAdd = new Node;
		currNodeToAdd->val = i;
		prev->next = currNodeToAdd;
		prev = currNodeToAdd;
	}
	
	return listHead;
}

void destroyList(struct Node* listHead)
{
	struct Node* next;
	while (NULL != listHead)
	{
		next = listHead->next;
		delete(listHead);
		listHead = next;
	}
}

// 1.
// This function needs to add a new node (newNode) AFTER the nodeToAddAfter assuming there are multiple
// readers and single writer.
// Assume assginment of a pointer is atomic.
// example:
// - current situation: 1-->2-->3-->4-->5-->6-->NULL
// - newNode is 7 and it needs to be added after 3, meaning eventually the list will be: 1-->2-->3-->7-->4-->5-->6-->sNULL
void addNode(struct Node* const newNode, struct Node* const nodeToAddAfter)
{
	cout << "addNode - about to add new node with val:" << newNode->val << " after node with val:" << nodeToAddAfter->val << endl;
	// first, newNode ALSO points on next of nodeToAddAfter - this is fine cause it does not affect any reader
	newNode->next = nodeToAddAfter->next;
	
	// now the list is the same, and 7-->4
	// second, make nodeToAddAfter point to newNode
	nodeToAddAfter->next = newNode;	
}

// 2.
void checkUrlAttack()
{
	string url1 = "url1";
	string url2 = "url2";
	string url3 = "url3";
	
	unordered_map<string, struct UrlNode*> urlMap;
  	
  	// first URL arrived, insert it as the list head
  	struct UrlNode* listHead = new UrlNode;
  	listHead->timeDelta = 0;
  	listHead->url = url1;
  	listHead->next = NULL;
  	
  	urlMap[url1] = listHead;
  	
  	// check if key is present
  	if (urlMap.find(url2) != urlMap.end())
  	{
  		cout << "map contains key:" << url2 << endl;
  	}
  	else
  	{
  		cout << "map does NOT contain key:" << url2 << endl;
  	}
  	// retrieve
	unordered_map<string, struct UrlNode*>::iterator i = urlMap.find(url1);
	cout << "Key: " << i->first << " Value: " << i->second << '\n';
	
	// sleep before inserting the 2nd URL
	/*s
	auto t_start = chrono::high_resolution_clock::now();
	this_thread::sleep_for(chrono::milliseconds(1000));

	// the work...
	auto t_end = chrono::high_resolution_clock::now();


	double elapsed_time_seconds = chrono::duration<double, chrono::seconds>(t_end-t_start).count();
	struct UrlNode* newNode = new UrlNode;
  	newNode->timeDelta = elapsed_time_seconds;
  	newNode->url = url2;
  	listHead->next = newNode;
  	urlMap[url2] = newNode;
  	
  	// sleep before inserting the 3rd URL
	t_start = chrono::high_resolution_clock::now();
	this_thread::sleep_for(chrono::milliseconds(1000));

	// the work...
	t_end = chrono::high_resolution_clock::now();

	elapsed_time_seconds = chrono::duration<double>(t_end-t_start).count();
	newNode = new UrlNode;
  	newNode->timeDelta = elapsed_time_seconds;
  	newNode->url = url3;
  	struct UrlNode* prev = urlMap[url2];
  	prev->next = newNode;
  	urlMap[url3] = newNode;
	*/
}

int main(int argc, char** argv)
{
	cout << "main - start" << endl;
	struct Node* listHead = createList(6);
	displayList(listHead);
	cout << "main - callign the addNode function" << endl;
	struct Node* newNode = new Node{7, NULL};
	struct Node* nodeToAddAfter = listHead->next->next;
	addNode(newNode, nodeToAddAfter);
	displayList(listHead);
	destroyList(listHead);
	
	// 2.
	checkUrlAttack();
	cout << "main - end" << endl;
	return 0;
}
