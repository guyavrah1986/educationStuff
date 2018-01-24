#include <iostream>

#include "cStatsCollectedBase.h"
#include "cStatsCollectedCounter.h"

using namespace std;

int main(int argc, char** argv)
{
	cout << "main spirent statistics module - start" << endl;

	CStatsCollectedCounter collectedCounter("sample collected counter", true, true);

	cout << "\n \n main spirent statistics module - end" << endl;
	return 0;
}
