#include <iostream>
#include <map>

/*
mov a, 0  // this is the place holder for the final result
mov c, X

LABEL LOOP_1:
	dec c (X--)
	mov b, Y  // keep it for later
	jnz c LOOP_2
	goto END_BOTH_LOOPS
	
LABEL LOOP_2:
	inc a (a++)
	dec b (Y--)
	jnz b LOOP_2
	goto LOOP_1
	
LABLE END_BOTH_LOOPS:
	HLT (end of the program)
*/

void findTwoNumsInArrayThatEqualValue()
{
    const char funcName [] = "findTwoNumsInArrayThatEqualValue - ";
    int valToFind = 17;
    printf("%s about to find two array elements that thier sum equals to:%d\n", funcName, valToFind);
    
    // we will assume the array is sorted
    int arr [] = {0, 1, 3, 4, 5, 6 ,8 , 9, 18, 76, 99};
    size_t arrLen = sizeof(arr)/sizeof(int);
    
    // go over the original array and "map" every number in it in its "complementry" 
    // number to valToFind. For example, given arr[0] = 9, it will be "mapped" to the
    // value 17-9=8 
    // NOTE: In case any number in the original array is greater than the valToFind
    // we will NOT map it (casue its index will be a negative value) --> meaning, For
    // simplicity we assume all the numbers in the array are positive and smaller than 
    // the valToFind
    int* start = arr;
    int* end = &(arr[arrLen - 1]);
    printf("%s about to iterate over the array with start pointer at:%p with value of:%d, and end pointer at:%p, with value of:%d\n", funcName, start, *start, end, *end);    
    while (start < end)
    {
        printf("%s start points at:%d, end points at:%d\n", funcName, *start, *end);
        if (*start + *end == valToFind)
        {
            printf("%s found two numbers equls to:%d\n", funcName, valToFind);
            return;
        }
        else if (*start + *end > valToFind)
        {
            end--;
        }
        else
        {
            start++;
        }
    }
}

struct item
{
  int val;
  unsigned long long indicator;
};

/*
* Some notes:
* 1. It is important to note that the setAll method needs to be thread safe
* 2. It is important to make sure that the global indicator does not reach beyond its max value
* 3. It is important to note that the get and setAll will be synchronized
*/

#define ITEMS_ARR_SIZE 10
struct item arr [ITEMS_ARR_SIZE];

int commonValue = 0;
unsigned long long numOfSetAll = 0;

int getItemVal(unsigned int index)
{
    if (numOfSetAll > arr[index].indicator)
    {
        return commonValue;
    }
    else
    {
        return arr[index].val;
    }
}

void setItemVal(unsigned int index, int valToSet)
{
    arr[index].val = valToSet;
    arr[index].indicator = numOfSetAll;
}

void setAll(int commonVal)
{
    commonValue = commonVal;
    if (numOfSetAll++ == MAX_LONG_VAL)
    {
        numOfSetAll = 0;
        // go over all the array of items and "reset" thier indicator value - this is O(n)
    }
}

void getSetAndResetProblem()
{
    const char funcName [] = "getSetAndResetProblem - ";
    printf("%s start\n", funcName);
    for (unsigned char i = 0; i < ITEMS_ARR_SIZE; ++i)
    {
        printf("arr[%u].val is:%d, arr[%u].indicator:%lu\n", i, arr[i].val, i, arr[i].indicator);
    }
    
}


#define MAX_LEN_OF_LIST 10

struct node
{
    int val;
    struct node* next;
};

/*
* Use cases: 
* 1. Single element linked list
* 2. Two elements, no duplications
* 3. Two elements, duplicated
* 4. Three element, first and second duplicated
* 5. Three element, first and third duplicated
* 6. Three element, first and last duplicated
* 7. Three element, second and last duplicated

*/
void removeDuplicatesFromUnSortedLinkedList(struct node* head)
{
    const char funcName [] = "removeDuplicatesFromUnSortedLinkedList - ";
    printf("%s about to remove duplications from the list that starts at address:%p\n", funcName, head);
    unsigned char map [MAX_LEN_OF_LIST] = {0};
    
    // edge cases
    if (head == NULL || head->next == NULL)
    {
        printf("%s empty or single element list, terminating\n", funcName);
        return;
    }
    
    // first traverse over the list to "count" how many times each number appears
    struct node* prev = NULL;
    struct node* curr = head;
    while (curr != NULL)
    {
        // value was already encountered, remove the current appearence of it
        if (map[curr->val] != 0)
        {
            // a duplicate was reached, remove it
            // no need  to forward prev afterwards!
            prev->next = curr->next;
        }
        else
        {
            map[curr->val]++;
            prev = curr;
        }

        curr = curr->next;
    }
    
    // for debug: disaply the list of appearences:
    for(unsigned char i = 0; i < MAX_LEN_OF_LIST; ++i)
    {
        printf("map[%u]:%u\n", i, map[i]);
    }
    
    printf("\n");
}

void displayList(const struct node* p)
{
    const char funcName [] = "displayList - ";
    printf("%s about to display list that its head is at address:%p\n", funcName, p);
    while (p != NULL)
    {
        printf("%d-->", p->val);
        p = p->next;
    }
    
    printf("NULL\n");
}

void createListWithSomeDuplicates()
{
    const char funcName [] = "createListWithSomeDuplicates - ";
    printf("%s about tp create linked list\n", funcName);
    struct node n1 = {1, NULL};
    struct node n2 = {2, NULL};
    n1.next = &n2;
    
    struct node n3 = {1, NULL};
    n2.next = &n3;
    
    n3.next = NULL;
    
    
    struct node n4 = {2, NULL};
    n3.next = &n4;
    n4.next = NULL;
    /*
    struct node n5 = {2, NULL};
    n4.next = &n5;
    
    struct node n6 = {6, NULL};
    n5.next = &n6;
    
    struct node n7 = {3, NULL};
    n6.next = &n7;
    
    struct node n8 = {8, NULL};
    n7.next = &n8;
    */
    printf("%s done creating the linked list, which is now:\n", funcName);
    displayList(&n1);
    
    removeDuplicatesFromUnSortedLinkedList(&n1);
    
    printf("%s AFTER removing duplications from the linked list, it is now:\n", funcName);
    displayList(&n1);
}

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

// TODO: 
// 1. Find a circle in a list
// 2. Given a list, write a function to remove duplicates
 
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
