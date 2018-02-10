#pragma once

#include "fileAccess.h"

class AsyncFileAccess : public IFileAccess
{
	public:
	AsyncFileAccess();
	virtual ~AsyncFileAccess();

	virtual void WriteFile(void* fileHandle, const char* buffToWrite, size_t numBytesToWrite, const std::function<void(const Result& res)>& callback) override;
	virtual void OpenFile(const std::string& fileName, const std::function<void(const Result& res, int fileDes)>& callback) override;
	virtual void RemoveFile(void* fileHandle, const std::function<void(const Result& res)>& callback) override;
	virtual void ExistsFile(const std::string& fileName, const std::function<void(const Result& res)>& callback) override;

};