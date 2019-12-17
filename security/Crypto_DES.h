// Crypto_DES
// #not set parity for keys
// author:liyajun

#pragma once

#include <string>
#include <openssl/des.h>

#define DES_BLOCK_SIZE 8

enum des_block_mode{
	des_ECB = 0, //algorithm_ecb_encrypt
	des_CBC = 1, //algorithm_cbc_encrypt, does not update the IV 
	des_CBC_REAL = 2, //des_ncbc_enctryp, update the IV
	des_CFB = 3, //algorithm_cfb_encrypt
	des_OFB = 4, //algorithm_ofb_encrypt
	des_TRIPLE_ECB = 5, //algorithm_ecb3_encrypt
	des_TRIPLE_CBC = 6  //algorithm_ede3_cbc_encrypt
};

class YCrypto_DES{	
//ECB mode
public:
	/*DES(ECB mode)	 encrypt using key of MD5 of original key, and Base64 encode*/
	static bool DES64_ECB_Encrypt_MD5AsKey(const std::string& sKey, const unsigned char *pSrc, int nSrcLen, std::string& sEncrypted,  int paddingScheme);
	/*DES(ECB mode)	 encrypt and Base64 encode*/
	static bool DES64_ECB_Encrypt(const std::string& sKey, const unsigned char *pSrc, int nSrcLen, std::string& sEncrypted,  int paddingScheme);

	/*Base64 decode and DES(ECB mode)	decrypt using key of MD5 of original key*/
	static int DES64_ECB_Decrypt_MD5AsKey(const std::string& sKey, const std::string& sSrc,  std::string& sDecrypted, int paddingScheme);//输出为string和int，此函数是为了方便使用，不需要编程者自己创建输出buffer
	static int DES64_ECB_Decrypt_MD5AsKey(const std::string& sKey, const std::string& sSrc, unsigned char *pDecrypted, int nDecryptLen, int paddingScheme);
	/*Base64 decode and DES(ECB mode)	decrypt*/
	static int DES64_ECB_Decrypt(const std::string& sKey, const std::string& sSrc,  std::string& sDecrypted, int paddingScheme);//输出为string和int，此函数是为了方便使用，不需要编程者自己创建输出buffer
	static int DES64_ECB_Decrypt(const std::string& sKey, const std::string& sSrc, unsigned char *pDecrypted, int nDecryptLen, int paddingScheme);

public:
	/*DES encrypt(ECB mode)		
		parameters:
			pKey: DES key
			pSrc: source data
			nSrcLen: length of source data in bytes
			pEncrypted: buffer to receive encrypted data
			nEncryptLen: buffer length
			paddingCheme: padding scheme
		return: length of output binary
	*/
	static int DES_ECB_Encrypt(const_DES_cblock* pKey, const unsigned char *pSrc, int nSrcLen, unsigned char *pEncrypted, int nEncryptLen, int paddingScheme);

	/*DES decrypt(ECB mode)		
		parameters:
			pKey: DES key
			pSrc: source data
			nSrcLen: length of source data in bytes
			pDecrypted: buffer to receive decrypted data
			nDecryptLen: buffer length
			paddingCheme: padding scheme
		return: length of output binary
	*/
	static int DES_ECB_Decrypt(const_DES_cblock* pKey, const unsigned char *pSrc, int nSrcLen, unsigned char *pDecrypted, int nDecryptLen, int paddingScheme);

//CBC mode
public:
	/*DES(CBCmode)	 encrypt using key of MD5 of original key, and Base64 encode*/
	static bool DES64_CBC_Encrypt_MD5AsKey(const std::string& sKey, const std::string& sIv,const unsigned char *pSrc, int nSrcLen, std::string& sEncrypted,  int paddingScheme);
	/*DES(CBC mode)	 encrypt and Base64 encode*/
	static bool DES64_CBC_Encrypt(const std::string& sKey, const std::string& sIv,const unsigned char *pSrc, int nSrcLen, std::string& sEncrypted,  int paddingScheme);

	/*Base64 decode and DES(ECB mode)	decrypt using key of MD5 of original key*/
	static int DES64_CBC_Decrypt_MD5AsKey(const std::string& sKey, const std::string& sIv, const std::string& sSrc, std::string& sDecrypted, int paddingScheme);
	static int DES64_CBC_Decrypt_MD5AsKey(const std::string& sKey, const std::string& sIv, const std::string& sSrc, unsigned char *pDecrypted, int nDecryptLen, int paddingScheme);

	/*Base64 decode and DES(ECB mode)	decrypt*/
	static int DES64_CBC_Decrypt(const std::string& sKey, const std::string& sIv, const std::string& sSrc, std::string& sDecrypted, int paddingScheme); 
	static int DES64_CBC_Decrypt(const std::string& sKey, const std::string& sIv, const std::string& sSrc, unsigned char *pDecrypted, int nDecryptLen, int paddingScheme); 

	/*DES encrypt(CBC mode)		
		parameters:
			pKey: DES key
			pIv: initial vector
			pSrc: source data
			nSrcLen: length of source data in bytes
			pEncrypted: buffer to receive encrypted data
			nEncryptLen: buffer length
			paddingCheme: padding scheme
		return: length of output binary
	*/
	static int DES_CBC_Encrypt(DES_cblock* pKey, DES_cblock* pIv, const unsigned char *pSrc, int nSrcLen, unsigned char *pEncrypted, int nEncryptLen, int paddingScheme);
	/*DES decrypt(CBC mode)		
		parameters:
			pKey: DES key
			pIv: initial vector
			pSrc: source data
			nSrcLen: length of source data in bytes
			pDecrypted: buffer to receive decrypted data
			nDecryptLen: buffer length
			paddingCheme: padding scheme
		return: length of output binary
	*/
	static int DES_CBC_Decrypt(const_DES_cblock* pKey, DES_cblock* pIv, const unsigned char *pSrc, int nSrcLen, unsigned char *pDecrypted, int nDecryptLen, int paddingScheme);

//Assist methods
public:
	/*Transform a character array to a hexadecimal style string. e.g. "12JK12JK" -> "31324A4B31324A4B"
	Params:
		pSrc: source character array
		nLen: length of character array, ending '\0' is not included
		isToUpperCase:  indicate case of returned hexadecimal style string
	Return: hexadecimal style string
	*/
	static std::string DESKeyToHexString(const_DES_cblock* pKey, bool isToUpperCase);

	/*Reverse transform of DESKeyToHexString.
	Params: 
		sSrc: hexadecimal style string. If has invalid character(not in '0~9' 'A'~'F'), corresponding transformed byte will be set to '\0'
		isUppderCase: case of hexadecimal style string
		pKey: output buffer. a DES_cblock. If length of sSrc > 8, the result will be truncated.
	*/
	static bool HexStringToDESKey(const std::string& sSrc, bool isUpperCase, DES_cblock* pKey);

	/*Store a DES_cblock into a string
	*/
	static std::string DESKeyToString(const_DES_cblock* pKey);

public:
	/* Calc MD5 HASH of input Key, then Extract first 8 bytes(DES block size) as output key. And set parity to odd.
		Params:
			sKey: original key
			pKey: output key
	*/
	static void GetMD5AsKey(const std::string& sKey, DES_cblock* pKey);//calc MD5 of key, and set parity to odd

private:
	YCrypto_DES(){}
	~YCrypto_DES(){}
};