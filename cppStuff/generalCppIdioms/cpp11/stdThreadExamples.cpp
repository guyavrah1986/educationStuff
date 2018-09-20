#include <iostream>
#include <thread>

using namespace std;

void workerThreadFuncArgsByVal(int x, string str)
{
	cout << "workerThreadFuncArgsByVal - thread ID is:" << this_thread::get_id() << endl;
	cout << "workerThreadFuncArgsByVal - x is:" << x << " str is:" << str << endl;
	str = "new_string";
	x = 10;
}

void workerThreadFuncArgsByConstRef(const int& x, const string& str)
{
	cout << "workerThreadFuncArgsByRef - thread ID is:" << this_thread::get_id() << endl;
	cout << "workerThreadFuncArgsByRef - got x is:" << x << " str is:" << str << endl;
	int& y = const_cast<int&>(x);
	y++;	
	string& strRef = const_cast<string&>(str);
	strRef = "new_str";
	cout << "workerThreadFuncArgsByRef - set x to:" << x << " str to:" << str << endl;
}

void workerThreadFuncArgsByRef(int& x, string& str)
{
	cout << "workerThreadFuncArgsByRef - thread ID is:" << this_thread::get_id() << endl;
	cout << "workerThreadFuncArgsByRef - got x is:" << x << " str is:" << str << endl;
	x = 10;
	str = "new_string";
	cout << "workerThreadFuncArgsByRef - set x to:" << x << " str to:" << str << endl;
}


int main(int argc, char** argv)
{
	cout << "main - start" << endl;

	string str = "main_str";	
	int x = 9;
	cout << "main - BEFORE calling workerThreadFuncArgsByVal" << endl;
	thread th1(workerThreadFuncArgsByVal,x, str);
	th1.join();
	cout << "main - AFTER calling workerThreadFuncArgsByVal, x is:" << x << " str is:" << str << endl;
	cout << "\n \n \n" << endl;

	cout << "main - BEFORE calling workerThreadFuncArgsByConstRef" << endl;
	thread th2(workerThreadFuncArgsByConstRef, x, str);
	th2.join();
	cout << "main - AFTER calling workerThreadFuncArgsByConstRef, x is:" << x << " str is:" << str << endl;
	cout << "\n \n \n" << endl;
	
	cout << "main - BEFORE calling workerThreadFuncArgsByRef" << endl;
	thread th3(workerThreadFuncArgsByRef, ref(x), ref(str));
	th3.join();
	cout << "main - AFTER calling workerThreadFuncArgsByRef, x is:" << x << " str is:" << str << endl;

	cout << "main - end" << endl;
	return 0;
}
