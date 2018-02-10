#pragma once

#include <functional>
#include <string>

#include "globalHeader.h"

class IFileAccess
{
	public:
	virtual void WriteFile(void* fileHandle, const char* buffToWrite, size_t numBytesToWrite, const std::function<void(const Result& res)>& callback) = 0;
	virtual void OpenFile(const std::string& fileName, const std::function<void(const Result& res, int fileDes)>& callback) = 0;
	virtual void RemoveFile(void* fileHandle, const std::function<void(const Result& res)>& callback) = 0;

	virtual ~IFileAccess() {}
}; 
