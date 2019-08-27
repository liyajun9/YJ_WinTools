#pragma once
#include <string>

class CYEncodings{
public:
	static std::string Base64_Encode(std::string sData);
	static std::string Base64_Encode(const unsigned char* pszData, unsigned int nCbLen);
	static std::string Base64_Decode(std::string const& sDecodedString);

private:
	CYEncodings(){}
	~CYEncodings(){}

	static inline bool is_base64(unsigned char c)
	{
		return (isalnum(c) || (c == '+' || c == '/'));
	}
};