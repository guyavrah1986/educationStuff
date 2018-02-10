#include <iostream>
#include <sys/stat.h>
#include <fcntl.h>

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

	// implementation specific - cast to int
	int handle = *(static_cast<int*>(fileHandle));
	cout << "AsyncFileAccess::WriteFile - got file handle:" << handle << endl;

}

void AsyncFileAccess::OpenFile(const string& fileName, const std::function<void(const Result& res, int fileDes)>& callback)
{
	cout << "AsyncFileAccess::OpenFile - trying to open file name:" << fileName << endl;
	Result res(ErrorCode::FS_SQS_ERROR_CODE_GENERAL_FAUILRE);

	int fd = open(fileName.c_str(), O_CREAT | O_WRONLY, S_IRUSR);
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



