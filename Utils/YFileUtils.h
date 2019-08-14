#pragma once
#include <Shlwapi.h>
#include "..\Log\tstring.h"

class CYFileUtils{
public:
	static tstring GetCurrentModuleDirectory();

private:
	CYFileUtils(){}
	~CYFileUtils(){}
};