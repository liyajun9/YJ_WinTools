#include "stdafx.h"
#include "YwsaException.h"
#include <winsock.h>
#include <wchar.h>
#include <sstream>

#pragma warning(disable:4996)
using namespace std;

std::string TranslateErrCode(DWORD errCode);

CYWSAException::CYWSAException(const char* file, const char* func, int line) throw()
	:m_szFile(file)
	,m_szFunc(func)
	,m_nLine(line)
{
	m_dwErrorCode = WSAGetLastError();
	m_sMessage = TranslateErrCode(m_dwErrorCode);
}

CYWSAException::CYWSAException(const char* file, const char* func) throw()
	:m_szFile(file)
	,m_szFunc(func)
	,m_nLine(-1)
{
	m_dwErrorCode = WSAGetLastError();
	m_sMessage = TranslateErrCode(m_dwErrorCode);
}

CYWSAException::CYWSAException(const char* file) throw()
	:m_szFile(file)
	,m_szFunc("<unknown func>")
	,m_nLine(-1)
{
	m_dwErrorCode = WSAGetLastError();
	m_sMessage = TranslateErrCode(m_dwErrorCode);
}

CYWSAException::CYWSAException() throw()
	:m_szFile("<unknown file>")
	,m_szFunc("<unknown func>")
	,m_nLine(-1)
{
	m_dwErrorCode = WSAGetLastError();
	m_sMessage = TranslateErrCode(m_dwErrorCode);
}

DWORD CYWSAException::GetErrorCode() const
{
	return m_dwErrorCode;
}

std::string CYWSAException::GetMessage() const
{
	return m_sMessage;
}

const char* CYWSAException::GetClassName() const
{
	return "WSAException";
}

const char* CYWSAException::what() const throw()
{
	return ToString().c_str();
}

const std::string& CYWSAException::ToString() const
{
	if(m_sWhat.empty()){
		stringstream sstr;
		sstr << GetClassName() << "-> ";
		if(m_nLine > 0){
			sstr << m_szFile << "(" << m_nLine << ")";
		}
		sstr << ": " << m_szFunc << ": (" << m_dwErrorCode << ")" <<m_sMessage;

		m_sWhat = sstr.str();
	}
	return m_sWhat;
}