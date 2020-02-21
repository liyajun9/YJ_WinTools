#pragma once
#include <string>
#include <openssl/aes.h>
#include "CipherUtils.h"

typedef unsigned char AES_cblock[16];

class YAes{
public: //with base64
	/*return : true on success, false on failure*/
	static bool AES64_CBC_Encrypt(const std::string& sKey, const std::string& sIv,  const std::string& sSrc, std::string& sEncrypted, int paddingScheme= padding_scheme::padding_pkcs7, int nKeyBits = 128);
	static bool AES64_CBC_Encrypt(const std::string& sKey, const std::string& sIv,  const char* pSrc, int nSrcLen, std::string& sEncrypted, int paddingScheme= padding_scheme::padding_pkcs7, int nKeyBits = 128);
	static bool AES64_CBC_Encrypt(const std::string& sKey, const std::string& sIv,  const unsigned char* pSrc, int nSrcLen, std::string& sEncrypted, int paddingScheme= padding_scheme::padding_pkcs7, int nKeyBits = 128);
	/*return: size of decrypted data on success,  0 on failure*/
	static int AES64_CBC_Decrypt(const std::string& sKey, const std::string& sIv,  const char* pSrc, int nSrcLen,unsigned char *pDecrypted, int nDecryptLen, int paddingScheme= padding_scheme::padding_pkcs7, int nKeyBits = 128);
	static int AES64_CBC_Decrypt(const std::string& sKey, const std::string& sIv,  const unsigned char* pSrc, int nSrcLen,unsigned char *pDecrypted, int nDecryptLen, int paddingScheme= padding_scheme::padding_pkcs7, int nKeyBits = 128);
	static int AES64_CBC_Decrypt(const std::string& sKey, const std::string& sIv,  const std::string sSrc, unsigned char *pDecrypted, int nDecryptLen, int paddingScheme= padding_scheme::padding_pkcs7, int nKeyBits = 128);
	static int AES64_CBC_Decrypt(const std::string& sKey, const std::string& sIv,  const char* pSrc, int  nSrcLen,std::string& sDecrypted, int paddingScheme= padding_scheme::padding_pkcs7, int nKeyBits = 128);
	static int AES64_CBC_Decrypt(const std::string& sKey, const std::string& sIv,  const unsigned char* pSrc, int  nSrcLen,std::string& sDecrypted, int paddingScheme= padding_scheme::padding_pkcs7, int nKeyBits = 128);
	static int AES64_CBC_Decrypt(const std::string& sKey, const std::string& sIv,  const std::string sSrc, std::string& sDecrypted, int paddingScheme= padding_scheme::padding_pkcs7, int nKeyBits = 128);

public:
	/*return: size of encrypted data on success,  0 on failure*/
	static int AES_CBC_Encrypt(const std::string& sKey, const std::string& sIv, const std::string& sSrc, unsigned char *pEncrypted, int nEncryptLen, int paddingScheme= padding_scheme::padding_pkcs7, int nKeyBits = 128);
	static int AES_CBC_Encrypt(const std::string& sKey, const std::string& sIv, const char* pSrc, int nSrcLen, unsigned char *pEncrypted, int nEncryptLen, int paddingScheme= padding_scheme::padding_pkcs7, int nKeyBits = 128);
	static int AES_CBC_Encrypt(const std::string& sKey, const std::string& sIv, const unsigned char* pSrc, int nSrcLen, unsigned char *pEncrypted, int nEncryptLen, int paddingScheme= padding_scheme::padding_pkcs7, int nKeyBits = 128);
	/*return: size of decrypted data on success,  0 on failure*/
	static int AES_CBC_Decrypt(const std::string& sKey, const std::string& sIv, const std::string& sSrc, unsigned char *pDecrypted, int nDecryptLen, int paddingScheme= padding_scheme::padding_pkcs7, int nKeyBits = 128);
	static int AES_CBC_Decrypt(const std::string& sKey, const std::string& sIv, const char* pSrc, int nSrcLen, unsigned char *pDecrypted, int nDecryptLen, int paddingScheme= padding_scheme::padding_pkcs7, int nKeyBits = 128);
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
	YAes() {}
	~YAes() {}
};