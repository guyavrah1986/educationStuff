#include <iostream>
#include <memory>
#include <chrono>   // for 
#include <thread>   // for std::thread

using namespace std;

// ============================================================================================================
// ============================================================================================================
// std::shared_ptr related functions:
// ============================================================================================================
// ============================================================================================================
void threadFunc(shared_ptr<int> pi, size_t numMilliSecToSleep)
{
    const string funcName = "threadFunc - ";
    size_t tid = hash<thread::id>{}(this_thread::get_id());

    cout << funcName + "got numMilliSecToSleep:" << numMilliSecToSleep << endl;
    this_thread::sleep_for(chrono::milliseconds(numMilliSecToSleep));
    cout << funcName + "thread[" << tid << "], done sleeping, pi value is:" << *pi << endl;
}

void multiThreadingUseCase()
{
    const string funcName = "multiThreadingUseCase - ";
    cout << funcName + "start" << endl;
    shared_ptr<int> pi = make_shared<int>(17);
    thread t1(threadFunc, pi, 1000);
    thread t2(threadFunc, pi, 5000);

    cout << funcName + "the ref count of pi is:" << pi.use_count() << endl;
    t1.join();

    cout << funcName + "after t1 has done, trying to access pi here:" << *pi << endl;
    cout << funcName + "the ref count of pi is:" << pi.use_count() << endl;

    t2.join();
    cout << funcName + "after t2 has done, trying to access pi here:" << *pi << endl;
    cout << funcName + "the ref count of pi is:" << pi.use_count() << endl;
    cout << funcName + "start" << endl;
}

void sharedPtrUsageExamples()
{
    const string funcName = "sharedPtrUsageExamples - ";
    cout << funcName + "start" << endl;

    // 1) Introduce the multi threading use case
    multiThreadingUseCase();

    cout << funcName + "end" << endl;
}

// ============================================================================================================
// ============================================================================================================
// Raw pointers related functions:
// ============================================================================================================
// ============================================================================================================
void f1(int* p)
{
    const string funcName = "f1 - ";
    cout << funcName + "got an int pointed by raw pointer at address:" << p << " ,with value of:" << *p << endl;
    delete p;
}

void problemsDescriptionRawPointer()
{
    const string funcName = "problemsDescriptionRawPointer - ";
    cout << funcName + "start" << endl;
    
    // Issues with raw pointers:
    // ------------------------

    // 1) 
    // Done using the object pointed by p1, delete it
    // If you forget to delete it explictly, EVEN though p1 is
    // out of scope once this function is done, the object it is
    // pointing to, will NOT be deleted --> so if the below line
    // was not present - we would have a memory leak!
    int* p1 = new int(17);
    cout << funcName + "defined a RAW pointer on the stack of the function and set it to:" << *p1 << endl;
    delete p1;


    // 2)
    // When passing raw pointers between different "context" (in this case
    // two functions) and these are NOT synchronized between them about the 
    // lifetime of the passed object --> undefined behaviour mnight occur.
    int* p2 = new int(15);
    cout << funcName + "defined a RAW pointer on the stack that points to address:" << p2 << ", and set it to:" << *p2 << endl;
    f1(p2);
    cout << funcName + "after returning from function, now p2 points to:" << *p2 << endl;
    cout << funcName + "end" << endl;
}

int main(int argc, char** argv)
{
    cout << "main - start" << endl;

    // First, let us introduce the problems 
    // with raw pointers
    problemsDescriptionRawPointer();

    // Now, see how (in particualr use cases) the
    // std::shared_ptr tackels these problems
    sharedPtrUsageExamples();
    
    cout << "main - end" << endl;
    return 0;
}