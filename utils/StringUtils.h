#pragma once
#include <string>
#include <functional>
#include <algorithm>

namespace NS_Yutils{

//Format a string to std::string which don't have a format function
std::string formatToString(const char* lpszMsg, ...);
std::wstring formatToString(const wchar_t* lpszMsg, ...);

//Tranform to uppercase or lowercase
template<typename T>
inline T& toUpper(T& str){
	ASSERT_STRINGTYPE(T);
	std::transform(str.begin(), str.end(), str.begin(), ::toupper);
	return str;
}

//Compare in case insensitive way
template<typename T>
inline int compareNoCase(const T& str1, const T& str2){
	ASSERT_STRINGTYPE(T);
	ToUpper(const_cast<T&>(str1));
	return str1.compare(ToUpper(const_cast<T&>(str2)));
}

//trim
template<typename T>
inline void trimLeft(T& str){
	ASSERT_STRINGTYPE(T);
	str.erase(str.begin(), std::find_if(str.begin(), str.end(), std::not1(std::ptr_fun<int, int>(isspace))));
}

template<typename T>
inline void trimRight(T& str){
	ASSERT_STRINGTYPE(T);
	str.erase(std::find_if(str.rbegin(), str.rend(), std::not1(std::ptr_fun<int, int>(isspace))).base(), str.end());
}

template<typename T>
inline void trimBoth(T& str){
	ASSERT_STRINGTYPE(T);
	TrimLeft(str);
	TrimRight(str);
}

};