#include "stdafx.h"
#include "YwsaException.h"
#include "YwinException.h"
#include <winsock.h>
#include <wchar.h>

CYWsaException::CYWsaException(TCHAR *pszAPI /*= _T("unknownAPI")*/, TCHAR *pszMethod /*= _T("unknownMethod")*/, TCHAR *pszClass /*= _T("unknownClass")*/)
{
	m_sClass = pszClass;
	m_sMethod = pszMethod;
	m_sAPI = pszAPI;
	m_errCode = WSAGetLastError();
	m_sReason = CYWinException::TranslateErrCode(m_errCode);

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

DWORD CYWsaException::GetErrorCode()
{
	return m_errCode;
}