// string utils
// author:liyajun

#pragma once
#include <string>

class NS_Yutils{

//Format a string to std::string which don't have a format function
std::string FormatToString(const char* lpszMsg, ...);
std::wstring FormatToString(const wchar_t* lpszMsg, ...);

//Compare in case insensitive way
int CompareNoCase(const std::string& str1, const std::string str2);

//Tranform to uppercase or lowercase
std::string& ToUpper(std::string& str);
};