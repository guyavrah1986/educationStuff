#include <iostream>
#include <map>
 
// Implementation assumptions:
// 1.In case there are three elements (or more) that their sum equals to 
//   val --> the first pair of numbers will be returned.
// 2. There are no two values that their sum is greater than MAX_INT.
// 3. There can be elements with values of 0.
// 4. There can be elements with negative values.
void findTwoNumsInArrThatSumsUpToVal(const int* arr, const size_t arrLen, const int val)
{
    const char funcName [] = "findTwoNumsInArrThatSumsUpToVal - ";
    printf("%s start\n", funcName);
    printf("%s got the array:\n", funcName);
    for (size_t i = 0; i < arrLen; ++i)
    {
        printf("%d\t", arr[i]);
    }
    
    printf("\n%s about to look for two elements in the array that sums up to:%d\n", funcName, val);
    std::map<int, int> map;
    for (size_t i = 0; i < arrLen; ++i)
    {
        int currKey = val - arr[i];
        printf("%s checking if:%d has a pair-element that sums it up to:%d\n", funcName, arr[i], val);
        if (map.count(arr[i]) == 1)
        {
            int sumUpVal = map.at(arr[i]);
            printf("%s the array element:%d has a sum-pair in the array which is:%d\n", funcName, arr[i], sumUpVal);
            return;
        }
        else
        {
            printf("%s added key,value:%d,%d to the map\n", funcName, currKey, arr[i]);
            map[currKey] = arr[i];
        }
    }

    printf("%s end\n", funcName);
}

void buildRandomArray(int* arr, const size_t arrLen, int maxVal)
{
    const char funcName [] = "buildRandomArray - ";
    printf("%s about to build random array with maximum value of:\n", funcName);
    // first set the array with values from 0-(maxVal -1)
    for (size_t i = 0; i < arrLen; ++i)
    {
        arr[i] = i;
    }
    
    printf("%s before randomizing the array it is:\n", funcName);
    for (size_t i = 0; i < arrLen; ++i)
    {
        printf("%d\t", arr[i]);
    }
    
    printf("\n");
    srand(time(NULL));   // Initialization, should only be called once.
    
    // now randomize the array
    for (size_t i = 0; i < arrLen - 1; ++i)
    {
        int randomNumber = rand() % maxVal;;      // Returns a pseudo-random integer between 0 and maxVal-1
        printf("%s on iteration:%lu, the random number is:%d from the rang:0-%d\n", funcName, i, randomNumber, maxVal);
        // use the random number to take the current value from the respective index
        int tmp = arr[randomNumber];
        arr[randomNumber] = arr[maxVal - 1];
        arr[maxVal - 1] = tmp;
        
        // decrease the range by 1
        maxVal--;
    }

    printf("%s AFTER randomizing the array it is:\n", funcName);
    for (size_t i = 0; i < arrLen; ++i)
    {
        printf("%d\t", arr[i]);
    }
    
    printf("\n");
    printf("%s end\n", funcName);
}
 
int main()
{
  // Create a map of strings to integers

  int arr [] = {1, 4, 3, 61, -2, 0, 18};
  int val = 6;
  const size_t arrLen = sizeof(arr)/sizeof(int);
  findTwoNumsInArrThatSumsUpToVal(arr, arrLen, val);
 
  val = 7;
  findTwoNumsInArrThatSumsUpToVal(arr, arrLen, val);
  return 0;
}
