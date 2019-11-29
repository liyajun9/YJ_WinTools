#include "stdafx.h"
#include "WSAException.h"
#include <winsock.h>
#include <wchar.h>
#include <sstream>

#pragma warning(disable:4996)
using namespace std;

std::string TranslateErrCode(DWORD errCode);

CWSAException::CWSAException(const char* file, const char* func, int line) throw()
	:m_sFile(file)
	,m_sFunc(func)
	,m_nLine(line)
{
	m_dwErrorCode = WSAGetLastError();
	m_sMessage = TranslateErrCode(m_dwErrorCode);
}

CWSAException::CWSAException(const char* file, const char* func) throw()
	:m_sFile(file)
	,m_sFunc(func)
	,m_nLine(-1)
{
	m_dwErrorCode = WSAGetLastError();
	m_sMessage = TranslateErrCode(m_dwErrorCode);
}

CWSAException::CWSAException(const char* file) throw()
	:m_sFile(file)
	,m_sFunc("<unknown func>")
	,m_nLine(-1)
{
	m_dwErrorCode = WSAGetLastError();
	m_sMessage = TranslateErrCode(m_dwErrorCode);
}

CWSAException::CWSAException() throw()
	:m_sFile("<unknown file>")
	,m_sFunc("<unknown func>")
	,m_nLine(-1)
{
	m_dwErrorCode = WSAGetLastError();
	m_sMessage = TranslateErrCode(m_dwErrorCode);
}

DWORD CWSAException::GetErrorCode() const
{
	return m_dwErrorCode;
}

std::string CWSAException::GetMessage() const
{
	return m_sMessage;
}

const char* CWSAException::GetClassName() const
{
	return "CWSAException";
}

const char* CWSAException::what() const throw()
{
	return ToString().c_str();
}

const std::string& CWSAException::ToString() const
{
	if(m_sWhat.empty()){
		stringstream sstr;
		sstr << GetClassName() 
			<< ":: "<< m_sFile 
			<< "(" << m_nLine << ")"
			<< "-> " << m_sFunc 
			<< "(" << m_dwErrorCode << ")"
			<< ": " << m_sMessage;

		m_sWhat = sstr.str();
	}
	return m_sWhat;
}