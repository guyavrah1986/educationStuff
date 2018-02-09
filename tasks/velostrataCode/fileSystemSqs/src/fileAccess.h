#pragma once

#include <functional>
#include <string>

#include "globalHeader.h"

class IFileAccess
{
	public:
	virtual void WriteFile(const std::string& fileName, const char* buffToWrite, size_t numBytesToWrite, const std::function<void(Result& res)>& callback) = 0;
	virtual void OpenFile(const std::string& fileName, const std::function<void(Result& res, int fileDes)>& callback) = 0;

	virtual ~IFileAccess() {}
}; 
