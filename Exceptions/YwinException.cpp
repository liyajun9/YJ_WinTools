#include "stdafx.h"
#include "YwinException.h"
#include <winbase.h>
#include <wchar.h>

#pragma warning(disable:4996)

using namespace std;
CYWinException::CYWinException(TCHAR *pszAPI /*= _T("unknownAPI")*/, TCHAR *pszMethod /*= _T("unknownMethod")*/, TCHAR *pszClass /*= _T("unknownClass")*/)
{
	m_sMethod = pszMethod;
	m_sClass = pszClass;
	m_sAPI = pszAPI;
	m_errCode = GetLastError();
	m_sReason = TranslateErrCode(m_errCode);

	TCHAR pszErrCode[MAX_LEN_ERRORCODE];
	memset(pszErrCode, 0, MAX_LEN_ERRORCODE);
	_itot(m_errCode, pszErrCode, 10);

	m_sMsg = _T("Exception: reason(");
	m_sMsg.append(pszErrCode);
	m_sMsg.append(_T(") : "));
	m_sMsg.append(m_sReason);
	m_sMsg.append(_T(" at "));
	m_sMsg.append(m_sClass);
	m_sMsg.append(_T("::"));
	m_sMsg.append(m_sMethod);
	m_sMsg.append(_T("   api = "));
	m_sMsg.append(m_sAPI);
}

DWORD CYWinException::GetErrorCode()
{
	return m_errCode;
}

tstring CYWinException::TranslateErrCode(DWORD errCode)
{
	LPVOID lpMsgBuf; 
	if(!FormatMessage( 
		FORMAT_MESSAGE_ALLOCATE_BUFFER | 
		FORMAT_MESSAGE_FROM_SYSTEM | 
		FORMAT_MESSAGE_IGNORE_INSERTS, 
		NULL, 
		errCode, 
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(LPTSTR) &lpMsgBuf, 
		0, 
		NULL 
		)){
			return TranslateErrCode(GetLastError());
	}
	tstring sRet = (LPTSTR) lpMsgBuf;
	LocalFree(lpMsgBuf);
	return sRet;
}