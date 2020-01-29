#pragma once
#include "ttype.h"
#include <exception>
#include <concrt.h>

class YWin32Exception : public std::exception
{
public:
	YWin32Exception(const char* file, const char* func, int line) throw();
	YWin32Exception(const char* file, const char* func) throw();
	YWin32Exception(const char* file) throw();
	YWin32Exception() throw();
	virtual ~YWin32Exception(){}

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
