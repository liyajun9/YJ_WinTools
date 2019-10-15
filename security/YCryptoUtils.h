#pragma once
#include <string.h>

#define MAX_BLOCK_SIZE 255

enum padding_scheme{
	padding_Zero = 0,
	padding_X923 = 1,
	padding_pkcs5 = 2,
	padding_pkcs7 = 3
};

/*Padding plainText
	Params:
		pIn: plainText
		nCbLen: number of bytes of plainText, ending '\0' is not included.
		pOut: output buffer
		nCbOutLen: number of bytes of output buffer.  suggest length >= (1 + nCbLen / nCbBlockSize) * nCbBlockSize
		nCbBlockSize: cipher block size
		paddingScheme: padding scheme. refer to enum type of padding_scheme.
	Return: length of output.  return 0 in case any error.
*/
int Padding(const void *pIn, unsigned int nCbLen, void *pOut, unsigned int nCbOutLen, unsigned int nCbBlockSize, int paddingScheme);

/*Remove padding from cipherText
	Params:
		pData: input cipherText and output removed padding result.
		nCbLen: number of bytes of cipherText, ending '\0' is not included.
		paddingScheme: padding scheme. refer to enum type of padding_scheme.
	Return: length of output. return 0 in case any error.
*/
int RemovePadding(void *pData, unsigned int nCbLen, int paddingScheme);

/*Transform a character array to a hexadecimal style string. e.g. "12JK" -> "31324A4B"
	Params:
		pSrc: source character array
		nLen: length of character array, ending '\0' is not included
		isToUpperCase:  indicate case of returned hexadecimal style string
	Return: hexadecimal style string
*/
std::string CharToHexString(const void *pSrc, unsigned int nLen, bool isToUpperCase);

/*Transform a hexadecimal style string back to a character array. e.g. "31324A4B" -> "12JK"
	Params: 
		sSrc: hexadecimal style string. If has invalid character(not in '0~9' 'A'~'F'), corresponding transformed byte will be set to '\0'
		isUppderCase: case of hexadecimal style string
		pDst: output buffer. a character array. 
		nCbLen: length of output buffer. If output buffer is less than required length, the result will be truncated.
*/
void HexStringToChar(std::string sSrc, bool isUpperCase, char *pDst, unsigned int nCbLen);