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
#include "..\Log\tstring.h"

#define MAX_LEN_ERRORCODE 16


class CYWinException : public CYException
{
public:
	CYWinException(TCHAR *pszAPI = _T("unknownAPI"), TCHAR *pszMethod = _T("unknownMethod"), TCHAR *pszClass = _T("unknownClass"));
	DWORD GetErrorCode();

public:
	static tstring TranslateErrCode(DWORD errCode);

protected:
	DWORD m_errCode;
	tstring m_sAPI;
};
