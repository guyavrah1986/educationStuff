#include <stdio.h>

void mainLoop()
{
	printf("mainLoop - please enter any key to terminate \n");

	return;
}

int main(int argc, char** argv)
{
	printf("main spirent - start\n");

	//CStatsCollectedCounter collectedCounter("sample collected counter", true, true);

	/*
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
	*/

	mainLoop();

	printf("\n \n main spirent - end \n");
	return 0;
}
