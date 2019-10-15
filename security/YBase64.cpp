#include "stdafx.h"
#include "YBase64.h"

static const std::string base64_chars = 
	"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
	"abcdefghijklmnopqrstuvwxyz"
	"0123456789+/";

std::string CYBase64::Encode(const unsigned char *pSrc, int nSrcLen)
{
	std::string sEncoded;
	Encode(pSrc, nSrcLen, sEncoded);
	return sEncoded;
}

void CYBase64::Encode(const std::string sSrc, int nSrcLen, std::string& sEncoded)
{
	unsigned char *pSrc = new unsigned char[nSrcLen]; memset(pSrc, 0, nSrcLen);
	memcpy(pSrc, sSrc.data(), nSrcLen);
	Encode(pSrc, nSrcLen, sEncoded);
}

 void CYBase64::Encode(const unsigned char *pSrc, int nSrcLen, std::string& sEncoded)
 {
	 sEncoded.empty();
	 int i = 0, j = 0;
	 unsigned char char_array_3[3], char_array_4[4];

	 while(nSrcLen--){
		 char_array_3[i++] = *(const_cast<const unsigned char*>(pSrc++));
		 if(3 == i){
			 char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
			 char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
			 char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);
			 char_array_4[3] = char_array_3[2] & 0x3f;

			 for(i = 0; i < 4; i++)
				 sEncoded += base64_chars[char_array_4[i]];
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
			 sEncoded += base64_chars[char_array_4[j]];

		 while((i++ < 3))
			 sEncoded += '=';
	 }
 }

 int CYBase64::Decode(const std::string& sSrc, unsigned char* pDecoded, int nDecodedLen)
 {
	 int nLen = sSrc.length();
	 int i = 0, j = 0, in_ = 0, out_ = 0;
	 unsigned char char_array_4[4], char_array_3[3];

	 while (nLen-- && ( sSrc[in_] != '=') && is_base64(sSrc[in_])) 
	 {
		 char_array_4[i++] = sSrc[in_]; in_++;
		 if (i ==4) {
			 for (i = 0; i <4; i++)
				 char_array_4[i] = static_cast<unsigned char>(base64_chars.find(char_array_4[i]));

			 char_array_3[0] = (char_array_4[0] << 2) + ((char_array_4[1] & 0x30) >> 4);
			 char_array_3[1] = ((char_array_4[1] & 0xf) << 4) + ((char_array_4[2] & 0x3c) >> 2);
			 char_array_3[2] = ((char_array_4[2] & 0x3) << 6) + char_array_4[3];

			 for (i = 0; (i < 3); i++){
				 if(out_ <= nDecodedLen)
					 pDecoded[out_++] = char_array_3[i];
				 else
					 return 0;
			 }
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

		 for (j = 0; (j < i - 1); j++){
			 if(out_ <= nDecodedLen)
				 pDecoded[out_++] = char_array_3[j];
			 else 
				 return 0;
		 }
	 }
	 return out_;
 }