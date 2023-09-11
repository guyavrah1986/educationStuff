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
