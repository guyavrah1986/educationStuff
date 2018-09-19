// ===================================================================================================================================================================
// ===================================================================================================================================================================
// 
// ---------------------------------
//

// 
//
//
// ===================================================================================================================================================================
// ===================================================================================================================================================================

#include <iostream>

#include "stdThreadRaiiWrapper.h"

using namespace std;

// ===================================================================================================================================================================
// =================================================================================================================================================================== 

bool isCalled = false;
bool isThrown = false;

void workerThreadWhileLoopThatThrowsException()
{
	cout << "workerThreadWhileLoopThatThrowsException" << endl;
	size_t numOfSecToWorkUntillExceptionIsThrown = 3;
	size_t numSecPassed = 0;
	isCalled = true;
	while (true)
	{
		cout << "workerThreadWhileLoopThatThrowsException - in iteration number:" << ++numSecPassed << endl;
		this_thread::sleep_for((chrono::seconds(1)));
		if (numSecPassed == numOfSecToWorkUntillExceptionIsThrown)
		{
			isThrown = true;
			throw ("worker thread stopped unexpectedly");
		}
	}

	// should never reach here
	cout << "workerThreadWhileLoopThatThrowsException - end" << endl;
}


int main(int argc, char** argv)
{
	cout << "main - start" << endl;
	StdThreadRaiiWrapper workerThread1(thread(workerThreadWhileLoopThatThrowsException), &thread::join);
	cout << "main - end" << endl;
	return 0;
}
