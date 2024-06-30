#include "potentialQuestions.h"

using namespace std;

int myQueueSample()
{
    const string funcName = "myQueueSample - ";
    cout << funcName + "start" << endl;
    const size_t numOfItemsInQueue = 3;
    MyQueue<MySampleClass> myQueue(numOfItemsInQueue);
    bool retVal = myQueue.InitQueue();
    if (false == retVal)
    {
        cout << funcName + "was unable to initialize the queue, aborting" << endl;
        return 1;
    }

    for (size_t i = 0; i < numOfItemsInQueue; ++i)
    {
        retVal = myQueue.InsertToQueue(MySampleClass(i, i));
        if (false == retVal)
        {
            cout << funcName + "was unable to add item to the queue, aborting" << endl;
            return 1;
        }
    }
    

    return 0;
}

int main(int argc, char** argv)
{
    cout << "main - start" << endl;
    int retVal = myQueueSample();
    if (0 != retVal)
    {
        cout << "main - the sample usage in the MyQueue failed" << endl;
    }
    
    cout << "main - end" << endl;
    return retVal;
}