#include "stdafx.h"
#include "YFileUtils.h"

std::string CYFileUtils::GetCurrentModuleDirectory()
{
	char pszFileName[MAX_PATH]; memset(pszFileName, 0, MAX_PATH);
	::GetModuleFileNameA(NULL, pszFileName, MAX_PATH);
	::PathRemoveFileSpecA(pszFileName);
	return std::string(pszFileName);
}