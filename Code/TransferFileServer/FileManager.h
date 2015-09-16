#pragma once
#include <string>
class FileManager
{
public:
	static void CreateFile(std::string filename);
	FileManager(void);
	~FileManager(void);
};

