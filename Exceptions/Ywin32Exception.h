#pragma once
#include "..\Log\tstring.h"
#include <exception>
#include <concrt.h>

class CYWin32Exception : public std::exception
{
public:
	CYWin32Exception(const char* file, const char* func, int line) throw();
	CYWin32Exception(const char* file, const char* func) throw();
	CYWin32Exception(const char* file) throw();
	CYWin32Exception() throw();
	virtual ~CYWin32Exception(){}

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
