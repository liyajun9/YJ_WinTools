#include "stdafx.h"
#include "Yexception.h"

CYException::CYException()
{

}

CYException::CYException(TCHAR *pszReason, TCHAR *pszMethod /*= L"unknownMethod"*/, TCHAR *pszClass /*= L"unknownClass"*/)
{
	m_sReason = pszReason;
	m_sClass = pszClass;
	m_sMethod = pszMethod;
	m_sMsg = _T("Exception: reason(") ;
	m_sMsg.append(m_sReason); 
	m_sMsg.append(_T(") at "));
	m_sMsg.append(m_sClass); 
	m_sMsg.append(_T("::")); 
	m_sMsg.append(m_sMethod);
}

std::wstring CYException::GetMsg()
{
	return m_sMsg;
}

std::wstring CYException::GetReason()
{
	return m_sReason;
}

std::wstring CYException::GetClass()
{
	return m_sClass;
}

std::wstring CYException::GetMethod()
{
	return m_sMethod;
}