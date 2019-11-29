#pragma once
#include <string>
#include "..\Log\tstring.h"

class CExceptionBase : public std::exception
{
public:
	CExceptionBase(const char* message, const char* file, const char* func, int line) throw();
	CExceptionBase(const char* message, const char* file, const char* func) throw();
	CExceptionBase(const char* message, const char* file) throw();
	CExceptionBase(const char* message) throw();
	virtual ~CExceptionBase() {};

public:
	void Init(const char* file, const char* func, int line);

	virtual std::string GetClassName() const;
	std::string GetMessage() const;
	const char* what() const throw();			
	const std::string& ToString() const;

protected:
	std::string m_sMessage;
	std::string m_sFile;
	std::string m_sFunc;
	int m_nLine;

private:
	mutable std::string m_sWhat; 
};

