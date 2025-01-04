#include <iostream>
#include <vector>

using namespace std;

typedef struct
{
    int x;
    int y;
    int z;
    double d;
}MyStruct;

MyStruct someFuncThatReturnsVal()
{
    return MyStruct {1, 2, 3, 4.5};
}

void usageInAutoKeyword()
{
    const string funcName = "usageInAutoKeyword - ";
    cout << funcName + "start" << endl;
    
    // OK, but not REALLY helpfull
    int x = 3;
    auto y = x; // y is an int and has the value 3
    
    vector<int> myVec {1, 2, 3};
    for (vector<int>::iterator it1 = myVec.begin(); it1 != myVec.end(); ++it1)
    {
        cout << funcName + "it1 points to:" << *it1 << endl;
    }
    
    // Good: increase readiabilty of the code while the actual
    // type of the STL container that is iterated is "less" 
    // important in this context
    for (auto it2 : myVec)
    {
        cout << funcName + "it2 points to:" << it2 << endl;
    }

    // Bad: Reduces readability - the return type from the function
    // is important to better understand the rest of the code
    auto ret = someFuncThatReturnsVal();
    // What to do now with ret...???
    
    cout << funcName + "end" << endl;
}

int main()
{
    cout << "main - start" << endl;
    usageInAutoKeyword();
    cout << "main - end" << endl;
    return 0;
}
