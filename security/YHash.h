#pragma once
#include <string>

class CYHash{
public:
	static std::string CalcMD5(const std::string& sIn, size_t nLen, bool isToUpperCase);
	static void CalcMD5(const std::string& sIn, size_t nLen, std::string& sOut, bool isToUpperCase);
	static void CalcMD5(const void* pIn, unsigned int nCbLen, char* pszOut, unsigned int nCbOutLen, bool isToUpperCase);

private:
	CYHash(){}
	~CYHash(){}
};