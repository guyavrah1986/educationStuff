#include <iostream>

using namespace std;

int returnNumberOfArrayPermutations(char arr [], size_t arrLen)
{
	string funcName = "returnNumberOfArrayPermutations - ";
	cout << funcName + "the original array is:" << endl;
	for (size_t i = 0; i < arrLen; ++i)
	{
		cout << "[" << arr[i] << "]";
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

	
	return 0;
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
