#pragma once
#include <string>
#include "..\Log\tstring.h"

class CYExceptionBase : public std::exception
{
public:
	CYExceptionBase(const char* message, const char* file, const char* func, int line) throw();
	CYExceptionBase(const char* message, const char* file, const char* func) throw();
	CYExceptionBase(const char* message, const char* file) throw();
	CYExceptionBase(const char* message) throw();
	virtual ~CYExceptionBase() {};

public:
	void Init(const char* file, const char* func, int line);

	virtual std::string GetClassName() const;
	std::string GetMessage() const;
	const char* what() const throw();			
	const std::string& ToString() const;

protected:
	std::string m_sMessage;
	const char* m_szFile;
	const char* m_szFunc;
	int m_nLine;

private:
	mutable std::string m_sWhat; 
};

