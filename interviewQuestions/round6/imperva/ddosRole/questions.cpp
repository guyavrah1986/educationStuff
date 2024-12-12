// ============================================================================
// Questions before interview:
// ---------------------------
// 1. Find first duplicate in an array: Given an array of ppositive integers,
// find the first duplicate in it. If it doesn't exist, return -1.
// ============================================================================
#include <cassert>
#include <iostream>
#include <unordered_set>

using namespace std;

int findFirstDuplicate(int* arr, int size)
{
    const string funcName = "findFirstDuplicate - ";
    if (NULL == arr || size <= 1)
    {
        cout << funcName + "the array is NULL of empty or with size 1" << endl;
        return -1;
    }
    
    unordered_set<int> arrSet;
    for (int i = 0; i < size; ++i)
    {
        auto res = arrSet.insert(arr[i]);
        if (false == res.second)
        {
            cout << funcName + "number:" << arr[i] << " is already present in the set, so it is a duplicate" << endl;
            return arr[i];
        }
    }
    
    cout << funcName + "there were NO duplicates in the array" << endl;
    return -1;
}

int DuplicateAtEnd()
{
    int arr[] = {1, 2, 3, 4, 5, 5};
    int size = sizeof(arr) / sizeof(arr[0]);
    int result = findFirstDuplicate(arr, size);
    //EXPECT_EQ(result, 5);
    assert(result == 5);
    return 0;
}

/*
TEST(FindFirstDuplicateTest, NullArray)
{
    int* arr = nullptr;
    int size = 5;
    int result = findFirstDuplicate(arr, size);
    EXPECT_EQ(result, -1);
}

TEST(FindFirstDuplicateTest, EmptyArray)
{
    int arr[] = {};
    int size = sizeof(arr) / sizeof(arr[0]);
    int result = findFirstDuplicate(arr, size);
    EXPECT_EQ(result, -1);
}

TEST(FindFirstDuplicateTest, NoDuplicates)
{
    int arr[] = {1, 2, 3, 4, 5};
    int size = sizeof(arr) / sizeof(arr[0]);
    int result = findFirstDuplicate(arr, size);
    EXPECT_EQ(result, -1);
}

TEST(FindFirstDuplicateTest, DuplicateInMiddle)
{
    int arr[] = {1, 2, 3, 2, 5};
    int size = sizeof(arr) / sizeof(arr[0]);
    int result = findFirstDuplicate(arr, size);
    EXPECT_EQ(result, 2);
}

TEST(FindFirstDuplicateTest, DuplicateAtStart)
{
    int arr[] = {1, 1, 2, 3, 4, 5};
    int size = sizeof(arr) / sizeof(arr[0]);
    int result = findFirstDuplicate(arr, size);
    EXPECT_EQ(result, 1);
}
*/

int runUnitTests()
{
    int res = DuplicateAtEnd();
    assert(res == 0);
    return 0;
}

int main()
{
    int arr1[] = {1, 2, 3, 4, 5};
    int res = findFirstDuplicate(arr1, 5);
    cout << "main - for arr1 return code is:" << res << endl;
    int arr2[] = {1, 2, 3, 2, 5};
    res = findFirstDuplicate(arr2, 5);
    cout << "main - for arr2 return code is:" << res << endl;
    res = runUnitTests();
    cout << "main - result of running unit tests is:" << res << endl;
    return 0;
}
