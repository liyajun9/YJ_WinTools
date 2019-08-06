#include "stdafx.h"
#include "Yexception.h"

CYexception::CYexception(wchar_t *pszMethod /*= _T("unknownMethod")*/, wchar_t *pszClass/* = _T("unknownClass")*/, wchar_t *pszReason/* = _T("unknownReason")*/)
{
	m_sReason = pszReason;
	m_sClass = pszClass;
	m_sMethod = pszMethod;
	m_sMsg = L"Exception: reason(" ;
	m_sMsg.append(m_sReason); 
	m_sMsg.append(L") at ");
	m_sMsg.append(m_sClass); 
	m_sMsg.append(L"::"); 
	m_sMsg.append(m_sMethod);
}

std::wstring CYexception::GetMsg()
{
	return m_sMsg;
}

std::wstring CYexception::GetReason()
{
	return m_sReason;
}

std::wstring CYexception::GetClass()
{
	return m_sClass;
}

std::wstring CYexception::GetMethod()
{
	return m_sMethod;
}