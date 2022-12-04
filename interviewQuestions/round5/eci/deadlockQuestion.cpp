// ===========================================================================================
// ===========================================================================================
// Compile the program (under Linux) with linking it to the pthread library:
// $ g++ deadlockQuestion.cpp -o prog -lpthread 
//
// This code generates two different types of deadlocks (upon user input).  
//
// ===========================================================================================
// ===========================================================================================

#include <iostream>
#include <thread>
#include <mutex>
#include <unistd.h>

using namespace std;

mutex g_lock1;
mutex g_lock2;

void thread1Func()
{
	cout << "thread1Func - start" << endl;
	cout << "thread1Func - about to lock mutex 1" << endl;
	g_lock1.lock();
	cout << "thread1Func - locked mutex 1" << endl;
	sleep(1);
	cout << "thread1Func - about to lock mutex 2" << endl;
	g_lock2.lock();
	cout << "thread1Func - locked mutex 2" << endl;


	// do some stuff...
	cout << "thread1Func - about to un-lock mutex 2" << endl;
	g_lock2.unlock();
	cout << "thread1Fnc - un-locked mutex 2" << endl;
	cout << "thread1Func - about to un-lock mutex 1" << endl;
	g_lock1.unlock();
	cout << "thread1Fnc - un-locked mutex 1" << endl;
	cout << "thread1Func - end" << endl;
} 

void thread2Func()
{
	cout << "thread2Func - start" << endl;

	cout << "thread2Func - about to lock mutex 2" << endl;
	g_lock2.lock();
	cout << "thread2Func - locked mutex 2" << endl;
	sleep(1);
	cout << "thread2Func - about to lock mutex 1" << endl;
	g_lock1.lock();
	cout << "thread2Func - locked mutex 1" << endl;


	// do some stuff...
	cout << "thread2Func - about to un-lock mutex 1" << endl;
	g_lock1.unlock();
	cout << "thread2Func - un-locked mutex 1" << endl;
	cout << "thread2Func - about to un-lock mutex 2" << endl;
	g_lock2.unlock();
	cout << "thread2Func - un-locked mutex 2" << endl;

	cout << "thread2Func - end" << endl;
}

// a)
void simualteAbbaDeadlock()
{
	cout << "simualteAbbaDeadlock - start" << endl;

	thread t1(thread1Func);
	thread t2(thread2Func);

	// join threads
	t1.join();
	t2.join();
	cout << "simualteAbbaDeadlock - joined threads" << endl;

	cout << "simualteAbbaDeadlock - end" << endl;
}

void threadFunc3()
{
	cout << "threadFunc3 - start" << endl;

	cout << "threadFunc3 - end" << endl;
}

// b)
void simualteSelfDeadlock()
{
	cout << "simualteSelfDeadlock - start" << endl;
		
	cout << "simualteSelfDeadlock - about lock for the first time lock1" << endl;
	g_lock1.lock();
	cout << "simualteSelfDeadlock - lock1 was locked" << endl;
	cout << "simualteSelfDeadlock - about to lock lock1 for the second time" << endl;
	g_lock1.lock();
	cout << "simualteSelfDeadlock - lock1 was locked" << endl;

	// technically, here we should have un-lock lock1, but this code will never be reached anyways...
	cout << "simualteSelfDeadlock - end" << endl;
}


// --------------------
// main
// --------------------

int main(int argc, char** argv)
{
	cout << "============" << endl;
	cout << "main - start" << endl;
	cout << "============" << endl;
	cout << "main - press 0 to exit, press 1 for ABBA deadlock, press 2 for self-deadlock" << endl;
	int num = 0;
	cin >> num;
	switch(num)
	{
		case 1: simualteAbbaDeadlock();
			break;
		case 2: simualteSelfDeadlock();
			break;
		default: cout << "main - terminating..." << endl;
			return 0;
	}

	char c;
	cout << "main - enter any key to terminate and hit ENTER" << endl;
	cin >> c;
	cout << "============" << endl;
	cout << "main - end" << endl;
	cout << "============" << endl;
	return 0;
}
