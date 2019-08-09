#include "stdafx.h"
#include "Yexception.h"

CYException::CYException()
{

}

CYException::CYException(wchar_t *pszReason, wchar_t *pszMethod /*= L"unknownMethod"*/, wchar_t *pszClass /*= L"unknownClass"*/)
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