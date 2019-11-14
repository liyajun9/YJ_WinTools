#pragma once
#include <string>
#include <tchar.h>

#if defined(UNICODE) || defined(_UNICODE)

#define tstring std::wstring
#define tout std::wcout
#define tin std::wcin
#define tostream std::wostream
#define tofstream std::wofstream
#define tifstream std::wifstream
#define tfstream std::wfstream

#else

#define tstring std::string
#define tout std::cout
#define tin std::cin
#define tostream std::ostream
#define tofstream std::ofstream
#define tifstream std::ifstream
#define tfstream std::fstream

#endif

#define ASSERT_STRINGTYPE(T)  static_assert(std::is_same<T, std::string>::value||std::is_same<T, std::wstring>::value, "type must be string or wstring")