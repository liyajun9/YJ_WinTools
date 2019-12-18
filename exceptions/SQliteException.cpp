#include "stdafx.h"
#include "SQliteException.h"

YSQLiteException::YSQLiteException(const char* message, const char* file, const char* func, int line) throw()
	: YException(message, file, func, line)
{
}

YSQLiteException::YSQLiteException(const char* message, const char* file, const char* func) throw()
	: YException(message, file, func)
{
}

YSQLiteException::YSQLiteException(const char* message, const char* file) throw()
	: YException(message, file)
{
}

YSQLiteException::YSQLiteException(const char* message) throw()
	: YException(message)
{
}

YSQLiteException::~YSQLiteException()
{
}

std::string YSQLiteException::GetClassName() const
{
	return "YSQLiteException";
}