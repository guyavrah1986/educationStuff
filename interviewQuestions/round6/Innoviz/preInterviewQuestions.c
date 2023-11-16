#include <stdio.h>


// this function returns the number of seconds that passed since some 
// reference point in time
int calcTime()
{
    NumOfSecondsFromStartingPoint = 17;
    return NumOfSecondsFromStartingPoint;
}

// 1 Q) What this function does?
// 1 A) The objective of this function is to wait one hour
// 2 Q) This function runs in a context in which there are interruptes
//      
void myFunction()
{
    int time = calcTime();
    while (time - calcTime() != 3600);
}

int main()
{
    printf("Hello World");

    return 0;
}
