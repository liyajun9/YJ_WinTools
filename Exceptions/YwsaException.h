
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
#include "..\Log\tstring.h"

class CYWsaException : public CYException
{
public:
	CYWsaException(TCHAR *pszAPI = _T("unknownAPI"), TCHAR *pszMethod = _T("unknownMethod"), TCHAR *pszClass = _T("unknownClass"));
	DWORD GetErrorCode();

public:
	static tstring GetLastErrorMsg(DWORD errcode);

protected:
	DWORD m_errCode;
	tstring m_sAPI;
};
