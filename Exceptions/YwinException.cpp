#include "stdafx.h"
#include "YwinException.h"
#include <winbase.h>
#include <wchar.h>

using namespace std;
CYwinException::CYwinException(wchar_t *pszAPI /*= L"unknownAPI"*/, wchar_t *pszMethod /*= L"unknownMethod"*/, wchar_t *pszClass /*= L"unknownClass"*/)
{
	m_sMethod = pszMethod;
	m_sClass = pszClass;
	m_sAPI = pszAPI;
	m_errCode = GetLastError();
	m_sReason = TranslateErrCode(m_errCode);

	wchar_t pszErrCode[MAX_LEN_ERRORCODE];
	memset(pszErrCode, 0, MAX_LEN_ERRORCODE);
	_itow(m_errCode, pszErrCode, 10);

	m_sMsg = L"Exception: reason(";
	m_sMsg.append(pszErrCode);
	m_sMsg.append(L") : ");
	m_sMsg.append(m_sReason);
	m_sMsg.append(L" at ");
	m_sMsg.append(m_sClass);
	m_sMsg.append(L"::");
	m_sMsg.append(m_sMethod);
	m_sMsg.append(L"   api = ");
	m_sMsg.append(m_sAPI);
}

DWORD CYwinException::GetErrorCode()
{
	return m_errCode;
}

std::wstring CYwinException::TranslateErrCode(DWORD errCode)
{
	LPVOID lpMsgBuf; 
	if(!FormatMessageW( 
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
	std::wstring sRet = (LPTSTR) lpMsgBuf;
	LocalFree(lpMsgBuf);
	return sRet;
}