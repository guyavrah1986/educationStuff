// ================================================================================================
// ================================================================================================
// 1. Implement a queue (I chose to do it in C++):
// Implementation notes:
// a) When initializing the queue, the maximum size of the queue is allocated. If the code was
//    unable to allocate all the requiered space, FALSE is returned.
// b) The queue clss is set to be a template class, so that its "container" (array) will be able
//    to holds items of any type. This, however, enforces the following:
//  - The T class MUST have default ctor implemented.
//  - 

// ================================================================================================
// ================================================================================================
#include <iostream>

using namespace std; // DO NOT do it in production

class MySampleClass
{
public:
    MySampleClass(int x, int y)
        : m_x(x)
        , m_y(y)
    {
        cout << "MySampleClass::MySampleClass - setting m_x to:" << m_x << " and m_y to:" << m_y << endl;
    }

    MySampleClass()
        : MySampleClass(0, 0)
    {
        cout << "MySampleClass::MySampleClass()" << endl;
    }

    MySampleClass(const MySampleClass& other)
        : MySampleClass(other.m_x, other.m_y)
    {
        cout << "MySampleClass::MySampleClass(copy)" << endl;
    }

    MySampleClass& operator=(const MySampleClass& rhs)
    {
        cout << "MySampleClass::MySampleClass(operator=)" << endl;
        if (&rhs == this)
        {
            return *this;
        }

        cout << "MySampleClass::MySampleClass(operator=) - actually copying" << endl;
        this->m_x = rhs.m_x;
        this->m_y = rhs.m_y;
        return *this;
    }

    ~MySampleClass()
    {
        cout << "MySampleClass::~MySampleClass" << endl;
    }

    int m_x;
    int m_y;
};

template <typename T>
class MyQueue
{
public:
    explicit MyQueue(const size_t queueSize)
        : m_maxSize(queueSize)
        , m_currSize(0)
        , m_queueArr(nullptr)
    {
        cout << "MyQueue::MyQueue - created queue with MAX size of:" << m_maxSize << endl;
    }

    ~MyQueue()
    {
        if (nullptr != m_queueArr)
        {
            delete [] m_queueArr;
            cout << "MyQueue::~MyQueue - deleted the array's queue" << endl;
        }

        cout << "MyQueue::~MyQueue - end" << endl;
    }

    // Disable copy semantics & move semantics
    MyQueue(const MyQueue& other) = delete;
    MyQueue& operator=(const MyQueue& rhs) = delete;
    MyQueue(const MyQueue&& other) = delete;
    MyQueue& operator=(const MyQueue&& rhs) = delete;

    // Public API:
    // ==========
    bool InitQueue()
    {
        const string funcName = "MySampleClass::InitQueue - ";
        cout << funcName + "about to allocate:" << m_maxSize << " elements in the array" << endl;
        m_queueArr = new(nothrow) T[m_maxSize];
        if (m_queueArr == nullptr)
        {
            cout << funcName + "Memory allocation failed" << endl;
            return false;
        }
    
        cout << funcName + "end" << endl;
        return true;
    }

    bool InsertToQueue(T val)
    {
        const string funcName = "MySampleClass:InsertToQueue - ";
        cout << funcName + "about to try and add item to the queue" << endl;
        if (nullptr == m_queueArr)
        {
            cout << funcName + "the queue array is NULL, aborting" << endl;
            return false;
        }

        // TODO: guard with mutex
        if (m_currSize == m_maxSize)
        {
            cout << funcName + "the queue is full, aborting" << endl;
            return false;
        }

        m_queueArr[m_currSize + 1] = val;
        ++m_currSize;
        // TODO: guard with mutex --> end
        return true;
    }

    T PopFromQueue();

    // Getters & setters:
    size_t GetNumOfItemsInQueue() const
    {
        // TODO: guard with mutex
        return m_currSize;
    }

private:
    size_t m_maxSize;
    size_t m_currSize;
    T* m_queueArr;
};

