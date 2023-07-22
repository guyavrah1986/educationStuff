#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <functional>

using namespace std;

typedef void (*funcPointer)(void);

void printFoo()
{
	cout << "foo";
}

void printBar()
{
	cout << "bar";
}

class FooBar 
{
private:
    int n;
    mutex cond_var_mutex;
    condition_variable go_foo_cv;
    condition_variable go_bar_cv;
    volatile bool go_foo = true;
    volatile bool go_bar = false;

public:
    FooBar(int n)
    {
        this->n = n;
    }

    void foo()  // function<void()> printFoo
    {
        cout << "foo - start" << endl;
        for (int i = 0; i < n; i++)
        {
            cout << "foo - iteration:" << i << ", before locking cond_var_mutex" << endl;
            unique_lock<mutex> lk(cond_var_mutex);
            cout << "foo - iteration:" << i << ", AFTER locking cond_var_mutex" << endl;
            go_foo_cv.wait(lk, [&]{return go_foo;});
            cout << "foo - iteration:" << i << ", AFTER waiting for goo_foo to be true" << endl;
            // printFoo() outputs "foo". Do not change or remove this line.
            printFoo();

            go_foo = false;
            go_bar = true;
            lk.unlock();
            cout << "foo - iteration:" << i << ", AFTER unlocking cond_var_mutex" << endl;
            go_bar_cv.notify_all();
            cout << "foo - iteration:" << i << ", AFTER goo_bar_cv notify_all" << endl;
        }
        cout << "foo - end" << endl;
    }

    void bar() // function<void()> printBar
    {    
        cout << "bar - start" << endl;
        for (int i = 0; i < n; i++)
        {
            cout << "bar - iteration:" << i << ", before locking cond_var_mutex" << endl;
            unique_lock<mutex> lk(cond_var_mutex);
            cout << "bar - iteration:" << i << ", AFTER locking cond_var_mutex" << endl;
            go_bar_cv.wait(lk, [&]{return go_bar;});
            cout << "bar - iteration:" << i << ", AFTER waiting for go_bar to be true" << endl;
            // printBar() outputs "bar". Do not change or remove this line.
            printBar();

            go_bar = false;
            go_foo = true;
            lk.unlock();
            cout << "bar - iteration:" << i << ", AFTER unlocking cond_var_mutex" << endl;
            go_foo_cv.notify_all();
            cout << "bar - iteration:" << i << ", AFTER go_foo_cv notify_all" << endl;
        }
        cout << "bar - end" << endl;
    }
};

int main(int argc, char** argv)
{
	cout << "main - start" << endl;
	FooBar fooBar(2);
	//function<void()> foo_function_pointer = printFoo;
	//function<void()> bar_function_pointer = printBar;
	funcPointer foo_print_func_pointer = printFoo;
	funcPointer bar_print_func_pointer = printBar;

    	//f_display(-9);
	thread barThread(fooBar.bar);
	thread fooThread(fooBar.foo);
	cout << "main - joining the two worker threads" << endl;
	barThread.join();
	fooThread.join();
	cout << "main - end" << endl;
}
