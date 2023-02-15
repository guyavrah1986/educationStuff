#include <thread>
#include <mutex>
#include <condition_variable>

using namespace std;

class FooBar 
{
private:
    int n;
    mutex m;
    condition_variable cv;
    bool ready;
    bool processed; 
public:
    FooBar(int n)
    {
        this->n = n;
        ready = false;
        processed = false;
    }

    void foo(function<void()> printFoo)
    {
        cout << "foo - start" << endl;
        for (int i = 0; i < n; i++)
        {
            // send data to the worker thread
            {
                lock_guard lk(m);
                // printFoo() outputs "foo". Do not change or remove this line.
                printFoo();
                ready = true;
                cout << "foo function thread() signals it is done printing" << endl;
            }
            cv.notify_one();
            cout << "foo function AFTER calling cv.notify_one()" << endl;
            // wait for the worker2 to finish
            {
                unique_lock lk(m);
                cv.wait(lk, [this]{return processed;});
            }
        }
        cout << "foo - end" << endl;
    }

    void bar(function<void()> printBar)
    {    
        cout << "bar - start" << endl;
        for (int i = 0; i < n; i++)
        {
            // Wait until foo function thread is done printing
            std::unique_lock lk(m);
            cv.wait(lk, [this]{return ready;});
 
            // after the wait, we own the lock.
            std::cout << "bar function has the lock" << std::endl;
 
            // Send data back to foo thread()
            // printBar() outputs "bar". Do not change or remove this line.
        	printBar();
            processed = true;
            std::cout << "bar function thread signals it printed bar" << std::endl;
 
            // Manual unlocking is done before notifying, to avoid waking up
            // the waiting thread only to block again (see notify_one for details)
            lk.unlock();
            cv.notify_one();
        }
        cout << "bar - end" << endl;
    }
};
