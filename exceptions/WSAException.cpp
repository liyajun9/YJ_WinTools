#include "stdafx.h"
#include "WSAException.h"
#include <winsock.h>
#include <wchar.h>
#include <sstream>

#pragma warning(disable:4996)

std::string TranslateErrCode(DWORD errCode);

YWSAException::YWSAException(const char* file, const char* func, int line) throw()
	:m_sFile(file)
	,m_sFunc(func)
	,m_nLine(line)
{
	m_dwErrorCode = WSAGetLastError();
	m_sMessage = TranslateErrCode(m_dwErrorCode);
}

YWSAException::YWSAException(const char* file, const char* func) throw()
	:m_sFile(file)
	,m_sFunc(func)
	,m_nLine(-1)
{
	m_dwErrorCode = WSAGetLastError();
	m_sMessage = TranslateErrCode(m_dwErrorCode);
}

YWSAException::YWSAException(const char* file) throw()
	:m_sFile(file)
	,m_sFunc("<unknown func>")
	,m_nLine(-1)
{
	m_dwErrorCode = WSAGetLastError();
	m_sMessage = TranslateErrCode(m_dwErrorCode);
}

YWSAException::YWSAException() throw()
	:m_sFile("<unknown file>")
	,m_sFunc("<unknown func>")
	,m_nLine(-1)
{
	m_dwErrorCode = WSAGetLastError();
	m_sMessage = TranslateErrCode(m_dwErrorCode);
}

DWORD YWSAException::GetErrorCode() const
{
	return m_dwErrorCode;
}

std::string YWSAException::GetMessage() const
{
	return m_sMessage;
}

const char* YWSAException::GetClassName() const
{
	return "YWSAException";
}

const char* YWSAException::what() const throw()
{
	return ToString().c_str();
}

const std::string& YWSAException::ToString() const
{
	if(m_sWhat.empty()){
		std::stringstream sstr;
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