#include "stdafx.h"
#include "YEncodings.h"

static const std::string base64_chars = 
	"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
	"abcdefghijklmnopqrstuvwxyz"
	"0123456789+/";

std::string CYEncodings::Base64_Encode(std::string sData)
{
	return Base64_Encode(reinterpret_cast<const unsigned char*>(sData.c_str()), sData.length());
}

std::string CYEncodings::Base64_Encode(const unsigned char* pszData, unsigned int nCbLen)
{
	std::string sRet;
	int i = 0, j = 0;
	unsigned char char_array_3[3], char_array_4[4];

	while(nCbLen--){
		char_array_3[i++] = *(const_cast<const unsigned char*>(pszData++));
		if(3 == i){
			char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
			char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
			char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);
			char_array_4[3] = char_array_3[2] & 0x3f;

			for(i = 0; i < 4; i++)
				sRet += base64_chars[char_array_4[i]];
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
			sRet += base64_chars[char_array_4[j]];

		while((i++ < 3))
			sRet += '=';
	}
	return sRet;
}

std::string CYEncodings::Base64_Decode(std::string const& sDecodedString)
{
	int nLen = sDecodedString.size();
	int i = 0, j = 0, in_ = 0;
	unsigned char char_array_4[4], char_array_3[3];
	std::string sRet;

	while (nLen-- && ( sDecodedString[in_] != '=') && is_base64(sDecodedString[in_])) 
	{
		char_array_4[i++] = sDecodedString[in_]; in_++;
		if (i ==4) {
			for (i = 0; i <4; i++)
				char_array_4[i] = base64_chars.find(char_array_4[i]);

			char_array_3[0] = (char_array_4[0] << 2) + ((char_array_4[1] & 0x30) >> 4);
			char_array_3[1] = ((char_array_4[1] & 0xf) << 4) + ((char_array_4[2] & 0x3c) >> 2);
			char_array_3[2] = ((char_array_4[2] & 0x3) << 6) + char_array_4[3];

			for (i = 0; (i < 3); i++)
				sRet += char_array_3[i];
			i = 0;
		}
	}

	if (i) 
	{
		for (j = i; j <4; j++)
			char_array_4[j] = 0;

		for (j = 0; j <4; j++)
			char_array_4[j] = base64_chars.find(char_array_4[j]);

		char_array_3[0] = (char_array_4[0] << 2) + ((char_array_4[1] & 0x30) >> 4);
		char_array_3[1] = ((char_array_4[1] & 0xf) << 4) + ((char_array_4[2] & 0x3c) >> 2);
		char_array_3[2] = ((char_array_4[2] & 0x3) << 6) + char_array_4[3];

		for (j = 0; (j < i - 1); j++) 
			sRet += char_array_3[j];
	}

	return sRet;
}