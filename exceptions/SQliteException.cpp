#include "stdafx.h"
#include "SQliteException.h"

CSQLiteException::CSQLiteException(const char* message, const char* file, const char* func, int line) throw()
	: CExceptionBase(message, file, func, line)
{
}

CSQLiteException::CSQLiteException(const char* message, const char* file, const char* func) throw()
	: CExceptionBase(message, file, func)
{
}

CSQLiteException::CSQLiteException(const char* message, const char* file) throw()
	: CExceptionBase(message, file)
{
}

CSQLiteException::CSQLiteException(const char* message) throw()
	: CExceptionBase(message)
{
}

CSQLiteException::~CSQLiteException()
{
}

std::string CSQLiteException::GetClassName() const
{
	return "CSQLiteException";
}