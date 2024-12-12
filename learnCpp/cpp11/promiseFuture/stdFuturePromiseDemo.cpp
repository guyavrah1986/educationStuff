#include <iostream>
#include <thread>
#include <future>
#include <chrono>

using namespace std;

// Function that produces a value
void produce(promise<int> promise)
{
    int64_t numSec = 2;
    cout << "thread:" << this_thread::get_id() << " produce - sleeping for:" << numSec << " seconds to simulate work..." << endl;
    this_thread::sleep_for(chrono::seconds(numSec)); // Simulate some work
    promise.set_value(42); // Set the result
    cout << "thread:" << this_thread::get_id() << " produce - after setting the promise value, terminating:" << numSec << " seconds to simulate work..." << endl;
}

// Function that consumes a value
void consume(future<int> future)
{
    cout << "thread:" << this_thread::get_id() << " consume - waiting for the value..." << endl;
    int value = future.get();
    cout << "thread:" << this_thread::get_id() << " consume - received value:" << value << endl;
}

int main(int argc, char** argv)
{
    cout << "thread:" << this_thread::get_id() << " main - start" << endl;
    promise<int> promise1;
    promise<int> promise2;

    // This is the accosiation between the promise and the future
    future<int> future = promise1.get_future();
    future = promise2.get_future();

    // Start producer and consumer threads
    thread producer(produce, move(promise1));
    thread consumer(consume, move(future));

    cout << "thread:" << this_thread::get_id() << " main - before joining two threads" << endl;

    // Join threads
    producer.join();
    consumer.join();
    cout << "thread:" << this_thread::get_id() << " main - end" << endl;
    return 0;
}