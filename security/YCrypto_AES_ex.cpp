#include "stdafx.h"
#include "YCrypto_AES_ex.h"
#include <openssl\ossl_typ.h>
#include <openssl\evp.h>
#include <openssl\aes.h>
#include "YBase64.h"

bool CYCrypto_AES_ex::AES64Encrypt_128cbc(const std::string& sKey, const std::string& sIv, const unsigned char* pSrc, int nSrcLen, std::string& sEncrypted)
{
	std::string sTmp;
	int nRes = 0;
	if(!(nRes = AESEncrypt_128cbc(sKey, sIv, pSrc, nSrcLen, sTmp)))
		return false;

	CYBase64::Encode(reinterpret_cast<const unsigned char*>(sTmp.data()), nRes, sEncrypted);
	return true;
}

bool CYCrypto_AES_ex::AES64Decrypt_128cbc(const std::string& sKey, const std::string& sIv, const unsigned char* pSrc, int nSrcLen, std::string& sDecrypted)
{
	std::string sTmp(reinterpret_cast<const char*>(pSrc), nSrcLen);
	unsigned char *pDecoded = new unsigned char[nSrcLen];	memset(pDecoded, 0, nSrcLen);
	int nRes =	0;
	if(!(nRes = CYBase64::Decode(sTmp, pDecoded, nSrcLen))){
		if(pDecoded) delete []pDecoded;
		return false;
	}	
	return AESDecrypt_128cbc(sKey, sIv, pDecoded, nRes, sDecrypted) > 0;
}

int CYCrypto_AES_ex::AESEncrypt_128cbc(const std::string& sKey, const std::string& sIv, const unsigned char* pSrc, int nSrcLen, std::string& sEncrypted)
{
	if(sKey.length() != 16 || sIv.length() != 16)		return 0;
	sEncrypted.clear();

	//create context
	EVP_CIPHER_CTX *ctx;
	if(!(ctx = EVP_CIPHER_CTX_new()))		return 0;

	//Initialize EVP_CIPHER
	if(1 != EVP_EncryptInit_ex(ctx, EVP_aes_128_cbc(), NULL, reinterpret_cast<const unsigned char*>(sKey.data()), reinterpret_cast<const unsigned char*>(sIv.data())))	return 0;

	int nBlockSize = EVP_CIPHER_block_size(EVP_aes_128_cbc());
	int nOutLen = nSrcLen + nBlockSize  - 1;
	int nLen1  = 0;
	unsigned char *pEncrypted = new unsigned char[nOutLen]; memset(pEncrypted, 0, nOutLen);
	if(1 != EVP_EncryptUpdate(ctx, pEncrypted, &nLen1, pSrc, nSrcLen)) {
		if(pEncrypted) delete []pEncrypted;
		return 0;
	}	

	int nLen2 = 0;
	if(1 != EVP_EncryptFinal_ex(ctx, pEncrypted + nLen1, &nLen2)){
		if(pEncrypted) delete []pEncrypted;
		return 0;
	}

	nOutLen = nLen1 + nLen2;

	EVP_CIPHER_CTX_free(ctx);
	sEncrypted.assign(reinterpret_cast<const char*>(pEncrypted), nOutLen);  
	if(pEncrypted) delete []pEncrypted;

	return nOutLen;
}

int CYCrypto_AES_ex::AESDecrypt_128cbc(const std::string& sKey, const std::string& sIv, const unsigned char* pSrc, int nSrcLen, std::string& sDecrypted)
{
	if(sKey.length() != 16 || sIv.length() != 16)		return 0;
	sDecrypted.clear();

	EVP_CIPHER_CTX *ctx;
	if(!(ctx = EVP_CIPHER_CTX_new()))		return 0;

	if(1 != EVP_DecryptInit_ex(ctx, EVP_aes_128_cbc(), NULL, reinterpret_cast<const unsigned char*>(sKey.data()), reinterpret_cast<const unsigned char*>(sIv.data())))		return 0;

	int nBlockSize = EVP_CIPHER_block_size(EVP_aes_128_cbc());
	int nPlainTextLen = 0;
	int nOutLen = nSrcLen + nBlockSize;
	unsigned char *pDecrypted = new unsigned char[nOutLen]; memset(pDecrypted, 0, nOutLen);
	int nLen1 = 0;
	if(1 != EVP_DecryptUpdate(ctx, pDecrypted, &nLen1, pSrc, nSrcLen)){
		if(pDecrypted) delete []pDecrypted;
		return 0;
	}
	nPlainTextLen = nLen1;

	int nLen2 = 0;
	if(1 != EVP_DecryptFinal_ex(ctx, pDecrypted + nLen1, &nLen2)){
		if(pDecrypted) delete []pDecrypted;
		return 0;
	}
	nPlainTextLen += nLen2;
	EVP_CIPHER_CTX_free(ctx);

	sDecrypted.assign(reinterpret_cast<const char*>(pDecrypted), nPlainTextLen);

	if(pDecrypted) delete []pDecrypted;
	return nPlainTextLen;
}

CYCrypto_AES_ex::CYCrypto_AES_ex()
{
}

CYCrypto_AES_ex::~CYCrypto_AES_ex()
{
}