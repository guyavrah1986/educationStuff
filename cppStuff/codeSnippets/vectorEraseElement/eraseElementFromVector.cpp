// ====================================================================================================================================
// ====================================================================================================================================
// Remove (erase) an element from std::vector given it is found.
//
//
// ====================================================================================================================================
// ====================================================================================================================================

#include <iostream>
#include <vector>

#include "myMovedObj.h"

using namespace std;

int main(int argc, char** argv)
{
	cout << "main - start" << endl;	
	size_t vecSize = 5;	
	int valToRemove = 2;	
	vector<MyMovedObj> vec;
	vec.reserve(vecSize);
	for(size_t i = 0; i < vecSize; ++i)
	{
		vec.emplace_back(move(MyMovedObj(i + 1)));
	}

	cout << "main - BEFORE removing element with value:" << valToRemove << ", vec size is:" << vec.size() << endl;
	// remove the element with value valToRemove in case it is found in the vector
	for(auto it = vec.begin(); it != vec.end();)
	{
		if((*it).GetValue() == valToRemove)
		{
			it = vec.erase(it);
		}
		else
		{
			++it;
		}
	}

	cout << "\n \n main - AFTER removing element with value:" << valToRemove << ", vec size is:" << vec.size() << endl;
	cout << "main - end" << endl;
	return 0;
}
