#include <iostream>

#include "coreMgr.h"
#include "globalHeader.h"

#include "cStatsCollectedBase.h"
#include "cStatsCollectedCounter.h"

using namespace std;

int main(int argc, char** argv)
{
	cout << "main spirent - start" << endl;

	//CStatsCollectedCounter collectedCounter("sample collected counter", true, true);

	CCoreMgr* coreMgr = CCoreMgr::GetInstance();

	if (coreMgr != nullptr)
	{
		cout << "main spirent - created CCoreMgr successfully" << endl;
	}
	else 
	{
		cout << "main spirent - had an error creating an instance of a CCoreMgr, aborting..." << endl;
		return 1;
	}	


	const list<EnProtocolType> protocolList = { SP_M2M_PROTOCOL_TYPE_LWM2M, SP_M2M_PROTOCOL_TYPE_MQTT };
		
	
	cout << "\n \n main spirent - end" << endl;
	return 0;
}
