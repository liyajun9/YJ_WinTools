#include "stdafx.h"
#include "YEncodings.h"

static const std::string base64_chars = 
	"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
	"abcdefghijklmnopqrstuvwxyz"
	"0123456789+/";

std::string CYEncodings::Base64_Encode(const std::string& sSrc)
{
	std::string sRes;
	Base64_Encode(reinterpret_cast<const unsigned char*>(sSrc.c_str()), 
						static_cast<unsigned int>(sSrc.length()), 
						sRes);
	return sRes;
}

std::string CYEncodings::Base64_Decode(const std::string& sSrc)
{
	std::string sRes;
	Base64_Decode(reinterpret_cast<const unsigned char*>(sSrc.c_str()), 
						static_cast<unsigned int>(sSrc.length()), 
						sRes);
	return sRes;
}

void CYEncodings::Base64_Encode(const std::string& sSrc, std::string& sDst)
{
	Base64_Encode(reinterpret_cast<const unsigned char*>(sSrc.c_str()), 
				static_cast<unsigned int>(sSrc.length()), 
				sDst);
}

void CYEncodings::Base64_Decode(const std::string& sSrc, std::string& sDst)
{
	Base64_Decode(reinterpret_cast<const unsigned char*>(sSrc.c_str()), 
				static_cast<unsigned int>(sSrc.length()), 
				sDst);
}

void CYEncodings::Base64_Encode(const unsigned char* pszSrc, unsigned int nCbLen, std::string& sDst)
{
	sDst.empty();
	int i = 0, j = 0;
	unsigned char char_array_3[3], char_array_4[4];

	while(nCbLen--){
		char_array_3[i++] = *(const_cast<const unsigned char*>(pszSrc++));
		if(3 == i){
			char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
			char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
			char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);
			char_array_4[3] = char_array_3[2] & 0x3f;

			for(i = 0; i < 4; i++)
				sDst += base64_chars[char_array_4[i]];
			i = 0;
		}		
	}

	if (i)
	{
		for(j = i; j < 3; j++)
			char_array_3[j] = '\0';

		char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
		char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
		char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);
		char_array_4[3] = char_array_3[2] & 0x3f;

		for (j = 0; (j < i + 1); j++)
			sDst += base64_chars[char_array_4[j]];

		while((i++ < 3))
			sDst += '=';
	}
}

void CYEncodings::Base64_Decode(const unsigned char* pszSrc, unsigned int nLen, std::string& sDst)
{
	sDst.empty();
	int i = 0, j = 0, in_ = 0;
	unsigned char char_array_4[4], char_array_3[3];

	while (nLen-- && ( pszSrc[in_] != '=') && is_base64(pszSrc[in_])) 
	{
		char_array_4[i++] = pszSrc[in_]; in_++;
		if (i ==4) {
			for (i = 0; i <4; i++)
				char_array_4[i] = static_cast<unsigned char>(base64_chars.find(char_array_4[i]));

			char_array_3[0] = (char_array_4[0] << 2) + ((char_array_4[1] & 0x30) >> 4);
			char_array_3[1] = ((char_array_4[1] & 0xf) << 4) + ((char_array_4[2] & 0x3c) >> 2);
			char_array_3[2] = ((char_array_4[2] & 0x3) << 6) + char_array_4[3];

			for (i = 0; (i < 3); i++)
				sDst += char_array_3[i];
			i = 0;
		}
	}

	if (i) 
	{
		for (j = i; j <4; j++)
			char_array_4[j] = 0;

		for (j = 0; j <4; j++)
			char_array_4[j] = static_cast<unsigned char>(base64_chars.find(char_array_4[j]));

		char_array_3[0] = (char_array_4[0] << 2) + ((char_array_4[1] & 0x30) >> 4);
		char_array_3[1] = ((char_array_4[1] & 0xf) << 4) + ((char_array_4[2] & 0x3c) >> 2);
		char_array_3[2] = ((char_array_4[2] & 0x3) << 6) + char_array_4[3];

		for (j = 0; (j < i - 1); j++) 
			sDst += char_array_3[j];
	}
}