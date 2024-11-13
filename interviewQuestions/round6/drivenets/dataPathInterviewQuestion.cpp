#include <iostream>
#include <queue>

using namespace std;

void func1()
{
    cout << "func1" << endl;
}

void func2()
{
    cout << "func2" << endl;
}

typedef void (*FuncPointer)(void);

class Task
{
 public:
    Task(const FuncPointer taskFuncPointer, const size_t deltaMiliSec)
        : m_taskFuncPointer(taskFuncPointer), m_deltaMiliSec(deltaMiliSec)
    {
        cout << "Task::Task - set m_deltaMiliSec to:" << m_deltaMiliSec << endl;
    }
    
    ~Task()
    {
        m_taskFuncPointer = nullptr;
    }

    FuncPointer m_taskFuncPointer;
    size_t      m_deltaMiliSec; 
};

struct LessThanByTimeToSchedule
{
    bool operator()(const Task& lhs, const Task& rhs) const
    {
        return lhs.m_deltaMiliSec < rhs.m_deltaMiliSec;
    }
};
    

int main()
{
    cout <<"main - start" << endl;
    Task t1(func1, 1);
    Task t2(func2, 2);
    //priority_queue<Task> pq;
    priority_queue<Task, vector<Task>, LessThanByTimeToSchedule> pq;

    
    //pq.push(t2);
    //pq.push(t1);
    
    cout <<"main - end" << endl;
    return 0;
}
