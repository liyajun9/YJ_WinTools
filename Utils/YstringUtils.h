// string utils
// author:liyajun

#pragma once
#include <string>

class CYstringUtils{

public:
	//Format a string to std::string which don't have a format function
    static std::string FormatToString(const char* lpszMsg, ...);
	static std::wstring FormatToString(const wchar_t* lpszMsg, ...);
};