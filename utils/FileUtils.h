#pragma once
#include <Shlwapi.h>
#include "Macros\ttype.h"

namespace NS_Yutils{

tstring getModuleFilePath(HINSTANCE hModule = 0, bool removeLastSlash = true); 
tstring& removeSuffix(tstring& sFileName);
void HandleFiles(const tstring& sDir, void(*cb)(const TCHAR *pszFileName));//not including files in directories. sDir without '\' or '/'
};