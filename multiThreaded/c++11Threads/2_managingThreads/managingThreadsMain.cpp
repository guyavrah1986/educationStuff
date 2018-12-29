// =============================================================================================================================
// =============================================================================================================================
// Chpater 2 - managing threads:
// -----------------------------
// 1) This function illustrate one approach to pass arguyments to the function that the 
//    thread is about to perfrom.
//
// 2) To avoid situatinos where the "parent thread" will terminate in a non ordinary
//    fashion BEFORE the created thread was joined - we MUST call t1.join() on ALL
//    possible paths.
//    NOTE: A more "complete" solution to this problem can be solved by wrapping the 
//    std::thread within a RAII based class.
//
// 3a) Important note regarding passing arguments to functions is that even if the 
//    argument of the function is declared by reference (also const reference), a copy
//    of the object is being sent to the thread's function !!
//
// 3b) One way to solve this issue is to pass the argument to the thread's function 
//     with "casting" using std::ref(arg).
//
//
// =============================================================================================================================
// =============================================================================================================================
#include <iostream>
#include <thread>
#include <string>

#include "myMovedObj.h"

using namespace std;

void sayHello(int i, double d)
{
	cout << "sayHello - got i:" << i << " and d:" << d << endl;
}

void passingArgumentsToTheThreadFunction()	// 1)
{
	cout << "passingArgumentsToTheThreadFunction - start" << endl;
	int i = 17;
	double d = 15;
	thread t1(sayHello, i, d);
	t1.join();
	cout << "passingArgumentsToTheThreadFunction - end" << endl;
}

void callJoinInCatchClause()	// 2)
{
	cout << "callJoinInCatchClause - start" << endl;

	thread t1(sayHello, 13, 4.5);
	try
	{
		cout << "callJoinInCatchClause - within try clause" << endl;
	}
	catch (...)
	{
		cout << "callJoinInCatchClause - within catch clause" << endl;
		if (t1.joinable())
		{
			t1.join();
		}
	}

	t1.join();
	cout << "callJoinInCatchClause - end" << endl;
}

void funcWithConstStringRefAsArg(MyMovedObj& obj)
{
	cout << "funcWithConstStringRefAsArg - start, got obj at address:" << &obj << endl;
	obj.SetValue(15);
}

void passArgumentToTheThreadFunction2()	// 3a)
{
	cout << "passArgumentToTheThreadFunction2 - start" << endl;
	MyMovedObj obj(17);
	cout << "passArgumentToTheThreadFunction2 - before invoking thread obj is:" << endl;
	cout << obj << endl;
	thread t(funcWithConstStringRefAsArg, obj);
	t.join();
	cout << "passArgumentToTheThreadFunction2 - after invoking thread obj is:" << endl;
	cout << obj << endl;
	cout << "passArgumentToTheThreadFunction2 - end" << endl;
}

void passArgumentToTheThreadFunction3()	// 3a)
{
	cout << "passArgumentToTheThreadFunction3 - start" << endl;
	MyMovedObj obj(17);
	cout << "passArgumentToTheThreadFunction3 - before invoking thread obj is:" << endl;
	cout << obj << endl;
	thread t(funcWithConstStringRefAsArg, ref(obj));
	t.join();
	cout << "passArgumentToTheThreadFunction3 - after invoking thread obj is:" << endl;
	cout << obj << endl;
	cout << "passArgumentToTheThreadFunction3 - end" << endl;
}

void passUniquePtrToThread()
{
	cout << "passUniquePtrToThread - start" << endl;
	unique_ptr<MyMovedObj> upObj{ new MyMovedObj(10) };
}
// =============================================================================================================================
// -----------
// main
// -----------
// =============================================================================================================================

int main(int argc, char** argv)
{	
	cout << "main - start" << endl;
	
	passingArgumentsToTheThreadFunction();
	callJoinInCatchClause();
	passArgumentToTheThreadFunction2();
	passArgumentToTheThreadFunction3();

	cout << "main - end" << endl;
	return 0;
}
