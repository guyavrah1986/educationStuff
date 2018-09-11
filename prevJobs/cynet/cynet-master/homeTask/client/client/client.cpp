#include "stdafx.h"

#include "simpleTcpCient.h"
#include "procMemoryPagesReader.h"

#include <windows.h>
#include <tlhelp32.h>
#include <iostream>

using namespace std;

int invokeCodingUnitTest()
{
	cout << "invokeCodingUnitTest - start" << endl;

	CProcMemoryPagesReader procMemoryReader;
	bool res = procMemoryReader.validateUtf16CodedBufferHasOnlyPrintableChar();
	if (res == false)
	{
		cout << "unit testing - convertSimpleUtf8StringToUtf16String FAILED" << endl;
		return 1;
	}

	return 0;
}

int invokeUnitTestsFunctions()
{
	CProcMemoryPagesReader procMemoryReader;

	bool res = procMemoryReader.parseEmptyBuff();
	if (res == false)
	{
		cout << "unit testing - parseEmptyBuff FAILED" << endl;
		return 1;
	}

	res = procMemoryReader.parseSingleNullByteBuff();
	if (res == false)
	{
		cout << "unit testing - parseSingleNullByteBuff FAILED" << endl;
		return 1;
	}

	res = procMemoryReader.parseSingleNonNullByteBuff();
	if (res == false)
	{
		cout << "unit testing - parseSingleNonNullByteBuff FAILED" << endl;
		return 1;
	}

	res = procMemoryReader.parseSingleStrWithNullCharBeforeItBuff();
	if (res == false)
	{
		cout << "unit testing - parseSingleStrWithNullCharBeforeItBuff FAILED" << endl;
		return 1;
	}

	res = procMemoryReader.parseSingleStrWithoutNullCharBeforeItBuff();
	if (res == false)
	{
		cout << "unit testing - parseSingleStrWithoutNullCharBeforeItBuff FAILED" << endl;
		return 1;
	}
	
	res = procMemoryReader.parseSingleStrWithoutNullCharBeforeItAndFourBytesStrAfterItBuff();
	if (res == false)
	{
		cout << "unit testing - parseSingleStrWithoutNullCharBeforeItAndFourBytesStrAfterItBuff FAILED" << endl;
		return 1;
	}

	res = procMemoryReader.parseTwoStrWithNullCharsBeforeTheFirstStrAndSeveralNullCharsBeforeTheSecondBuff();
	if (res == false)
	{
		cout << "unit testing - parseTwoStrWithNullCharsBeforeTheFirstStrAndSeveralNullCharsBeforeTheSecondBuff FAILED" << endl;
		return 1;
	}

	res = procMemoryReader.parseTwoStrWithNullCharsBeforeTheFirstStrAndSeveralNullCharsBeforeTheSecondBuffToCharVector();
	if (res == false)
	{
		cout << "unit testing - parseTwoStrWithNullCharsBeforeTheFirstStrAndSeveralNullCharsBeforeTheSecondBuffToCharVector FAILED" << endl;
		return 1;
	}
	
	return 0;
}

int main(int argc, char* argv [])
{
#ifndef UNIT_TESTING
	if (argc != 3)
	{
		cerr << "main - expecting two arguments: ip port - aborting..." << endl;
		return 1;
	}

	if (argv[1] == NULL || argv[2] == NULL)
	{
		cerr << "main - ip and/or port which were provided is (are) invalid (NULL) - aborting..." << endl;
		return 1;
	}

	// Create the TCP client to talk to the server
	CSimpleTcpCient client(argv[1], argv[2]);

	// Create the Process memory reader that will handle reading the 
	// allocated memory pages of the executable
	CProcMemoryPagesReader procMemoryReader;
	
	// Find the PID of the executable we wish to read its memory
	Result res = procMemoryReader.FindProcessIdOfDesiredExe();
	if (res.IsSuccess() == false)
	{
		cerr << "main - could not find PID of the desired exe, aborting..." << endl;
		return 1;
	}

	res = procMemoryReader.SetDebugPrivildgeForCurrentProc();
	if (res.IsSuccess() == false)
	{
		cerr << "main - was unable to set debug privildge for the current process, aborting..." << endl;
		return 1;
	}

	res = procMemoryReader.ReadAllocatedPages(client);
	if (res.IsSuccess() == false)
	{
		cerr << "main - was unable to read all the pages of the executable and/or sent it to the server, aborting..." << endl;
		return 1;
	}

	res = client.DisconnectFromServer();
	if (res.IsSuccess() == false)
	{
		cerr << "main - was unable to successfully disconnect from the server" << endl;
		return 1;
	}
#endif /* UNIT_TESTING */
	
#ifdef UNIT_TESTING
	// ------------
	// unit testing
	// ------------
	/*
	int res1 = invokeUnitTestsFunctions();
	if (res1 != 0)
	{
		cerr << "main (invokeUnitTestsFunctions) - one (or more) tests caused an error, aborting..." << endl;
		return 1;
	}
	*/
	int res2 = invokeCodingUnitTest();
	if (res2 != 0)
	{
		cerr << "main (invokeCodingUnitTest) - one (or more) tests caused an error, aborting..." << endl;
		return 1;
	}
#endif /* UNIT_TESTING */

	char wait;
	cout << "main - enter any char and press ENTER to terminate" << endl;
	cin >> wait;
	return 0;
}
