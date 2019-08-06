
// Windows Exception with GetWSALastError information
// Example:
//	try{
//			...
//			throw CYWsaException(L"api",L"method",L"class");
//		}catch(CYWsaException e){
//			...handle
//		}
// author:liyajun
#pragma once
#include "Yexception.h"
#include <concrt.h>

class CYwsaException : public CYexception
{
public:
	CYwsaException(wchar_t *pszAPI = L"unknownAPI", wchar_t *pszMethod = L"unknownMethod", wchar_t *pszClass = L"unknownClass");
	DWORD GetErrorCode();

public:
	static std::wstring GetLastErrorMsg(DWORD errcode);

protected:
	DWORD m_errCode;
	std::wstring m_sAPI;
};
