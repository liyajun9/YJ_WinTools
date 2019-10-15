#pragma once
#include <string>

class CYMD5{
public:
	static std::string Update(const std::string& sIn, size_t nLen, bool isToUpperCase);
	static void Update(const std::string& sIn, size_t nLen, std::string& sOut, bool isToUpperCase);
	static void Update(const void* pIn, unsigned int nCbLen, char* pszOut, unsigned int nCbOutLen, bool isToUpperCase);

private:
	CYMD5(){}
	~CYMD5(){}
};