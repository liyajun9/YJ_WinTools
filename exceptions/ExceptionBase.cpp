#include "stdafx.h"
#include "ExceptionBase.h"
#include <sstream>

using namespace std;

CExceptionBase::CExceptionBase(const char* message, const char* file, const char* func, int line) throw()
	: std::exception()
	,m_sMessage(message)
	,m_szFile(file)
	,m_szFunc(func)
	,m_nLine(line)
{
}

CExceptionBase::CExceptionBase(const char* message, const char* file, const char* func) throw()
	: std::exception()
	,m_sMessage(message)
	,m_szFile(file)
	,m_szFunc(func)
	,m_nLine(-1)
{
}

CExceptionBase::CExceptionBase(const char* message, const char* file) throw()
	: std::exception()
	,m_sMessage(message)
	,m_szFile(file)
	,m_szFunc("<unknown func>")
	,m_nLine(-1)
{
}

CExceptionBase::CExceptionBase(const char* message) throw()
	: std::exception()
	,m_sMessage(message)
	,m_szFile("<unknown file>")
	,m_szFunc("<unknown func>")
	,m_nLine(-1)
{
}

std::string CExceptionBase::GetMessage() const
{
	return m_sMessage;
}

const char* CExceptionBase::what() const throw()
{
	return ToString().c_str();
}

const std::string& CExceptionBase::ToString() const
{
	if(m_sWhat.empty()){
		stringstream sstr;
		sstr << GetClassName() 
			<< ":: "<< m_szFile 
			<< "(" << m_nLine << ")"
			<< "-> " << m_szFunc 
			<< ": " << m_sMessage;

		m_sWhat = sstr.str();
	}
	return m_sWhat;
}

std::string CExceptionBase::GetClassName() const
{
	return "CExceptionBase";
}