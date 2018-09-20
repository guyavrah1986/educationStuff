// ==================================================================================================================
// Question: 
// ---------
// 0) pre-interview:
// Implement a "waiting" mechanis which is similar to barrier.
// 
// Assumptions in the solution:
// ----------------------------
// a. Writing & Reading the value of the global variables is atomic.
//
// 
// 1) Two threads run function q1 untill completion. What will be the poissbile values of sum at the end ?
// Answer:
// - Max value (full synchronization) - 20. 
// - Min value: 2 
//
// 2) Implement an algorithm to decide whether or not the string from the entire ASCII alpha bet (256 options) is 
//    composed ONLY from characters within charSet.
//    Best solution: Hold (insert) all the characters from charSet into a map, and than for each character in buffer
//    to check whether this chracter is in the map or not.
//    Run time: Lookup - O(Log(k)) X O(n) = O(log(k) * n).
//
// 3) How does a mutes is implemented ?
//
// 4) What is the diffenret in processes on 32/64 bit systems ?
//
// 5) IP and ethernet header fileds.
// 
// 
// 
// ==================================================================================================================

#include <iostream>
#include <thread>

using namespace std;

size_t gFlag = 0;
const size_t gTotalNumOfThreads = 2;


int sum = 0;

void q1()
{
	for (size_t i = 0; i < 10; ++i)
	{
		sum++;
	}
}

void q2()
{

	const char* buff = "zskjhksdksdjnfkjsnf"; 	// lenght N (N is very big)
	const char* charSet = "ABCDEF";			// lenght K (K is small)	
}

void preInterviewQuestion()
{
	cout << "func - start, thread ID:" << this_thread::get_id() << endl;
	gFlag++;
	size_t count = 0;
	while (gFlag < gTotalNumOfThreads)
	{
		if (count % 100 == 0)
			cout << "func - waiting, thread ID:" << this_thread::get_id() << endl;
		++count;
	}

	cout << "func - after waiting, thread ID:" << this_thread::get_id() << endl;
}

int main(int argc, char** argv)
{	
	cout << "main - start, thread ID:" << this_thread::get_id() << endl;
	
	thread th1(func);
	thread th2(func);

	cout << "main - after creating two threads, thread ID:" << this_thread::get_id() << endl;
	th1.join();
	th2.join();
	cout << "main - after joining two threads, thread ID:" << this_thread::get_id() << endl;

	cout << "main - end" << endl;
	return 0;
}
