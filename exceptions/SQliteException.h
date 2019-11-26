#pragma once
#include "ExceptionBase.h"

class CSQLiteException : public CExceptionBase{
public:
	CSQLiteException(const char* message, const char* file, const char* func, int line) throw();
	CSQLiteException(const char* message, const char* file, const char* func) throw();
	CSQLiteException(const char* message, const char* file) throw();
	CSQLiteException(const char* message) throw();
	virtual ~CSQLiteException();

public:
	virtual std::string GetClassName() const;

};