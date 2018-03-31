#include <iostream>
#include <vector>

using namespace std;

int main(int argc, char** argv)
{
	cout << "proc1 - Start" << endl;

	vector<char*> ptrArr;
	const size_t maxNumOfAllocations = 5;
	size_t allocations = 0;
	ptrArr.reserve(maxNumOfAllocations);
	int input = 0;
	
	while (input != -1 && allocations < maxNumOfAllocations)
	{
		cout << "proc1 - please enter your choise:" << endl;
		cout << "1) proc1 - enter number of bytes to allocate on the heap" << endl;
		cout << "2) proc1 - enter number of allocation you wish to touch (should be [0-" <<  maxNumOfAllocations - 1 << "]" << endl;
		cout << "3) proc1 - enter -1 to terminate" << endl;
		cin >> input;

		if (input == -1)
		{
			cout << "proc1 - user entered -1, terminating..." << endl;
			break;
		}
		else if (input >= 0 && input <=  maxNumOfAllocations - 1)
		{
			char* tmp = ptrArr[input];
			cout << "proc1 - touching allocation number:" << input << " at address:" << tmp << endl;
			*tmp = 'A';
		}
		else 
		{		
			char* tmp = new char [input];
			ptrArr.emplace_back(tmp);
			cout << "proc1 - allocated allocation number:" << allocations << endl;
			++allocations;
		}

	}
	cout << "proc1 - End" << endl;
	return 0;
}

