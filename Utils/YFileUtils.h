#pragma once
#include <Shlwapi.h>

class CYFileUtils{
public:
	static std::wstring GetCurrentModuleDirectory();

private:
	CYFileUtils(){}
	~CYFileUtils(){}
};