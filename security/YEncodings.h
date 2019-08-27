#pragma once
#include <string>

class CYEncodings{
public:
	static std::string Base64_Encode(const std::string& sSrc);
	static std::string Base64_Decode(const std::string& sSrc);

	static void Base64_Encode(const std::string& sSrc, std::string& sDst);
	static void Base64_Decode(const std::string& sSrc, std::string& sDst);

	static void Base64_Encode(const unsigned char* pszSrc, unsigned int nCbLen, std::string& sDst);
	static void Base64_Decode(const unsigned char* pszSrc, unsigned int nLen, std::string& sDst);

private:
	CYEncodings(){}
	~CYEncodings(){}

	static inline bool is_base64(unsigned char c)
	{
		return (isalnum(c) || (c == '+' || c == '/'));
	}
};