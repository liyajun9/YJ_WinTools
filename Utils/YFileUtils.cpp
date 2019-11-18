#include "stdafx.h"
#include "YFileUtils.h"

#pragma comment(lib, "Shlwapi.lib")

tstring NS_Yutils::GetModuleFilePath(HINSTANCE hModule)
{
	TCHAR pszFileName[MAX_PATH]; memset(pszFileName, 0, MAX_PATH);
	::GetModuleFileName(hModule, pszFileName, MAX_PATH);
	::PathRemoveFileSpec(pszFileName);
	return tstring(pszFileName);
}

tstring NS_Yutils::GetModuleFilePathWithSlash(HINSTANCE hModule)
{
	TCHAR pszFileName[MAX_PATH]; memset(pszFileName, 0, MAX_PATH);
	::GetModuleFileName(hModule, pszFileName, MAX_PATH);
	return tstring(pszFileName);
}