#include "stdafx.h"
#include "YFileUtils.h"

std::wstring CYFileUtils::GetCurrentModuleDirectory()
{
	wchar_t pszFileName[MAX_PATH]; memset(pszFileName, 0, MAX_PATH);
	::GetModuleFileNameW(NULL, pszFileName, MAX_PATH);
	::PathRemoveFileSpecW(pszFileName);
	return std::wstring(pszFileName);
}