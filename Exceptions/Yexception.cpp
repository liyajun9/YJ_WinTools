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

tstring CYException::GetMsg()
{
	return m_sMsg;
}

tstring CYException::GetReason()
{
	return m_sReason;
}

tstring CYException::GetClass()
{
	return m_sClass;
}

tstring CYException::GetMethod()
{
	return m_sMethod;
}