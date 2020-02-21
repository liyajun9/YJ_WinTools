#pragma once
#include <string>

constexpr size_t MD5_BUFFER_SIZE = 33;

class YMD5{
public:
	static std::string Update(const std::string& sIn, bool toUpperCase = true);
	static std::string Update(const std::string& sIn, size_t nLen, bool toUpperCase = true);

	static void Update(const std::string& sIn, std::string& sOut, bool toUpperCase = true);
	static void Update(const std::string& sIn, size_t nLen, std::string& sOut, bool toUpperCase = true);

	/*
	Note: Nothing happends if nCbOutLen < MD5_BUFFER_SIZE
	*/
	static void Update(const void* pIn, unsigned int nCbLen, char* pszOut, unsigned int nCbOutLen, bool toUpperCase = true);

private:
	YMD5(){}
	~YMD5(){}
};