#include "stdafx.h"
#include "Exception.h"

namespace YJ_WinTools{

CException::CException(PCTSTR pszReason/* = _T("unknownReason")*/, PCTSTR pszClass/* = _T("unknownClass")*/, PCTSTR pszMethod /*= _T("unknownMethod")*/)
{
	m_sReason = pszReason;
	m_sClassName = pszClass;
	m_sMethodName = pszMethod;
#ifdef _UNICODE
	m_sMsg = _T("Exception: Reason(") +  m_sReason + _T(") at ") + m_sClassName + _T("::") + m_sMethodName;
#else
	m_sMsg = "Exception: Reason(" + m_sReason + ") at " + m_sClassName + "::" + m_sMethodName;
#endif
}

_tstring CException::GetMsg()
{
	return m_sMsg;
}

_tstring CException::GetReason()
{
	return m_sReason;
}

_tstring CException::GetClass()
{
	return m_sClassName;
}

_tstring CException::GetMethod()
{
	return m_sMethodName;
}

void CException::MessageBox(HWND hWnd)
{
#ifdef _UNICODE
	::MessageBox(hWnd, _T("Error"), GetMsg().c_str(), MB_ICONSTOP);
#else
	::MessageBox(hWnd, "Error", GetMsg().c_str(), MB_ICONSTOP);
#endif
}

}