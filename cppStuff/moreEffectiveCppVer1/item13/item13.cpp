// ========================================================================================================================================================================
/*
* Item 13:
* --------
* Preface: Generally speaking, throwing an exception is NO DIFFERNET from "ordinary" passing an argument to a function - so all the 
* different cases that might occur when dealing when throwing (passing an exception object) to its "reciver" (the catch block), has the 
* same considerations of passing a "normal" object to a fuction.
*
* 1) By pointert:
*    The first option leaves us with the "question" - Who should clean-up after the pointer (pointing to an exception) object ?
*    Offcourse if it is not an exception allocated on the heap - than it is even worse - cause we are catching a pointer to an object
*    that is no longer valid now...
*
* 2) By value:
*    Other than the ovious overhead of creating and copying the exception object, we are also get risky in situations such as 
*    "object slicing" (in this case we wont call our exception what method, but the one that std::exception has).
* 
* !! @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ !!
* !! @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ !!
* Key note: Always catch exceptions by reference !!
* !! @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ !!
* !! @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ !!
*/
// ======================================================================================================================================================================

#define _CRTDBG_MAP_ALLOC  // NOTE: the order of the includes that FOLLOWS this define is important !!!
#include <stdlib.h>  
#include <crtdbg.h> 

#include <iostream>
#include <string>

using namespace std;

class MyException : public exception
{
public:
	MyException(const string& msg)
		: m_msg(msg)
	{
		cout << "MyException::MyException - set m_msg to:" << m_msg << endl;
	}

	~MyException()
	{
		cout << "MyException::~MyException" << endl;
	}

	virtual const char* what() throw()
	{
		cout << "MyException - what" << endl;
		return m_msg.c_str();
	}

	const string m_msg;
};

void throwExceptionBypointer()
{
	MyException* e = new MyException("exception created on the heap");
	throw e;
}

void catchingExeceptionByPointerExample()
{
	cout << "catchingExeceptionByPointerExample - start" << endl;
	try
	{
		cout << "catchingExeceptionByPointerExample - within try block" << endl;
		throwExceptionBypointer();
	}
	catch (MyException* pe)
	{
		cerr << "catchingExeceptionByPointerExample - within catch block, caught an exception by pointer:" << pe->what() << endl;
		// 1) Should we delete it or not ?? 
		delete pe;
	}

	cout << "\n \n catchingExeceptionByPointerExample - end" << endl;
}

void throwExceptionByValue()
{
	MyException e("exception created on the stack and is being thrown by value");
	throw e;
}

void catchingExeceptionByValueExample()
{
	cout << "catchingExeceptionByValueExample - start" << endl;
	try
	{
		cout << "catchingExeceptionByValueExample - within try block" << endl;
		throwExceptionByValue();
	}
	catch (exception e)
	{
		cerr << "catchingExeceptionByPointerExample - within catch block, caught an exception by value:" << e.what() << endl;
	}

	cout << "\n \n catchingExeceptionByValueExample - end" << endl;
}

void item13Usage()
{
	cout << "item13Usage - start" << endl;

	catchingExeceptionByPointerExample();
	catchingExeceptionByValueExample();

	cout << "\n \n item13Usage - end" << endl;
}

int main(int argc, char** argv)
{
	cout << "main - start" << endl;

	item13Usage();

	char c = 0;
	cout << "main - enter any key to terminate (and press enter)" << endl;
	cin >> c;
	cout << "\n \n main - end" << endl;
	_CrtDumpMemoryLeaks();
	return 0;
}
