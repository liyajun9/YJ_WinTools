// Windows Exception with GetLastError information
// Example:
//	try{
//			...
//			throw CYWinException(L"api",L"method",L"class");
//		}catch(CYWinException e){
//			...handle
//		}
// author:liyajun
#pragma once
#include "Yexception.h"
#include <concrt.h>

#define MAX_LEN_ERRORCODE 16


class CYWinException : public CYException
{
public:
	CYWinException(wchar_t *pszAPI = L"unknownAPI", wchar_t *pszMethod = L"unknownMethod", wchar_t *pszClass = L"unknownClass");
	DWORD GetErrorCode();

public:
	static std::wstring TranslateErrCode(DWORD errCode);

protected:
	DWORD m_errCode;
	std::wstring m_sAPI;
};
