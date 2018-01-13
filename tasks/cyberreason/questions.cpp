// =======================================================================================================================================
/*
*   Cyberreason questions:
* ------------------------
* 1) You are given a two dimensional array with Nx2 rows. Each row holds the start and end point of a line (along the X axis).
*    Find the largest number of lines that are "intersect".
*
*/
// =======================================================================================================================================

#include <iostream>
#include <algorithm>

#define NUM_OF_ROWS 8

using namespace std;

uint8_t g_arr[NUM_OF_ROWS][2] = {{0, 2}, {1, 7}, {8, 9}, {6, 10}, {8, 11}, {3, 7}, {4, 6}, {0, 5}};

size_t naiveSolution(const uint8_t arr[NUM_OF_ROWS][2])
{
	cout << "naiveSolution - start" << endl;
	size_t numOfSectionsPerElement [NUM_OF_ROWS] = {0};
	
	for (size_t i = 0; i < NUM_OF_ROWS; ++i)
	{
		uint8_t currStart = arr[i][0];
		uint8_t currEnd = arr[i][1];
		for (size_t j = 0; j < NUM_OF_ROWS; ++j)
		{
			if (j == i)
			{
				continue;
			}

			if ((currEnd < arr[j][0]) || (currStart > arr[j][1]))
			{
				cout << "section " << i << " DOES NOT intersect with section " << j << endl;
			}

			else
			{
				cout << "section " << i << " intersect with section " << j << endl;
				numOfSectionsPerElement[i]++;
			}
		}
	}
	cout << "naiveSolution - displaying numOfSectionsPerElement array \n \n" << endl;
	for (size_t i = 0; i < NUM_OF_ROWS; ++i)
	{
		cout << "section " << i << " {" << static_cast<unsigned int>(arr[i][0]) << "," << static_cast<unsigned int>(arr[i][1]) << "}: 	has " << numOfSectionsPerElement[i] << " sections within it" << endl;
	}
	
	cout << "naiveSolution - end" << endl;
}


void betterSolution(const uint8_t arr[NUM_OF_ROWS][2])
{
	uint8_t startTimeArr [NUM_OF_ROWS];
	uint8_t endTimeArr [NUM_OF_ROWS];

	for (size_t i = 0; i < NUM_OF_ROWS; ++i)
	{
		startTimeArr[i] = arr[i][0];
		endTimeArr[i] = arr[i][1];
	}

	// sort the arrays
	sort(startTimeArr, startTimeArr + NUM_OF_ROWS);
	sort(endTimeArr, endTimeArr + NUM_OF_ROWS);

	// for debug
	cout << "betterSolution - startTimeArr after sorting is:" << endl;
	for (size_t i = 0; i < NUM_OF_ROWS; ++i)
	{
		cout << static_cast<unsigned int>(startTimeArr[i]) << " ";
	}

	cout << "\n \n betterSolution - endTimeArr after sorting is:" << endl;
	for (size_t i = 0; i < NUM_OF_ROWS; ++i)
	{
		cout << static_cast<unsigned int>(endTimeArr[i]) << " ";
	}

	size_t max = 0;
	size_t currMax = 0;
	for (size_t i = 0; i < NUM_OF_ROWS; ++i)
	{
		max++;
		// find first end time of a task that was finsihed after current task started
		
	}
}

int main(int argc, char** argv)
{
	cout << "main - start \n \n " << endl;

	//naiveSolution(g_arr);
	betterSolution(g_arr);
	cout << "\n \n main - end" << endl;
	return 0;
}
