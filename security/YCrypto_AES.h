#pragma once
#include <string>
#include <openssl/aes.h>
#include "YCryptoUtils.h"

#pragma warning(disable:4482)
typedef unsigned char AES_cblock[16];

class CYCrypto_AES{
	//CBC modd
public:
/*AES(CBC mode)	 encrypt and Base64 encode*/
static bool AES64_CBC_Encrypt(const std::string& sKey, const std::string& sIv,  const unsigned char* pSrc, int nSrcLen, std::string& sEncrypted, int paddingScheme= padding_scheme::padding_pkcs7, int nKeyBits = 128);
/*Base64 decode and AES(CBC mode)	decrypt*/
static int AES64_CBC_Decrypt(const std::string& sKey, const std::string& sIv,  const std::string sSrc, unsigned char *pDecrypted, int nDecryptLen, int paddingScheme= padding_scheme::padding_pkcs7, int nKeyBits = 128);
static int AES64_CBC_Decrypt(const std::string& sKey, const std::string& sIv,  const std::string sSrc, std::string& sDecrypted, int paddingScheme= padding_scheme::padding_pkcs7, int nKeyBits = 128);//输出为string和int，此函数是为了方便使用，不需要编程者自己创建输出buffer

public:
	/*AES encrypt(CBC mode)
		parameters:
			sKey: AES key
			nKeyBits: 128/192/256
			sIv: initial vector
			pSrc: source data
			nSrcLen: length of source data in bytes
			pEncrypted: buffer to receive encrypted data
			nEncryptLen: buffer length
			paddingCheme: padding scheme
		return: length of output data
	*/
	static int AES_CBC_Encrypt(const std::string& sKey, const std::string& sIv, const unsigned char* pSrc, int nSrcLen, unsigned char *pEncrypted, int nEncryptLen, int paddingScheme= padding_scheme::padding_pkcs7, int nKeyBits = 128);

		/*AES decrypt(CBC mode)
		parameters:
			sKey: AES key
			nKeyBits: 128/192/256
			sIv: initial vector
			pSrc: source data
			nSrcLen: length of source data in bytes
			pDecrypted: buffer to receive decrypted data
			nDecryptLen: buffer length
			paddingCheme: padding scheme
		return: length of output data
	*/
	static int AES_CBC_Decrypt(const std::string& sKey, const std::string& sIv, const unsigned char* pSrc, int nSrcLen, unsigned char *pDecrypted, int nDecryptLen, int paddingScheme= padding_scheme::padding_pkcs7, int nKeyBits = 128);

public:
/*Transform a character array to a hexadecimal style string. e.g. "12JK12JK" -> "31324A4B31324A4B"
	Params:
		pSrc: source character array
		nLen: length of character array, ending '\0' is not included
		isToUpperCase:  indicate case of returned hexadecimal style string
	Return: hexadecimal style string
	*/
	static std::string AESKeyToHexString(const AES_KEY* pKey, bool isToUpperCase);

	/*Reverse transform of DESKeyToHexString.
	Params: 
		sSrc: hexadecimal style string. If has invalid character(not in '0~9' 'A'~'F'), corresponding transformed byte will be set to '\0'
		isUppderCase: case of hexadecimal style string
		pKey: output buffer. a DES_cblock. If length of sSrc > 8, the result will be truncated.
	*/
	static bool HexStringToAESKey(const std::string& sSrc, bool isUpperCase, AES_KEY* pKey);

	/*Store a DES_cblock into a string
	*/
	static std::string AESKeyToString(const AES_KEY* pKey);

private:
	CYCrypto_AES() {}
	~CYCrypto_AES() {}
};