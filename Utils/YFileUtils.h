#pragma once
#include <Shlwapi.h>

class CYFileUtils{
public:
	static std::string GetCurrentModuleDirectory();

private:
	CYFileUtils(){}
	~CYFileUtils(){}
};