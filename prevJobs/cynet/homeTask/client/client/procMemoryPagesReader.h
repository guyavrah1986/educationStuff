#pragma once

#include <windows.h>
#include <vector>

#include "cpp.hint"
#include "globalHeader.h"

class CSimpleTcpCient;

class CProcMemoryPagesReader
{
	NO_COPY(CProcMemoryPagesReader);

public:
	CProcMemoryPagesReader();
	~CProcMemoryPagesReader();

	Result FindProcessIdOfDesiredExe();
	Result SetDebugPrivildgeForCurrentProc() const;
	Result ReadAllocatedPages(IN CSimpleTcpCient& client);


	// ----- unit testing ------
	bool parseEmptyBuff();
	bool parseSingleNullByteBuff();
	bool parseSingleNonNullByteBuff();
	bool parseSingleStrWithNullCharBeforeItBuff();
	bool parseSingleStrWithoutNullCharBeforeItBuff();
	bool parseSingleStrWithoutNullCharBeforeItAndFourBytesStrAfterItBuff();
	bool parseTwoStrWithNullCharsBeforeTheFirstStrAndSeveralNullCharsBeforeTheSecondBuff();
	bool parseTwoStrWithNullCharsBeforeTheFirstStrAndSeveralNullCharsBeforeTheSecondBuffToCharVector();

	bool validateUtf16CodedBufferHasOnlyPrintableChar();

	// ----- unit testing ------

private:
	std::vector<char> parseStringFromPageToCharVector(IN const std::vector<char>& buff);
	template <typename T> std::vector<T> removeNonPrintableCharsFromBuff(IN const std::vector<char>& buff, IN T charTypeToConvert);

private:
	const SIZE_T MEGA_BYTES = 1048576;
	const std::wstring targetProcessName = L"explorer.exe";
	const std::string explorerProcessName = "explorer.exe";
	const size_t numOfCharsInValidString = 5;
	const size_t maxBuffToSendSize = 10 * MEGA_BYTES;

	DWORD m_pid;
	HANDLE m_processHandle;
};
