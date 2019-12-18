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

YWin32Exception::YWin32Exception(const char* file, const char* func, int line) throw()
	:m_sFile(file)
	,m_sFunc(func)
	,m_nLine(line)
{
	m_dwErrorCode = GetLastError();
	m_sMessage = TranslateErrCode(m_dwErrorCode);
}

YWin32Exception::YWin32Exception(const char* file, const char* func) throw()
	:m_sFile(file)
	,m_sFunc(func)
	,m_nLine(-1)
{
	m_dwErrorCode = GetLastError();
	m_sMessage = TranslateErrCode(m_dwErrorCode);
}

YWin32Exception::YWin32Exception(const char* file) throw()
	:m_sFile(file)
	,m_sFunc("<unknown func>")
	,m_nLine(-1)
{
	m_dwErrorCode = GetLastError();
	m_sMessage = TranslateErrCode(m_dwErrorCode);
}

YWin32Exception::YWin32Exception() throw()
	:m_sFile("<unknown file>")
	,m_sFunc("<unknown func>")
	,m_nLine(-1)
{
	m_dwErrorCode = GetLastError();
	m_sMessage = TranslateErrCode(m_dwErrorCode);
}

DWORD YWin32Exception::GetErrorCode() const
{
	return m_dwErrorCode;
}

std::string YWin32Exception::GetMessage() const
{
	return m_sMessage;
}

const char* YWin32Exception::GetClassName() const
{
	return "YWin32Exception";
}

const char* YWin32Exception::what() const throw()
{
	return ToString().c_str();
}

const std::string& YWin32Exception::ToString() const
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

