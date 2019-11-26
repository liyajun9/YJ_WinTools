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

tstring& NS_Yutils::RemoveFileExtension(tstring& sFileName)
{
	tstring::size_type nPos = sFileName.find_last_of(_T('.'));
	if(nPos != tstring::npos){
		sFileName = sFileName.substr(0,nPos);
	}
	return sFileName;
}

void NS_Yutils::TraverseDirectory(const tstring& sDir, void(*cb)(const TCHAR *pszFileName))
{
	HANDLE hFind = INVALID_HANDLE_VALUE;
	WIN32_FIND_DATA ffd;

	tstring sWildcard = sDir;
	sWildcard.append(_T("\\*.*"));
	hFind = FindFirstFile(sWildcard.c_str(), &ffd);
	if(hFind == INVALID_HANDLE_VALUE)
		return;

	TCHAR pszFile[MAX_PATH];
	do{
		if(_tcscmp(ffd.cFileName, _T(".")) != 0 && _tcscmp(ffd.cFileName, _T("..")) != 0){
			if(ffd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY){
				continue;
			}else{
				memset(pszFile, 0, MAX_PATH);
				memcpy(pszFile, sDir.c_str(), sDir.length());
				memcpy(pszFile + sDir.length(), _T("\\"), 1);
				memcpy(pszFile + sDir.length() + 1, ffd.cFileName, _tcslen(ffd.cFileName));
				cb(pszFile);
			}
		}
	}while(FindNextFile(hFind, &ffd) != 0);

	FindClose(hFind);
	hFind = INVALID_HANDLE_VALUE;
}