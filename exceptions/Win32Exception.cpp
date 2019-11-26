#include "stdafx.h"
#include "Win32Exception.h"
#include <winbase.h>
#include <wchar.h>
#include <sstream>

#pragma warning(disable:4996)
using namespace std;

std::string TranslateErrCode(DWORD errCode)
{
	LPVOID lpMsgBuf; 
	if(!FormatMessageA( 
		FORMAT_MESSAGE_ALLOCATE_BUFFER | 
		FORMAT_MESSAGE_FROM_SYSTEM | 
		FORMAT_MESSAGE_IGNORE_INSERTS, 
		NULL, 
		errCode, 
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(LPSTR) &lpMsgBuf, 
		0, 
		NULL 
		)){
			return TranslateErrCode(GetLastError());
	}
	std::string sRet = (LPSTR) lpMsgBuf;
	LocalFree(lpMsgBuf);
	return sRet;
}

CWin32Exception::CWin32Exception(const char* file, const char* func, int line) throw()
	:m_szFile(file)
	,m_szFunc(func)
	,m_nLine(line)
{
	m_dwErrorCode = GetLastError();
	m_sMessage = TranslateErrCode(m_dwErrorCode);
}

CWin32Exception::CWin32Exception(const char* file, const char* func) throw()
	:m_szFile(file)
	,m_szFunc(func)
	,m_nLine(-1)
{
	m_dwErrorCode = GetLastError();
	m_sMessage = TranslateErrCode(m_dwErrorCode);
}

CWin32Exception::CWin32Exception(const char* file) throw()
	:m_szFile(file)
	,m_szFunc("<unknown func>")
	,m_nLine(-1)
{
	m_dwErrorCode = GetLastError();
	m_sMessage = TranslateErrCode(m_dwErrorCode);
}

CWin32Exception::CWin32Exception() throw()
	:m_szFile("<unknown file>")
	,m_szFunc("<unknown func>")
	,m_nLine(-1)
{
	m_dwErrorCode = GetLastError();
	m_sMessage = TranslateErrCode(m_dwErrorCode);
}

DWORD CWin32Exception::GetErrorCode() const
{
	return m_dwErrorCode;
}

std::string CWin32Exception::GetMessage() const
{
	return m_sMessage;
}

const char* CWin32Exception::GetClassName() const
{
	return "CWin32Exception";
}

const char* CWin32Exception::what() const throw()
{
	return ToString().c_str();
}

const std::string& CWin32Exception::ToString() const
{
	if(m_sWhat.empty()){
		stringstream sstr;
		sstr << GetClassName() 
			<< ":: "<< m_szFile 
			<< "(" << m_nLine << ")"
			<< "-> " << m_szFunc 
			<< "(" << m_dwErrorCode << ")"
			<< ": " << m_sMessage;

		m_sWhat = sstr.str();
	}
	return m_sWhat;
}

