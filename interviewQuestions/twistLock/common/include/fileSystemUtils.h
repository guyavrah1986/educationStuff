#pragma once

#include <string>

#include "../../src/include/globalInternalInclude.h"

class FileSystemUtils
{

	NO_COPY(FileSystemUtils);

public:
	FileSystemUtils();
	~FileSystemUtils();

	static std::string GetCurrentWorkingDirectory();
};
