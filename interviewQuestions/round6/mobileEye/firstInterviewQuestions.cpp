// ============================================================================
// The send_non_blocking_send function, as the name suggests is a non blocking
// function that sends len bytes of the buffer pointed by buff.
//
// Using it, implement the blocking_send function that returns only after the
// bytes pointed by buff were sent.
//
//
// ============================================================================
#include <iostream>
#include <unistd.h> // for sleep()
#include <thread>
#include <mutex>
#include <condition_variable>

using namespace std;

void (callBackFunc)(void* ctx);

void myCallBackFunc(void* ctx)
{
	if (nullptr == ctx)
	{
		cout << "myCallBackFunc - context is NULL, aborting" << endl;
		return;
	}
	
	condition_variable* condVar = static_cast<condition_variable*>(ctx);
	unsigned int num = 2; //*(static_cast<unsigned int*>(ctx));
        cout << "myCallBackFunc - about to sleep for:" << num << " seconds" << endl;
	sleep(num);
	cout << "myCallBackFunc - DONE sleeping for:" << num << " seconds" << endl;
	condVar->notify_one();
	cout << "myCallBackFunc - end" << endl;
}

void send_non_blocking(void* buff, size_t len, void* ctx)
{
	cout << "send_non_blocking - start" << endl;
	thread callBackFuncThread(myCallBackFunc, ctx);
	callBackFuncThread.detach();
	cout << "send_non_blocking - after detaching the call back function thread, terminating" << endl;
}


void blocking_send(void* buff, size_t len)
{
	if (nullptr == buff)
	{
		cout << "blocking_send - got NULL pointer, aborting" << endl;
		return;
	}


	{
		mutex blockingFuncMutex;
		condition_variable condVar;
		unique_lock<mutex> lock(blockingFuncMutex);
 
		// Wait for the non blocking function to return - it will signal
		// it by "raising" the cond_var
		cout << "blocking_send - calling the send_non_blocking" << endl;
		send_non_blocking(buff, len, static_cast<void*>(&condVar));
		cout << "blocking_send - about to wait on the condition variable" << endl;
		condVar.wait(lock);
                cout << "blocking_send - DONE waiting on the condition variable" << endl;
	}

	cout << "blocking_send - got buff of size:" << len << endl;
}


int main(int argc, char** argv)
{
	cout << "main - start" << endl;
	char buff [] = {'a', 'b', 'c'};
	size_t len = sizeof(buff);
	blocking_send(static_cast<void*>(buff), len);
	cout << "main - end" << endl;
	return 0;
}
