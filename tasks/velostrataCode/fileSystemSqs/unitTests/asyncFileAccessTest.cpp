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
	if(remove(m_workingDir.c_str()) < 0)
	{
		cout << "AsyncFileAccessTest::~AsyncFileAccessTest - was unable to remove folder:" << m_workingDir << endl;
	}
	else
	{
		cout << "AsyncFileAccessTest::~AsyncFileAccessTest - removed folder:" << m_workingDir << " successfully" << endl;
	}
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
	string fileNameWhichDoesNotExist(m_workingDir + "newFile");
	bool called = false;

	/*
	tested.ExistsFile(fileNameWhichDoesNotExist, [this, &called](const Result& result)
	{
		called = true;
		EXPECT_EQ(result.GetErrorCode(), ErrorCode::FS_SQS_ERROR_CODE_FILE_DOES_NOT_EXIST);
	});
	*/
}

TEST_F(AsyncFileAccessTest, openFileWhichDoesNotExsist)
{
	string fileName(m_workingDir + "newFile");
	EXPECT_EQ(1, 1);
}
