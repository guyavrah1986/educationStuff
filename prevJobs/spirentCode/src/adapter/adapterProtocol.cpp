#include <iostream>

#include "adapProtocol.h"

using namespace std;

BaseAdapProtocol::BaseAdapProtocol()
{
	cout << "BaseAdapProtocol::BaseAdapProtocol" << endl;
}

BaseAdapProtocol::~BaseAdapProtocol()
{
	cout << "BaseAdapProtocol::~BaseAdapProtocol" << endl;
}

BaseAdapProtocol* BaseAdapProtocol::Create()
{
	cout << "BaseAdapProtocol::Create" << endl;
}
