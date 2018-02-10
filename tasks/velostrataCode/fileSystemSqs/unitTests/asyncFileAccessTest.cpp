#include <iostream>
#include <cstring>
#include <sys/stat.h>
#include <sys/types.h>

#include "asyncFileAccessTest.h"

using namespace std;

AsyncFileAccessTest::AsyncFileAccessTest()
	: tested()
{
	cout << "AsyncFileAccessTest::AsyncFileAccessTest" << endl;
	char cwd[1024];
	if (getcwd(cwd, sizeof(cwd)) != NULL)
	{
		string tmp(cwd);
		m_workingDir = tmp;
		m_workingDir += FILES_FOLDER;
		int result = mkdir(m_workingDir.c_str(), 0777);
		cout << "AsyncFileAccessTest::AsyncFileAccessTest - files will be written into:" <<  m_workingDir << endl;
	}
}

AsyncFileAccessTest::~AsyncFileAccessTest()
{
	cout << "AsyncFileAccessTest::~AsyncFileAccessTest" << endl;
	tested.RemoveFolder(m_workingDir, [this](const Result& res)
	{
		if (res.IsSuccess() == false)
		{
			cerr << "AsyncFileAccessTest::~AsyncFileAccessTest - was unable to remove the folder that was used for the unit tests,"
					"please check it out !!" << endl;
		}
		else
		{
			cout << "AsyncFileAccessTest::~AsyncFileAccessTest - removed  folder:" << m_workingDir << " successfully" << endl;
		}
	});
}

void AsyncFileAccessTest::SetUp()
{
	cout << "AsyncFileAccessTest::SetUp" << endl;
}

void AsyncFileAccessTest::TearDown()
{
	cout << "AsyncFileAccessTest::TearDown" << endl;
}


// =====================================================================================================================
// GTests for this class
// =====================================================================================================================

TEST_F(AsyncFileAccessTest, lookForFileWhichDoesNotExsist)
{
	cout << "AsyncFileAccessTest::lookForFileWhichDoesNotExsist" << endl;
	string fileNameWhichDoesNotExist(m_workingDir + "/doesNotExist");
	bool called = false;

	tested.ExistsFile(fileNameWhichDoesNotExist, [this, &called](const Result& result)
	{
		called = true;
		EXPECT_EQ(result.GetErrorCode(), ErrorCode::FS_SQS_ERROR_CODE_FILE_DOES_NOT_EXIST);
	});
	EXPECT_EQ(called, true);
}

TEST_F(AsyncFileAccessTest, openFileThatDoesNotExist)
{
	cout << "AsyncFileAccessTest::openFileThatDoesNotExist" << endl;

	string fileName(m_workingDir + "/newFile");
	bool called = false;
	tested.OpenFile(fileName, [this, &called](const Result& res, int fileDes)
	{
		called = true;
		EXPECT_NE(fileDes, -1);
		EXPECT_EQ(res.GetErrorCode(), ErrorCode::FS_SQS_ERROR_CODE_SUCCESS);
	});

	EXPECT_EQ(called, true);
}

TEST_F(AsyncFileAccessTest, lookForFileWhichExsist)
{
	cout << "AsyncFileAccessTest::lookForFileWhichExsist" << endl;
	string fileNameWhichExist(m_workingDir + "/fileThatExsits");
	int fd;
	tested.OpenFile(fileNameWhichExist, [this, &fd](const Result& res, int fileDes)
	{
		fd = fileDes;
		EXPECT_EQ(res.GetErrorCode(), ErrorCode::FS_SQS_ERROR_CODE_SUCCESS);
	});

	bool called = false;
	tested.ExistsFile(fileNameWhichExist, [this, &called](const Result& result)
	{
		called = true;
		EXPECT_EQ(result.GetErrorCode(), ErrorCode::FS_SQS_ERROR_CODE_FILE_EXISTS);
	});
	EXPECT_EQ(called, true);
}

TEST_F(AsyncFileAccessTest, writeToNewFile)
{
	cout << "AsyncFileAccessTest::writeToNewFile" << endl;
	string fileName(m_workingDir + "/newFileForWrite");
	int fd;
	tested.OpenFile(fileName, [this, &fd](const Result& res, int fileDes)
	{
		fd = fileDes;
		EXPECT_EQ(res.GetErrorCode(), ErrorCode::FS_SQS_ERROR_CODE_SUCCESS);
	});

	bool called = false;
	void* handle = static_cast<void*>(&fd);
	char buff [] = "abcd";
	size_t numBytesToWrite = strlen(buff);
	tested.WriteFile(handle, buff, numBytesToWrite, [this, &called](const Result& res)
	{
		called = true;
		EXPECT_EQ(res.GetErrorCode(), ErrorCode::FS_SQS_ERROR_CODE_SUCCESS);
	});

	EXPECT_EQ(called, true);
}

TEST_F(AsyncFileAccessTest, removeFile)
{
	cout << "AsyncFileAccessTest::removeFile" << endl;
	string fileName(m_workingDir + "/fileToRemove");
	int fd;
	tested.OpenFile(fileName, [this, &fd](const Result& res, int fileDes)
	{
		fd = fileDes;
	});

	void* handle = static_cast<void*>(&fd);
	char buff [] = "abcde";
	size_t numBytesToWrite = strlen(buff);
	tested.WriteFile(handle, buff, numBytesToWrite, [this](const Result& res)
	{
		EXPECT_EQ(res.IsSuccess(), true);
	});

	bool called = false;
	tested.RemoveFile(fileName, [this, &called](const Result& res)
	{
		called = true;
		EXPECT_EQ(res.IsSuccess(), true);
	});
	EXPECT_EQ(called, true);
}

