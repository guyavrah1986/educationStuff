#include <iostream>
#include <fcntl.h>
#include <unistd.h>

#include "asyncFileAccess.h"

using namespace std;

AsyncFileAccess::AsyncFileAccess()
{
	cout << "AsyncFileAccess::AsyncFileAccess" << endl;
}

AsyncFileAccess::~AsyncFileAccess()
{
	cout << "AsyncFileAccess::~AsyncFileAccess" << endl;
}

void AsyncFileAccess::WriteFile(void* fileHandle, const char* buffToWrite, size_t numBytesToWrite, const function<void(const Result& res)>& callback)
{
	if (fileHandle == nullptr)
	{
		cerr << "AsyncFileAccess::WriteFile - fileHandle is NULL, terminating..." << endl;
		callback(Result(ErrorCode::FS_SQS_ERROR_CODE_GENERAL_FAUILRE));
		return;
	}

	// NOTE: implementation specific - cast to int
	int handle = *(static_cast<int*>(fileHandle));
	//cout << "AsyncFileAccess::WriteFile - got file handle:" << handle << endl;
    size_t bytesWritten = write(handle, buffToWrite, numBytesToWrite);
	cout << "AsyncFileAccess::WriteFile - written successfully " << bytesWritten << " bytes into file handle:" << handle << endl;
	callback(Result(ErrorCode::FS_SQS_ERROR_CODE_SUCCESS));\
}

void AsyncFileAccess::OpenFile(const string& fileName, const std::function<void(const Result& res, int fileDes)>& callback)
{
	cout << "AsyncFileAccess::OpenFile - trying to open file name:" << fileName << endl;
	Result res(ErrorCode::FS_SQS_ERROR_CODE_GENERAL_FAUILRE);

	int fd = open(fileName.c_str(), O_CREAT | O_WRONLY, S_IRUSR | S_IWUSR);
	if(fd != -1)
	{
		cout << "AsyncFileAccess::OpenFile - file:" << fileName << " has been created successfully" << endl;
	    res = ErrorCode::FS_SQS_ERROR_CODE_SUCCESS;
	}
	else
	{
		cerr << "AsyncFileAccess::OpenFile - file:" << fileName << " has NOT been created" << endl;
	}

	callback(res, fd);
}

void AsyncFileAccess::RemoveFile(void* fileHandle, const function<void(const Result& res)>& callback)
{
	if (fileHandle == nullptr)
	{
		cerr << "AsyncFileAccess::RemoveFile - got NULL file handle, terminating..." << endl;
		callback(Result(ErrorCode::FS_SQS_ERROR_CODE_GENERAL_FAUILRE));
		return;
	}
}

void AsyncFileAccess::ExistsFile(const string& fileName, const function<void(const Result& res)>& callback)
{
	if(access(fileName.c_str(), F_OK) != -1)
	{
		cout << "AsyncFileAccess::ExistsFile - file:" << fileName << " already exists" << endl;
		callback(Result(ErrorCode::FS_SQS_ERROR_CODE_FILE_EXISTS));
	}
	else
	{
		cout << "AsyncFileAccess::ExistsFile - file:" << fileName << " DOES NOT exist" << endl;
		callback(Result(ErrorCode::FS_SQS_ERROR_CODE_FILE_DOES_NOT_EXIST));
	}
}


