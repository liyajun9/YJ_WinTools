#include "stdafx.h"
#include "Exception.h"
#include <sstream>

YException::YException(const char* message, const char* file, const char* func, int line) throw()
	: std::exception()
	,m_sMessage(message)
	,m_sFile(file)
	,m_sFunc(func)
	,m_nLine(line)
{
}

YException::YException(const char* message, const char* file, const char* func) throw()
	: std::exception()
	,m_sMessage(message)
	,m_sFile(file)
	,m_sFunc(func)
	,m_nLine(-1)
{
}

YException::YException(const char* message, const char* file) throw()
	: std::exception()
	,m_sMessage(message)
	,m_sFile(file)
	,m_sFunc("<unknown func>")
	,m_nLine(-1)
{
}

YException::YException(const char* message) throw()
	: std::exception()
	,m_sMessage(message)
	,m_sFile("<unknown file>")
	,m_sFunc("<unknown func>")
	,m_nLine(-1)
{
}

std::string YException::GetMessage() const
{
	return m_sMessage;
}

const char* YException::what() const throw()
{
	return ToString().c_str();
}

const std::string& YException::ToString() const
{
	if(m_sWhat.empty()){
		std::stringstream sstr;
		sstr << GetClassName() 
			<< ":: "<< m_sFile 
			<< "(" << m_nLine << ")"
			<< "-> " << m_sFunc 
			<< ": " << m_sMessage;

		m_sWhat = sstr.str();
	}
	return m_sWhat;
}

std::string YException::GetClassName() const
{
	return "YException";
}