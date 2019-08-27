// Crypto_DES
// #not set parity for keys
// author:liyajun

#pragma once

#include <string>
#include <openssl/des.h>

enum des_block_mode{
	des_ECB = 0, //algorithm_ecb_encrypt
	des_CBC = 1, //algorithm_cbc_encrypt, does not update the IV 
	des_CBC_REAL = 2, //des_ncbc_enctryp, update the IV
	des_CFB = 3, //algorithm_cfb_encrypt
	des_OFB = 4, //algorithm_ofb_encrypt
	des_TRIPLE_ECB = 5, //algorithm_ecb3_encrypt
	des_TRIPLE_CBC = 6  //algorithm_ede3_cbc_encrypt
};

class CYCrypto_DES{	
public:
	static void DES64_CBC_JavaLike(const std::string& sKey, const std::string& sIv,const std::string& sInData, std::string& sOutData, bool bEncrypt);

	static void DES_ECB(const std::string& sKey, const std::string& sInData, unsigned int nCbLen, std::string& sOutData, bool bEncrypt, int paddingScheme);
	static void DES_ECB(DES_cblock* pKey, const void* pInData, unsigned int nCbLen, std::string& sOutData, bool bEncrypt, int paddingScheme);

	static void DES_CBC(const std::string& sKey, const std::string& sIv,const std::string& sInData, unsigned int nCbLen, std::string& sOutData, bool bEncrypt, int paddingScheme);
	static void DES_CBC(DES_cblock* pKey, DES_cblock* pIv,const void* pInData, unsigned int nCbLen, std::string& sOutData, bool bEncrypt, int paddingScheme);

public:
	static std::string DESKeyToHexString(const DES_cblock* pKey, bool isToUpperCase);
	static bool HexStringToDESKey(const std::string& sSrc, bool isUpperCase, DES_cblock* pKey);

	static std::string DESKeyToString(const DES_cblock* pKey);

public:
	static void GenerateKeyLikeJava(const std::string& sKey, DES_cblock* pKey);//calc MD5 of key, and set parity to odd

private:
	CYCrypto_DES(){}
	~CYCrypto_DES(){}
};