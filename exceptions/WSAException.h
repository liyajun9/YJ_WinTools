#pragma once
#include <concrt.h>
#include "ttype.h"
#include <exception>

class YWSAException : public std::exception
{
public:
	YWSAException(const char* file, const char* func, int line) throw();
	YWSAException(const char* file, const char* func) throw();
	YWSAException(const char* file) throw();
	YWSAException() throw();
	virtual ~YWSAException(){}

public:
	DWORD GetErrorCode() const;
	std::string GetMessage() const;
	const char* GetClassName() const;
	const char* what() const throw();
	const std::string& ToString() const;

protected:
	DWORD m_dwErrorCode;
	std::string m_sMessage;
	std::string m_sFile;
	std::string m_sFunc;
	int m_nLine;

private:
	mutable std::string m_sWhat;
};
