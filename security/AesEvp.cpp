#include "pch.h"
#include "AesEvp.h"
#include <openssl\ossl_typ.h>
#include <openssl\evp.h>
#include <openssl\aes.h>
#include "Base64.h"
#include <memory>
#include <vector>

bool YAesEvp::AES64Encrypt_128cbc(const std::string& sKey, const std::string& sIv, const unsigned char* pSrc, int nSrcLen, std::string& sEncrypted)
{
	std::string sTmp;
	int nRes = 0;
	if(!(nRes = AESEncrypt_128cbc(sKey, sIv, pSrc, nSrcLen, sTmp)))
		return false;

	YBase64::Encode(reinterpret_cast<const unsigned char*>(sTmp.data()), nRes, sEncrypted);
	return true;
}

bool YAesEvp::AES64Decrypt_128cbc(const std::string& sKey, const std::string& sIv, const unsigned char* pSrc, int nSrcLen, std::string& sDecrypted)
{
	std::string sTmp(reinterpret_cast<const char*>(pSrc), nSrcLen);
	std::vector<unsigned char> decodedVec(nSrcLen, 0);
	int nRes =	0;
	if(!(nRes = YBase64::Decode(sTmp, &decodedVec[0], nSrcLen)))
		return false;

	bool bRet = AESDecrypt_128cbc(sKey, sIv, &decodedVec[0], nRes, sDecrypted) > 0;
	return bRet;
}

int YAesEvp::AESEncrypt_128cbc(const std::string& sKey, const std::string& sIv, const unsigned char* pSrc, int nSrcLen, std::string& sEncrypted)
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
	std::vector<unsigned char> encryptedVec(nOutLen, 0);
	if(1 != EVP_EncryptUpdate(ctx, &encryptedVec[0], &nLen1, pSrc, nSrcLen))
		return 0;

	int nLen2 = 0;
	if(1 != EVP_EncryptFinal_ex(ctx, &encryptedVec[nLen1], &nLen2))
		return 0;

	nOutLen = nLen1 + nLen2;

	EVP_CIPHER_CTX_free(ctx);
	sEncrypted.assign(reinterpret_cast<const char*>(&encryptedVec[0]), nOutLen);

	return nOutLen;
}

int YAesEvp::AESDecrypt_128cbc(const std::string& sKey, const std::string& sIv, const unsigned char* pSrc, int nSrcLen, std::string& sDecrypted)
{
	if(sKey.length() != 16 || sIv.length() != 16)		return 0;
	sDecrypted.clear();

	EVP_CIPHER_CTX *ctx;
	if(!(ctx = EVP_CIPHER_CTX_new()))		return 0;

	if(1 != EVP_DecryptInit_ex(ctx, EVP_aes_128_cbc(), NULL, reinterpret_cast<const unsigned char*>(sKey.data()), reinterpret_cast<const unsigned char*>(sIv.data())))		return 0;

	int nBlockSize = EVP_CIPHER_block_size(EVP_aes_128_cbc());
	int nPlainTextLen = 0;
	int nOutLen = nSrcLen + nBlockSize;

	std::vector<unsigned char> decryptedVec(nOutLen, 0);
	int nLen1 = 0;
	if(1 != EVP_DecryptUpdate(ctx, &decryptedVec[0], &nLen1, pSrc, nSrcLen))
		return 0;

	nPlainTextLen = nLen1;

	int nLen2 = 0;
	if(1 != EVP_DecryptFinal_ex(ctx, &decryptedVec[nLen1], &nLen2))
		return 0;

	nPlainTextLen += nLen2;
	EVP_CIPHER_CTX_free(ctx);

	sDecrypted.assign(reinterpret_cast<const char*>(&decryptedVec[0]), nPlainTextLen);

	return nPlainTextLen;
}