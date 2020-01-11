#include "stdafx.h"
#include "Crypto_Sign.h"
#include <openssl/pem.h>
#include "MD5.h"
#include "Base64.h"
#include <memory>

#pragma warning(disable:4996)

int YCrypto_Sign::RSA_MD5_SignVerify(const std::string& sPEMFilePath,  const std::string& sSign, const std::string& sMsg)
{
	return RSA_MD5_SignVerify(sPEMFilePath, sSign, reinterpret_cast<const unsigned char*>(sMsg.data()), sMsg.length());
}

int YCrypto_Sign::RSA_MD5_SignVerify(const std::string& sPEMFilePath,  const std::string& sSign, const char *pSrc, int nSrcLen)
{
	return RSA_MD5_SignVerify(sPEMFilePath, sSign, reinterpret_cast<const unsigned char*>(pSrc), nSrcLen);
}

int YCrypto_Sign::RSA_MD5_SignVerify(const std::string& sPEMFilePath,  const std::string& sSign, const unsigned char *pSrc, int nSrcLen)
{
	unsigned char pDigest[MD5_BUFFER_SIZE];
	memset(pDigest, 0, MD5_BUFFER_SIZE);
	YMD5::Update(reinterpret_cast<const void *>(pSrc), nSrcLen, reinterpret_cast<char *>(pDigest), MD5_BUFFER_SIZE, false);

	FILE* pPubKeyFile = fopen(sPEMFilePath.c_str(), "rb");
	if(pPubKeyFile == NULL)
		return 0;

	RSA *pPubKey = RSA_new();
	pPubKey = PEM_read_RSA_PUBKEY(pPubKeyFile, &pPubKey, NULL, NULL);

	fclose(pPubKeyFile);
	if(pPubKey == NULL)
		return 0;

	int nLen = sSign.length();
	std::shared_ptr<unsigned char> spDecoded(new unsigned char[nLen], std::default_delete<unsigned char[]>());
	memset(spDecoded.get(), 0, nLen);
	int nRetnLen = YBase64::Decode(sSign, spDecoded.get(), nLen);

	int nRet = RSA_verify(NID_md5, pDigest, MD5_BUFFER_SIZE, spDecoded.get(), nRetnLen, pPubKey);
	return nRet;
}

int YCrypto_Sign::RSA_MD5_Sign(const std::string& sPEMFilePath, const std::string& sMsg, std::string& sSign)
{
	return RSA_MD5_Sign(sPEMFilePath, reinterpret_cast<const unsigned char*>(sMsg.data()), sMsg.length(), sSign);
}

int YCrypto_Sign::RSA_MD5_Sign(const std::string& sPEMFilePath, const char* pSrc, int nSrcLen, std::string& sSign)
{
	return RSA_MD5_Sign(sPEMFilePath, reinterpret_cast<const unsigned char*>(pSrc), nSrcLen, sSign);
}

int YCrypto_Sign::RSA_MD5_Sign(const std::string& sPEMFilePath, const unsigned char* pSrc, int nSrcLen, std::string& sSign)
{
	sSign.clear();
	FILE* pPriKeyFile = fopen(sPEMFilePath.c_str(), "r");
	if(pPriKeyFile == NULL)
		return 0;

	RSA *pPriKey = RSA_new();
	pPriKey = PEM_read_RSAPrivateKey(pPriKeyFile, NULL, NULL, NULL);
	fclose(pPriKeyFile);
	if(pPriKey == NULL)
		return 0;

	unsigned char pDigest[MD5_BUFFER_SIZE];
	memset(pDigest, 0, MD5_BUFFER_SIZE);
	YMD5::Update(reinterpret_cast<const void *>(pSrc), nSrcLen, reinterpret_cast<char *>(pDigest), MD5_BUFFER_SIZE, false);

	int nOutLen = RSA_size(pPriKey);
	std::shared_ptr<unsigned char> spDst(new unsigned char[nOutLen], std::default_delete<unsigned char[]>());
	memset(spDst.get(), 0, nOutLen);

	unsigned int nRet(0);
	unsigned int nLen(0);
	nRet = RSA_sign(NID_md5, pDigest, MD5_BUFFER_SIZE, spDst.get(), &nLen, pPriKey);
	if(nRet > 0){
		std::string sTmp(reinterpret_cast<char*>(spDst.get()), nLen);
		YBase64::Encode(sTmp, nLen, sSign);
	}

	return (int)nLen;
}