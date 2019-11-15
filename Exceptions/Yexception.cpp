#include "stdafx.h"
#include "Yexception.h"
#include <sstream>

using namespace std;

CYExceptionBase::CYExceptionBase(const char* message, const char* file, const char* func, int line) throw()
	: std::exception()
	,m_sMessage(message)
	,m_szFile(file)
	,m_szFunc(func)
	,m_nLine(line)
{
}

CYExceptionBase::CYExceptionBase(const char* message, const char* file, const char* func) throw()
	: std::exception()
	,m_sMessage(message)
	,m_szFile(file)
	,m_szFunc(func)
	,m_nLine(-1)
{
}

CYExceptionBase::CYExceptionBase(const char* message, const char* file) throw()
	: std::exception()
	,m_sMessage(message)
	,m_szFile(file)
	,m_szFunc("<unknown func>")
	,m_nLine(-1)
{
}

CYExceptionBase::CYExceptionBase(const char* message) throw()
	: std::exception()
	,m_sMessage(message)
	,m_szFile("<unknown file>")
	,m_szFunc("<unknown func>")
	,m_nLine(-1)
{
}

std::string CYExceptionBase::GetMessage() const
{
	return m_sMessage;
}

const char* CYExceptionBase::what() const throw()
{
	return ToString().c_str();
}

const std::string& CYExceptionBase::ToString() const
{
	if(m_sWhat.empty()){
		stringstream sstr;
		sstr << GetClassName() << "-> ";
		if(m_nLine > 0){
			sstr << m_szFile << "(" << m_nLine << ")";
		}
		sstr << ": " << m_szFunc << ": " << m_sMessage;

		m_sWhat = sstr.str();
	}
	return m_sWhat;
}

std::string CYExceptionBase::GetClassName() const
{
	return "CYExceptionBase";
}