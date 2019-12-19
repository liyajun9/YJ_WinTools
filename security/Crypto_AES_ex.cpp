#include "stdafx.h"
#include "Crypto_AES_ex.h"
#include <openssl\ossl_typ.h>
#include <openssl\evp.h>
#include <openssl\aes.h>
#include "Base64.h"
#include <memory>

bool YCrypto_AES_ex::AES64Encrypt_128cbc(const std::string& sKey, const std::string& sIv, const unsigned char* pSrc, int nSrcLen, std::string& sEncrypted)
{
	std::string sTmp;
	int nRes = 0;
	if(!(nRes = AESEncrypt_128cbc(sKey, sIv, pSrc, nSrcLen, sTmp)))
		return false;

	YBase64::Encode(reinterpret_cast<const unsigned char*>(sTmp.data()), nRes, sEncrypted);
	return true;
}

bool YCrypto_AES_ex::AES64Decrypt_128cbc(const std::string& sKey, const std::string& sIv, const unsigned char* pSrc, int nSrcLen, std::string& sDecrypted)
{
	std::string sTmp(reinterpret_cast<const char*>(pSrc), nSrcLen);
	std::shared_ptr<unsigned char> spDecoded(new unsigned char[nSrcLen], std::default_delete<unsigned char[]>());
	memset(spDecoded.get(), 0, nSrcLen);
	int nRes =	0;
	if(!(nRes = YBase64::Decode(sTmp, spDecoded.get(), nSrcLen)))
		return false;

	bool bRet = AESDecrypt_128cbc(sKey, sIv, spDecoded.get(), nRes, sDecrypted) > 0;
	return bRet;
}

int YCrypto_AES_ex::AESEncrypt_128cbc(const std::string& sKey, const std::string& sIv, const unsigned char* pSrc, int nSrcLen, std::string& sEncrypted)
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
	std::shared_ptr<unsigned char> spEncrypted(new unsigned char[nOutLen], std::default_delete<unsigned char[]>());
	memset(spEncrypted.get(), 0, nOutLen);
	if(1 != EVP_EncryptUpdate(ctx, spEncrypted.get(), &nLen1, pSrc, nSrcLen)) 
		return 0;

	int nLen2 = 0;
	if(1 != EVP_EncryptFinal_ex(ctx, spEncrypted.get() + nLen1, &nLen2))
		return 0;

	nOutLen = nLen1 + nLen2;

	EVP_CIPHER_CTX_free(ctx);
	sEncrypted.assign(reinterpret_cast<const char*>(spEncrypted.get()), nOutLen);  

	return nOutLen;
}

int YCrypto_AES_ex::AESDecrypt_128cbc(const std::string& sKey, const std::string& sIv, const unsigned char* pSrc, int nSrcLen, std::string& sDecrypted)
{
	if(sKey.length() != 16 || sIv.length() != 16)		return 0;
	sDecrypted.clear();

	EVP_CIPHER_CTX *ctx;
	if(!(ctx = EVP_CIPHER_CTX_new()))		return 0;

	if(1 != EVP_DecryptInit_ex(ctx, EVP_aes_128_cbc(), NULL, reinterpret_cast<const unsigned char*>(sKey.data()), reinterpret_cast<const unsigned char*>(sIv.data())))		return 0;

	int nBlockSize = EVP_CIPHER_block_size(EVP_aes_128_cbc());
	int nPlainTextLen = 0;
	int nOutLen = nSrcLen + nBlockSize;
	std::shared_ptr<unsigned char> spDecrypted(new unsigned char[nOutLen], std::default_delete<unsigned char[]>());
	memset(spDecrypted.get(), 0, nOutLen);
	int nLen1 = 0;
	if(1 != EVP_DecryptUpdate(ctx, spDecrypted.get(), &nLen1, pSrc, nSrcLen))
		return 0;

	nPlainTextLen = nLen1;

	int nLen2 = 0;
	if(1 != EVP_DecryptFinal_ex(ctx, spDecrypted.get() + nLen1, &nLen2))
		return 0;

	nPlainTextLen += nLen2;
	EVP_CIPHER_CTX_free(ctx);

	sDecrypted.assign(reinterpret_cast<const char*>(spDecrypted.get()), nPlainTextLen);

	return nPlainTextLen;
}

YCrypto_AES_ex::YCrypto_AES_ex()
{
}

YCrypto_AES_ex::~YCrypto_AES_ex()
{
}