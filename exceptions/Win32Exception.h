#pragma once
#include "..\Log\tstring.h"
#include <exception>
#include <concrt.h>

class CWin32Exception : public std::exception
{
public:
	CWin32Exception(const char* file, const char* func, int line) throw();
	CWin32Exception(const char* file, const char* func) throw();
	CWin32Exception(const char* file) throw();
	CWin32Exception() throw();
	virtual ~CWin32Exception(){}

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
