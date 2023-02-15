#include <iostream>
#include <string>
#include <thread>
#include <mutex>
#include <condition_variable>

using namespace std;

mutex m;
condition_variable cv;
string threadsData;
bool ready = false;
bool processed = false;
 
void worker_thread2()
{
	cout << "worker_thread2 - start" << endl;
	// Wait until main() sends data
	unique_lock lk(m);
	cv.wait(lk, []{return ready;});
 
	// after the wait, we own the lock.
	cout << "worker_thread2 is processing data\n";
	threadsData += " after processing";
 
	// Send data back to main()
	processed = true;
	cout << "worker_thread2 signals data processing completed\n";
 
	// Manual unlocking is done before notifying, to avoid waking up
	// the waiting thread only to block again (see notify_one for details)
	lk.unlock();
	cv.notify_one();
	cout << "worker_thread2 - end" << endl;
}

void worker_thread1()
{
	cout << "worker_thread1 - start" << endl;

	// send data to the worker thread
	{
		lock_guard lk(m);
		threadsData = "Example data";
		ready = true;
		cout << "worker_thread1 signals data ready for processing\n";
	}
	cv.notify_one();
 	cout << "worker_thread1 AFTER calling cv.notify_one()" << endl;
	// wait for the worker2 to finish
	{
		unique_lock lk(m);
		cv.wait(lk, []{return processed;});
	}
	cout << "worker_thread1 - end" << endl;
}
 
int main()
{
	cout << "main - about to start the two worker threads" << endl;
	thread worker1(worker_thread1);
	thread worker2(worker_thread2);

 
	cout << "main - joining the two worker threads" << endl;
	worker1.join();
	worker2.join();
	cout << "main - end" << endl;
	return 0;
}
