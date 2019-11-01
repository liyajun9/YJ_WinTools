#include "stdafx.h"
#include "YFileUtils.h"

#pragma comment(lib, "Shlwapi.lib")

tstring NS_Yutils::GetCurrentModuleDirectory()
{
	TCHAR pszFileName[MAX_PATH]; memset(pszFileName, 0, MAX_PATH);
	::GetModuleFileName(NULL, pszFileName, MAX_PATH);
	::PathRemoveFileSpec(pszFileName);
	return tstring(pszFileName);
}