#include "stdafx.h"
#include "YwsaException.h"
#include "YwinException.h"
#include <winsock.h>
#include <wchar.h>

CYwsaException::CYwsaException(wchar_t *pszAPI /*= L"unknownAPI"*/, wchar_t *pszMethod /*= L"unknownMethod"*/, wchar_t *pszClass /*= L"unknownClass"*/)
{
	m_sClass = pszClass;
	m_sMethod = pszMethod;
	m_sAPI = pszAPI;
	m_errCode = WSAGetLastError();
	m_sReason = CYwinException::TranslateErrCode(m_errCode);

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

DWORD CYwsaException::GetErrorCode()
{
	return m_errCode;
}