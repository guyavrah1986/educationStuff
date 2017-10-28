// ===================================================================================================================================================================
// ===================================================================================================================================================================
// 
// 1) 

// ===================================================================================================================================================================
// ===================================================================================================================================================================
#include <memory>
#include <iostream>
#include <string>
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <functional>

typedef void (*callBackPtr)(void);
pthread_t* globalSecThread;
void calledFromLambdaFunc(int arg, callBackPtr callback);
void* dummy(void* arg);



class MyObj : public std::enable_shared_from_this<MyObj> 
{

public:
	MyObj(int a) : m_a(a)
	{
		std::cout << "MyObj::MyObj - setting m_a to:" << m_a << std::endl;
	}

	~MyObj() 
	{
		std::cout << "MyObj::~MyObj - killing this:" << this << " with m_a:" << m_a << std::endl;
	}

	void invokeAsyncFunc()
	{
		std::cout << "MyObj::invokeAsyncFunc - is run by thread ID:" << pthread_self() << std::endl;
		
		// define some local variables on the function stack
		std::string str("stack_string");
		int localInt = 17;
		
		// here we need to make sure "this" object will exists when the function
		// will get back here !!
		//pthread_t secTid;
		auto self(shared_from_this());
		calledFromLambdaFunc(localInt, [self]()
		{
			std::cout << "MyObj::invokeAsyncFunc - within the lambda body - this->m_a is:" << std::endl; // this->m_a

		});
		std::cout << "MyObj::invokeAsyncFunc - after the lambda body, return to main" << std::endl;
		return;
	}

	int m_a;
};

// dummy function to "sleep" for couple of seconds
void* dummy(void* arg)
{
	std::cout << "dummy - start" << std::endl;
	unsigned int num = 3;
	callBackPtr callback = (callBackPtr)(arg);
	std::cout << "\n \n dummy is being run by thread ID:" << pthread_self() << " about to sleep for:" << num << " seconds" << std::endl;
	sleep(num);
	std::cout << "\n \n dummy is DONE sleeping invoking the callback" << std::endl;
	callback();
}


void calledFromLambdaFunc(int arg, callBackPtr callback) //
{
	std::cout << "calledFromLambdaFunc - start" << std::endl;
	// here we call an async function USING ANOTEHR (new) 
	// thread - in order to simulate a situation where we return from it
	// and the calling (invoking) object should have been "long gone"
        int err = pthread_create(globalSecThread, nullptr, &dummy, &callback);
        if (err != 0)
	{
		std::cout << "calledFromLambdaFunc - was unable to create a new thread, terminating..." << std::endl;
		exit(1);
	}
	else
	{
		/*
		if(pthread_join(*pThreadId, nullptr)) 
		{
			std::cout << "calledFromLambdaFunc - was unable to wait for the other thread to terminate its dummy function, aborting..." << std::endl;
			callback(nullptr);
		}
		*/
		std::cout << "calledFromLambdaFunc - created new thread successfully, terminating" << std::endl;
		//callback(pThreadId);
	}
}



// ===================================================================================================================================================================
// ===================================================================================================================================================================
// main
// ===================================================================================================================================================================
// ===================================================================================================================================================================


int main(int argc, char** argv)
{

	std::cout << "main - start" << std::endl;
	std::cout << "main is being run by thread ID:" << pthread_self() << std::endl;
	globalSecThread = new pthread_t;
	MyObj obj(12);

	// call the "main" function via the "main" thread
	obj.invokeAsyncFunc();

	// wait for the new thread to finish
	
	if(pthread_join(*globalSecThread, nullptr)) 
	{
		std::cout << "main - was unable to wait for the other thread:" << *globalSecThread << std::endl;
		return 2;
	}
	

	// yet sleep long enough for it to terminate so that the callback
	// function will be called on an object that is no longer valid !!
	unsigned int numToSleepMain = 5;	
	sleep(numToSleepMain);
	std::cout << "\n \n main - end" << std::endl;
	return 0;
}
