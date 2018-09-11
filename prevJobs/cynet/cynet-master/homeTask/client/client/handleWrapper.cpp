#include "stdafx.h"
#include <iostream>
#include <windows.h>
#include <tlhelp32.h>

#include "handleWrapper.h"

using namespace std;

CHandleWrapper::CHandleWrapper()
{
	cout << "CHandleWrapper::CHandleWrapper" << endl;
	m_handle = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0); //all processes
}

CHandleWrapper::~CHandleWrapper()
{
	BOOL retVal = CloseHandle(m_handle);
	if (retVal == 0)
	{
		cerr << "CHandleWrapper::~CHandleWrapper - encountered an error when trying to close handle:" << GetLastError() << endl;
	}
}

HANDLE CHandleWrapper::GetHandle() const
{
	return m_handle;
}