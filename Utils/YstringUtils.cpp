#include "stdafx.h"
#include "YstringUtils.h"
#include <algorithm>
#include <stdarg.h>

std::string CYStringUtils::FormatToString(const char* lpszMsg, ...)
{
    std::string sRes;
    va_list argList;
    va_start(argList, lpszMsg);
    size_t nSize = _vscprintf(lpszMsg, argList);
    if(sRes.capacity() < (nSize + 1))
        sRes.resize(nSize + 1);

    vsprintf((char*)sRes.data(), lpszMsg, argList);
    va_end(argList);

    return sRes;
}

std::wstring CYStringUtils::FormatToString(const wchar_t* lpszMsg, ...)
{
	std::wstring sRes;
	va_list argList;
	va_start(argList, lpszMsg);
	size_t nSize = _vscwprintf(lpszMsg, argList);
	if(sRes.capacity() < (nSize + 1))
		sRes.resize(nSize + 1);

	vswprintf((wchar_t*)sRes.data(), lpszMsg, argList);
	va_end(argList);

	return sRes;
}

int CYStringUtils::CompareNoCase(const std::string& str1, const std::string str2)
{
	ToUpper(const_cast<std::string&>(str1));
	return str1.compare(ToUpper(const_cast<std::string&>(str2)));
}

std::string& CYStringUtils::ToUpper(std::string& str)
{
	std::transform(str.begin(), str.end(), str.begin(), ::toupper);
	return str;
}

