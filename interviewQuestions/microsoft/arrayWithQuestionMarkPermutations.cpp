#include <iostream>
#include <math.h>       /* pow */

using namespace std;

int returnNumberOfArrayPermutations(char arr [], size_t arrLen)
{
	string funcName = "returnNumberOfArrayPermutations - ";
	cout << funcName + "the original array is of length:" << arrLen << ", with the following content:" << endl;
	size_t numOfQuestionMarks = 0;
	for (size_t i = 0; i < arrLen; ++i)
	{
		cout << "[" << arr[i] << "]";
		if (arr[i] == '?')
		{
			++numOfQuestionMarks;
		}
	}

	cout << endl;
	// NULL array
	if (arr == NULL)
	{
		cout << funcName + "invalid array" << endl;
		return -1;
	}

	// Empty array
	if (arrLen == 0)
	{
		cout << funcName + "empty array" << endl;
		return 0;
	}

	cout << funcName + "there are total of:" << numOfQuestionMarks << " ? in the original array" << endl;
	size_t numOfPermutations = pow(2, numOfQuestionMarks);
	cout << funcName + "there are:" << numOfPermutations << " different permutations set of sub arrays" << endl;
	return numOfPermutations;
}

int runSampleTestCases()
{
	string funcName = "runSampleTestCases - ";
	cout << funcName + "start" << endl;

	// test case 1: NULL array (invalid array)
	char* arr = NULL;
	size_t arrLen = 0;
	size_t testCase = 1;
	cout << funcName + "runnign test case " << testCase << endl;
	int res = returnNumberOfArrayPermutations(arr, arrLen);
	int expectedRes = -1;	
	if (res != expectedRes)
	{
		cout << funcName + "expected result as:" << expectedRes << ", but got:" << res << endl;
		return 1;
	}


	// test case 2: empty array
	char c = 0;
	arr = &c; // so it won't be NULL
	arrLen = 0;
	testCase = 2;
	cout << funcName + "runnign test case " << testCase << endl;
	res = returnNumberOfArrayPermutations(arr, arrLen);
	expectedRes = 0;	
	if (res != expectedRes)
	{
		cout << funcName + "expected result as:" << expectedRes << ", but got:" << res << endl;
		return 1;
	}

	// test case 3: array with single ?
	const size_t arr3Len = 3;
	char arr3 [arr3Len] = {'1', '0', '?'};
	size_t numOfQuestionMarks = 1;
	size_t numOfPermutations = pow(2, numOfQuestionMarks);
	testCase = 3;
	cout << funcName + "runnign test case " << testCase << endl;
	res = returnNumberOfArrayPermutations(arr3, arr3Len);
	expectedRes = 2;	
	if (res != expectedRes)
	{
		cout << funcName + "expected result as:" << expectedRes << ", but got:" << res << endl;
		return 1;
	}

	cout << funcName + "end" << endl;
	return 0;
}


int main(int argc, char** argv)
{
	string funcName = "main - ";
	cout << funcName + "start" << endl;

	int res = runSampleTestCases();
	if (res != 0)
	{
		cout << funcName + "not all test cases were successfull" << endl;
	}

	cout << funcName + "end" << endl;
	return 0;
}
