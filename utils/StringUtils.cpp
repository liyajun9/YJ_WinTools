#include "stdafx.h"
#include "StringUtils.h"
#include <algorithm>
#include <stdarg.h>
#pragma warning(disable:4996)

std::string NS_Yutils::FormatToString(const char* lpszMsg, ...)
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

std::wstring NS_Yutils::FormatToString(const wchar_t* lpszMsg, ...)
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

