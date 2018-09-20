// ==================================================================================================================
// Question: 
// ---------
// Implement a "waiting" mechanis which is similar to barrier.
// 
// Assumptions in the solution:
// ----------------------------
// a. Writing & Reading the value of the global variables is atomic.
// ==================================================================================================================

#include <iostream>
#include <thread>

using namespace std;

size_t gFlag = 0;
const size_t gTotalNumOfThreads = 2;

void func()
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
