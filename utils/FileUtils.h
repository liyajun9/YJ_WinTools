#pragma once
#include <Shlwapi.h>
#include "ttype.h"

namespace NS_Yutils{

tstring GetModuleFilePath(HINSTANCE hModule = 0); 
tstring GetModuleFilePathWithSlash(HINSTANCE hModule = 0); 
tstring& RemoveFileExtension(tstring& sFileName);
void TraverseDirectory(const tstring& sDir, void(*cb)(const TCHAR *pszFileName));//traverse files in a directory but not including directories. sDir must not end with '\' or '/'
};