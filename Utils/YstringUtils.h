// string utils
// author:liyajun

#pragma once
#include <string>

class CYstringUtils{

public:
	//Format a string to std::string which don't have a format function
    static std::string FormatToString(const char* lpszMsg, ...);
	static std::wstring FormatToString(const wchar_t* lpszMsg, ...);

	//Compare in case insensitive way
	static int CompareNoCase(const std::string& str1, const std::string str2);

	//Tranform to uppercase or lowercase
	static std::string& ToUpper(std::string& str);
};