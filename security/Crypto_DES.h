// Crypto_DES
// #not set parity for keys
// author:liyajun

#pragma once

#include <string>
#include <openssl/des.h>

#define DES_BLOCK_SIZE 8

enum des_block_mode{
	des_ECB = 0,				//algorithm_ecb_encrypt
	des_CBC = 1,				//algorithm_cbc_encrypt, does not update the IV 
	des_CBC_REAL = 2,	//des_ncbc_enctryp, update the IV
	des_CFB = 3,				//algorithm_cfb_encrypt
	des_OFB = 4,				//algorithm_ofb_encrypt
	des_TRIPLE_ECB = 5, //algorithm_ecb3_encrypt
	des_TRIPLE_CBC = 6  //algorithm_ede3_cbc_encrypt
};

class YCrypto_DES{	
public:	//actual key=MD5(key)
	static bool DES64_ECB_Encrypt_KeyMD5(const std::string& sKey, const unsigned char *pSrc, int nSrcLen, std::string& sEncrypted,  int paddingScheme = padding_pkcs5);
	static bool DES64_CBC_Encrypt_KeyMD5(const std::string& sKey, const std::string& sIv,const unsigned char *pSrc, int nSrcLen, std::string& sEncrypted,  int paddingScheme = padding_pkcs5);

	static int DES64_ECB_Decrypt_KeyMD5(const std::string& sKey, const std::string& sSrc,  std::string& sDecrypted, int paddingScheme = padding_pkcs5);
	static int DES64_ECB_Decrypt_KeyMD5(const std::string& sKey, const std::string& sSrc, unsigned char *pDecrypted, int nDecryptLen, int paddingScheme = padding_pkcs5);
	static int DES64_CBC_Decrypt_KeyMD5(const std::string& sKey, const std::string& sIv, const std::string& sSrc, std::string& sDecrypted, int paddingScheme = padding_pkcs5);
	static int DES64_CBC_Decrypt_KeyMD5(const std::string& sKey, const std::string& sIv, const std::string& sSrc, unsigned char *pDecrypted, int nDecryptLen, int paddingScheme = padding_pkcs5);

public: //with base64
	static bool DES64_ECB_Encrypt(const std::string& sKey, const std::string& sSrc, std::string& sEncrypted,  int paddingScheme = padding_pkcs5);
	static bool DES64_ECB_Encrypt(const std::string& sKey, const char *pSrc, int nSrcLen, std::string& sEncrypted,  int paddingScheme = padding_pkcs5);
	static bool DES64_ECB_Encrypt(const std::string& sKey, const unsigned char *pSrc, int nSrcLen, std::string& sEncrypted,  int paddingScheme = padding_pkcs5);

	static bool DES64_CBC_Encrypt(const std::string& sKey, const std::string& sIv, const std::string& sSrc, std::string& sEncrypted,  int paddingScheme = padding_pkcs5);
	static bool DES64_CBC_Encrypt(const std::string& sKey, const std::string& sIv, const char *pSrc, int nSrcLen, std::string& sEncrypted,  int paddingScheme = padding_pkcs5);
	static bool DES64_CBC_Encrypt(const std::string& sKey, const std::string& sIv, const unsigned char *pSrc, int nSrcLen, std::string& sEncrypted,  int paddingScheme = padding_pkcs5);

	static int DES64_ECB_Decrypt(const std::string& sKey, const std::string& sSrc,  std::string& sDecrypted, int paddingScheme = padding_pkcs5);
	static int DES64_ECB_Decrypt(const std::string& sKey, const char* pSrc, int nSrcLen,  std::string& sDecrypted, int paddingScheme = padding_pkcs5);
	static int DES64_ECB_Decrypt(const std::string& sKey, const unsigned char* pSrc, int nSrcLen,  std::string& sDecrypted, int paddingScheme = padding_pkcs5);
	static int DES64_ECB_Decrypt(const std::string& sKey, const std::string& sSrc, unsigned char *pDecrypted, int nDecryptLen, int paddingScheme = padding_pkcs5);
	static int DES64_ECB_Decrypt(const std::string& sKey, const char* pSrc, int nSrcLen, unsigned char *pDecrypted, int nDecryptLen, int paddingScheme = padding_pkcs5);
	static int DES64_ECB_Decrypt(const std::string& sKey, const unsigned char* pSrc, int nSrcLen, unsigned char *pDecrypted, int nDecryptLen, int paddingScheme = padding_pkcs5);

	static int DES64_CBC_Decrypt(const std::string& sKey, const std::string& sIv, const std::string& sSrc, std::string& sDecrypted, int paddingScheme = padding_pkcs5); 
	static int DES64_CBC_Decrypt(const std::string& sKey, const std::string& sIv, const char* pSrc, int nSrcLen, std::string& sDecrypted, int paddingScheme = padding_pkcs5); 
	static int DES64_CBC_Decrypt(const std::string& sKey, const std::string& sIv, const unsigned char* pSrc, int nSrcLen, std::string& sDecrypted, int paddingScheme = padding_pkcs5); 
	static int DES64_CBC_Decrypt(const std::string& sKey, const std::string& sIv, const std::string& sSrc, unsigned char *pDecrypted, int nDecryptLen, int paddingScheme = padding_pkcs5); 
	static int DES64_CBC_Decrypt(const std::string& sKey, const std::string& sIv, const char* pSrc, int nSrcLen, unsigned char *pDecrypted, int nDecryptLen, int paddingScheme = padding_pkcs5); 
	static int DES64_CBC_Decrypt(const std::string& sKey, const std::string& sIv, const unsigned char* pSrc, int nSrcLen, unsigned char *pDecrypted, int nDecryptLen, int paddingScheme = padding_pkcs5); 

public:
	/*return: length of output binary on success, 0 on failure*/
	static int DES_CBC_Encrypt(const std::string& sKey, const std::string& sIv, const std::string& sSrc, unsigned char *pEncrypted, int nEncryptLen, int paddingScheme = padding_pkcs5);
	static int DES_CBC_Encrypt(const std::string& sKey, const std::string& sIv, const char *pSrc, int nSrcLen, unsigned char *pEncrypted, int nEncryptLen, int paddingScheme = padding_pkcs5);
	static int DES_CBC_Encrypt(const std::string& sKey, const std::string& sIv, const unsigned char *pSrc, int nSrcLen, unsigned char *pEncrypted, int nEncryptLen, int paddingScheme = padding_pkcs5);
	static int DES_CBC_Encrypt(DES_cblock* pKey, DES_cblock* pIv, const unsigned char *pSrc, int nSrcLen, unsigned char *pEncrypted, int nEncryptLen, int paddingScheme = padding_pkcs5);

	static int DES_ECB_Encrypt(const std::string& sKey, const std::string& sSrc, unsigned char *pEncrypted, int nEncryptLen, int paddingScheme = padding_pkcs5);
	static int DES_ECB_Encrypt(const std::string& sKey, const char *pSrc, int nSrcLen, unsigned char *pEncrypted, int nEncryptLen, int paddingScheme = padding_pkcs5);
	static int DES_ECB_Encrypt(const std::string& sKey, const unsigned char *pSrc, int nSrcLen, unsigned char *pEncrypted, int nEncryptLen, int paddingScheme = padding_pkcs5);
	static int DES_ECB_Encrypt(const_DES_cblock* pKey, const unsigned char *pSrc, int nSrcLen, unsigned char *pEncrypted, int nEncryptLen, int paddingScheme = padding_pkcs5);

	/*return: length of output binary on success, 0 on failure*/
	static int DES_CBC_Decrypt(const std::string& sKey, const std::string& sIv, const std::string& sSrc, unsigned char *pDecrypted, int nDecryptLen, int paddingScheme = padding_pkcs5);
	static int DES_CBC_Decrypt(const std::string& sKey, const std::string& sIv, const char *pSrc, int nSrcLen, unsigned char *pDecrypted, int nDecryptLen, int paddingScheme = padding_pkcs5);
	static int DES_CBC_Decrypt(const std::string& sKey, const std::string& sIv, const unsigned char *pSrc, int nSrcLen, unsigned char *pDecrypted, int nDecryptLen, int paddingScheme = padding_pkcs5);
	static int DES_CBC_Decrypt(const_DES_cblock* pKey, DES_cblock* pIv, const unsigned char *pSrc, int nSrcLen, unsigned char *pDecrypted, int nDecryptLen, int paddingScheme = padding_pkcs5);

	static int DES_ECB_Decrypt(const std::string& sKey, const std::string& sSrc, unsigned char *pDecrypted, int nDecryptLen, int paddingScheme = padding_pkcs5);
	static int DES_ECB_Decrypt(const std::string& sKey, const char *pSrc, int nSrcLen, unsigned char *pDecrypted, int nDecryptLen, int paddingScheme = padding_pkcs5);
	static int DES_ECB_Decrypt(const std::string& sKey, const unsigned char *pSrc, int nSrcLen, unsigned char *pDecrypted, int nDecryptLen, int paddingScheme = padding_pkcs5);
	static int DES_ECB_Decrypt(const_DES_cblock* pKey, const unsigned char *pSrc, int nSrcLen, unsigned char *pDecrypted, int nDecryptLen, int paddingScheme = padding_pkcs5);


//Assistant
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