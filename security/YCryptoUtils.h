#pragma once
#include <string.h>

enum padding_scheme{
	padding_Zero = 0,
	padding_X923 = 1,
	padding_pkcs5 = 2,
	padding_pkcs7 = 3
};

int Padding(const void *pIn, unsigned int nCbLen, void *pOut, unsigned int nCbOutLen, unsigned int nCbBlockSize, int paddingScheme);
int RemovePadding(void *pData, unsigned int nCbLen, int paddingScheme);
std::string CharToHexString(const void *pSrc, unsigned int nLen, bool isToUpperCase);
void HexStringToChar(std::string sSrc, bool isUpperCase, char *pDst, unsigned int nCbLen);