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
int numOfIterations = 2;
 
void worker_thread2()
{
	cout << "worker_thread2 - start" << endl;
	for (int i = 0; i < numOfIterations; ++i)
	{
		cout << "worker_thread2 - iteration:" << i << endl;
		// Wait until main() sends data
		cout << "worker_thread2 BEFORE unique_lock lk(m)" << endl;
		unique_lock lk(m);
		cout << "worker_thread2 AFTER unique_lock lk(m)" << endl;
		cv.wait(lk, []{return ready;});
	 	cout << "worker_thread2 AFTER cv.wait" << endl;
		// after the wait, we own the lock.
		cout << "bar" << endl;
	 
		// Send data back to main()
		processed = true;

	 
		// Manual unlocking is done before notifying, to avoid waking up
		// the waiting thread only to block again (see notify_one for details)
		cout << "worker_thread2 BEFORE lk.unlock" << endl;
		lk.unlock();
		cout << "worker_thread2 AFTER lk.unlock" << endl;

		cv.notify_one();
		cout << "worker_thread2 AFTER cv.notify" << endl;
		//ready = false;
	}
	cout << "worker_thread2 - end" << endl;
}

void worker_thread1()
{
	cout << "worker_thread1 - start" << endl;
	for (int i = 0; i < numOfIterations; ++i)
	{
		cout << "worker_thread1 - iteration:" << i << endl;
		// send data to the worker thread
		{
			lock_guard lk(m);
			cout << "worker_thread1 AFTER lock_guard lk(m)" << endl;
			cout << "foo" << endl;
			ready = true;
			cout << "worker_thread1 signals data ready for processing\n";
		}
		cv.notify_one();
		cout << "worker_thread1 AFTER  cv.notify_one()" << endl;
		// wait for the worker2 to finish
		{
			cout << "worker_thread1 BEFORE unique_lock lk(m)" << endl;
			unique_lock lk(m);
			//lock_guard lk(m);
	 		cout << "worker_thread1 AFTER calling unique_lock lk(m)" << endl;
			cv.wait(lk, []{return processed;});
	 		cout << "worker_thread1 AFTER cv.wait" << endl;
			//ready = false;
		}
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
