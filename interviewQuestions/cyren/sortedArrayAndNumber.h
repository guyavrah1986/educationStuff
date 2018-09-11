// ===============================================================================================================================
/*
* Given a sorted array and a number - find two numbers that their sum eaquls to the given number.
*/
// ===============================================================================================================================

const unsigned int len = 9;

#include <iostream>
#include <unordered_map>

using namespace std;

int arr [] = {1,3,5,6,7,9,12,45,67};
int target = 16;

void sortedArrAndNumberQuestion()
{
	unordered_map<int, int> map;
	for (unsigned int i = 0; i < len; ++i)
	{
		map[arr[i]] = i;
	}

	for (unsigned int i = 0; i < len; ++i)
	{
		auto search = map.find(target - arr[i]); 
			
		if(search != map.end() && search->first != i)
		{
			cout << search->first << " + " << target - search->first << " = " << target << endl;
		}	
	}	
}
