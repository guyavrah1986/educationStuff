#pragma once

#include "globalHeader.h"

#include <windows.h>

class CHandleWrapper
{
	NO_COPY(CHandleWrapper);

public:
	CHandleWrapper();
	~CHandleWrapper();

	HANDLE GetHandle() const;

private:
	HANDLE m_handle;
};