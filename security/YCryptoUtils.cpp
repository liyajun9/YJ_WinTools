#include "stdafx.h"
#include "YCryptoUtils.h"
#include <string.h>

int Padding(const void *pIn, unsigned int nCbLen, void *pOut, unsigned int nCbOutLen, unsigned int nCbBlockSize, int paddingScheme)
{
	if(nCbBlockSize == 0 || nCbBlockSize > 255) return 0;
	if(paddingScheme < padding_Zero || paddingScheme > padding_pkcs7) return 0;
	if(paddingScheme == padding_pkcs5 && nCbBlockSize != 8) return 0;

	memset(pOut, 0, nCbOutLen);
	memcpy(pOut, pIn, nCbLen);
	int r = nCbLen % nCbBlockSize;
	unsigned char* pRes = reinterpret_cast<unsigned char*>(pOut);
	unsigned char c = '\0';

	switch(paddingScheme){
	case padding_Zero:
		if(r == 0)	return nCbLen;
		else return (nCbLen + nCbBlockSize - r);

	case padding_X923:
		c = nCbBlockSize - r;
		pRes[nCbLen + nCbBlockSize - r - 1] = c;
		return (nCbLen + nCbBlockSize - r);

	case padding_pkcs5:
		c = 8 - r;
		for(int i = (8 - r); i > 0; i--){
			pRes[nCbLen + 8 - r - i] = c;
		}
		return (nCbLen + 8 - r);

	case padding_pkcs7:
		c = nCbBlockSize - r;
		for(int i = (nCbBlockSize - r); i > 0; i--){
			pRes[nCbLen + nCbBlockSize - r - i] = c;
		}
		return (nCbLen + nCbBlockSize - r);

	default:
		return 0;
	}
}

int RemovePadding(void *pData, unsigned int nCbLen, int paddingScheme)
{
	if(pData == NULL || nCbLen == 0 || paddingScheme < padding_Zero || paddingScheme > padding_pkcs7)
		return 0;

	unsigned int nRealLen(0);
	unsigned char *pszData = reinterpret_cast<unsigned char*>(pData);
	switch(paddingScheme){
	case padding_Zero:
		for(unsigned int i=nCbLen-1; i>=0; i--){
			if(pszData[i] != '\0'){
				nRealLen = i + 1;
			}
		}				
		break;
	case padding_X923:
	case padding_pkcs5:
	case padding_pkcs7:
		nRealLen = nCbLen - pszData[nCbLen - 1];
		break;
	}
	if(nRealLen > 0 && paddingScheme != padding_Zero){
		for(unsigned int i=nCbLen-1; i>=nRealLen; i--)
			pszData[i] = '\0';
	}

	return nRealLen;
}

std::string CharToHexString(const void *pSrc, unsigned int nLen, bool isToUpperCase)
{
	unsigned charA = isToUpperCase ? 'A' : 'a';
	std::string sHex;
	unsigned char ch;
	const unsigned char *srcptr = reinterpret_cast<const unsigned char*>(pSrc);
	while (nLen--)
	{
		ch = ((*srcptr & 0xF0) >> 4);
		if(ch <= 9) ch += '0';
		else ch += (charA- 10);
		sHex.append(1, ch);

		ch = (*srcptr++ & 0x0F);
		if(ch <= 9) ch += '0';
		else ch += (charA - 10);
		sHex.append(1, ch);
	}
	return sHex;
}

void HexStringToChar(std::string sSrc, bool isUpperCase, char *pDst, unsigned int nCbLen)
{
	char higher, lower;
	char charA = isUpperCase ? 'A' : 'a';
	unsigned int nSrcLen = static_cast<unsigned int>(sSrc.length());
	unsigned int nLen = nSrcLen < nCbLen ? nSrcLen : nCbLen;
	for(unsigned int i=0; i<nLen; i++){
		higher = sSrc[i*2] <= '9' ? sSrc[i*2] - '0' : sSrc[i*2] + 10 - charA;
		lower = sSrc[i*2 + 1] <= '9' ? sSrc[i*2+1] - '0' : sSrc[i*2 + 1] + 10 - charA;
		pDst[i] = (higher << 4) + lower;
	}
}