#include <iostream>
#include <vector>

using namespace std;

int main(int argc, char** argv)
{
	cout << "proc2 - Start" << endl;

	vector<void*> ptrArr;
	const size_t maxNumOfAllocations = 5;
	size_t allocations = 0;
	ptrArr.reserve(maxNumOfAllocations);
	size_t input = 1;
	
	while (input != 0 && allocations < maxNumOfAllocations)
	{
		cout << "proc2 - please enter your choise:" << endl;
		cout << "proc2- enter number of bytes to allocate on the heap OR enter 0 to terminate" << endl;
		cin >> input;
		
		if (input == 0)
		{
			cout << "proc2 - user entered 0, terminating..." << endl;
			break;
		}
		
		void* tmp = new char [input];
		ptrArr.emplace_back(tmp);
	}
	cout << "proc2 - End" << endl;
	return 0;
}

