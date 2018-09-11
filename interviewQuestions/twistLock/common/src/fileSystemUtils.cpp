#include "../include/fileSystemUtils.h"

#include <iostream>
#include <unistd.h>

using namespace std;

FileSystemUtils::FileSystemUtils()
{
	cout << "FileSystemUtils::FileSystemUtils" << endl;
}

FileSystemUtils::~FileSystemUtils()
{
	cout << "FileSystemUtils::~FileSystemUtils" << endl;
}

string FileSystemUtils::GetCurrentWorkingDirectory()
{
	char currWorkingDir[1024];
	string ret;
	if (getcwd(currWorkingDir, sizeof(currWorkingDir)) != NULL)
	{
		ret = currWorkingDir;
	}

	return ret;
}
