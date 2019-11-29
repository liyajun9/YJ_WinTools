#include "stdafx.h"
#include "ExceptionBase.h"
#include <sstream>

using namespace std;

CExceptionBase::CExceptionBase(const char* message, const char* file, const char* func, int line) throw()
	: std::exception()
	,m_sMessage(message)
	,m_sFile(file)
	,m_sFunc(func)
	,m_nLine(line)
{
}

CExceptionBase::CExceptionBase(const char* message, const char* file, const char* func) throw()
	: std::exception()
	,m_sMessage(message)
	,m_sFile(file)
	,m_sFunc(func)
	,m_nLine(-1)
{
}

CExceptionBase::CExceptionBase(const char* message, const char* file) throw()
	: std::exception()
	,m_sMessage(message)
	,m_sFile(file)
	,m_sFunc("<unknown func>")
	,m_nLine(-1)
{
}

CExceptionBase::CExceptionBase(const char* message) throw()
	: std::exception()
	,m_sMessage(message)
	,m_sFile("<unknown file>")
	,m_sFunc("<unknown func>")
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
			<< ":: "<< m_sFile 
			<< "(" << m_nLine << ")"
			<< "-> " << m_sFunc 
			<< ": " << m_sMessage;

		m_sWhat = sstr.str();
	}
	return m_sWhat;
}

std::string CExceptionBase::GetClassName() const
{
	return "CExceptionBase";
}