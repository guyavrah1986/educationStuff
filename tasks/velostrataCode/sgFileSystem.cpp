
#include <iostream>

#include "sgFileSystem.h"

using namespace std;	

SgFileSystem::SgFileSystem(const string& rootPath)
	: m_rootPath(rootPath)
{
	cout << "SgFileSystem::SgFileSystem - setting m_rootPath to:" << m_rootPath << endl;
}

SgFileSystem::~SgFileSystem()
{
	cout << "SgFileSystem::~SgFileSystemPath" << endl;
}

void SgFileSystem::Delete(const string& fileName, const function<void(Result& res)>& callback)
{

}

void SgFileSystem::Exsists(const string& fileName, char* buff, size_t numOfByteToRead, const function<void(Result& res)>& callback)
{

}
	
void SgFileSystem::Write(const string& fileName, const char* buff, size_t len, const function<void(Result& res)>& callback)
{

}

void SgFileSystem::Read(const string& fileName, char* buff, size_t numOfByteToRead, const function<void(Result& res)>& callback)
{

}

void SgFileSystem::List(const string& fileName, char* buff, size_t numOfByteToRead, const function<void(Result& res)>& callback)
{

}

string SgFileSystem::GetRootPath() const
{
	return m_rootPath;
}
