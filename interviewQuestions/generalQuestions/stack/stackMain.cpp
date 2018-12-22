// ===================================================================================================
// ===================================================================================================
// This file contains questions in the "area" of stack (data structure) from different interviewes 
//    that either:
// a) I have been to and was asked (and they are not part of the 150 job-hunt famous questions list.
// b) I have prepeared to before a praticular interview I went to (and not neccessarly was asked 
//    this question throughout the interview).
// c) Saw on some forum or site and wanted to document it.
//
// 1) Implement a stack
// 
// ===================================================================================================
// ===================================================================================================
#include <iostream>
#include <thread>

#include "myStack.h"

using namespace std;

// 1)
void question1()
{
	cout << "question1 - start" << endl;

	MyStack<int> myStack(10);
	bool res = myStack.Push(1);
	res = myStack.Push(2);
	res = myStack.Push(3);
	myStack.DisplayStack();
	int ret;
	res = myStack.Pop(&ret);
	cout << "question1 - after first poping element we got:" << ret << endl;
	myStack.DisplayStack();
	res = myStack.Pop(&ret);
	cout << "question1 - after second poping element we got:" << ret << endl;
	myStack.DisplayStack();
	res = myStack.Pop(&ret);
	cout << "question1 - after third poping element we got:" << ret << endl;
	myStack.DisplayStack();

	res = myStack.Pop(&ret);
	if (res == true)
	{
		cout << "question1 - after stack is EMPTY, trying to pop element we got:" << ret << endl;
	}
	else
	{
		cout << "question1 - after stack is EMPTY, there is no element availble to pop" << endl;
	}

	myStack.DisplayStack();

	cout << "question1 - end" << endl;
}

void pusherThreadFunc(MyStack<int>& myStack, size_t numOfPushes)
{
	cout << "pusherThreadFunc - start" << endl;
	size_t numOfSuccessfullPush = 0;
	bool res = false;	
	for (size_t i = 0; i < numOfPushes; )
	{
		res = myStack.Push(i);
		if (res == true)
		{
			++i;
		}
	}

	cout << "pusherThreadFunc - end" << endl;
}

void poperThreadFunc(MyStack<int>& myStack, size_t numOfPops)
{
	cout << "poperThreadFunc - start" << endl;
	size_t numOfSuccessfullPop = 0;
	bool res = false;	
	int ret;
	for (size_t i = 0; i < numOfPops; )
	{
		res = myStack.Pop(&ret);
		if (res == true)
		{
			cout << "poperThreadFunc - poped:" << ret << endl;
			++i;
		}
	}

	cout << "poperThreadFunc - end" << endl;
}

void testQuestion1MultiThreaded()
{
	cout << "testQuestion1MultiThreaded - start" << endl;

	MyStack<int> myStack(10);
	thread pusherThread(&pusherThreadFunc,ref(myStack), 17);
	thread poperThread(&poperThreadFunc,ref(myStack), 10);

	pusherThread.join();
	poperThread.join();
	
	cout << "testQuestion1MultiThreaded - end" << endl;
}

int main(int argc, char** argv)
{
	cout << "main - start \n" << endl;

	// 1)
	question1();
	testQuestion1MultiThreaded();

	cout << "\n \n main - end \n" << endl;
	return 0;
}
