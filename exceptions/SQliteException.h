#pragma once
#include "Exception.h"

class YSQLiteException : public YException{
public:
	YSQLiteException(const char* message, const char* file, const char* func, int line) throw();
	YSQLiteException(const char* message, const char* file, const char* func) throw();
	YSQLiteException(const char* message, const char* file) throw();
	YSQLiteException(const char* message) throw();
	virtual ~YSQLiteException();

public:
	virtual std::string GetClassName() const;

};