#pragma once
#include <concrt.h>
#include "..\Log\tstring.h"
#include <exception>

class CWSAException : public std::exception
{
public:
	CWSAException(const char* file, const char* func, int line) throw();
	CWSAException(const char* file, const char* func) throw();
	CWSAException(const char* file) throw();
	CWSAException() throw();
	virtual ~CWSAException(){}

public:
	DWORD GetErrorCode() const;
	std::string GetMessage() const;
	const char* GetClassName() const;
	const char* what() const throw();
	const std::string& ToString() const;

protected:
	DWORD m_dwErrorCode;
	std::string m_sMessage;
	const char* m_szFile;
	const char* m_szFunc;
	int m_nLine;

private:
	mutable std::string m_sWhat;
};
