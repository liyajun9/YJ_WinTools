#include "stdafx.h"
#include "YFileUtils.h"

tstring CYFileUtils::GetCurrentModuleDirectory()
{
	TCHAR pszFileName[MAX_PATH]; memset(pszFileName, 0, MAX_PATH);
	::GetModuleFileName(NULL, pszFileName, MAX_PATH);
	::PathRemoveFileSpec(pszFileName);
	return tstring(pszFileName);
}