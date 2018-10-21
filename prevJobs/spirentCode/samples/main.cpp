#include <iostream>

#include "coreMgr.h"
#include "../src/globalHeader.h"

#include "../src/statsModule/cStatsCollectedBase.h"
#include "../src/statsModule/cStatsCollectedCounter.h"


using namespace std;

void mainLoop()
{
	cout << "mainLoop - please enter any key to terminate" << endl;
	int x;	
	cin >> x;
	
	return;
}

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
	CCoreClient* client = coreMgr->CreateClient(protocolList);	
	

	mainLoop();
	
	// manually delete the singleTone object
	delete client;
	cout << "\n \n main spirent - end" << endl;
	return 0;
}
