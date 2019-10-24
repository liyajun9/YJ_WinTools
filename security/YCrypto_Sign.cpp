#include "stdafx.h"
#include "YCrypto_Sign.h"
#include <openssl/pem.h>
#include "YMD5.h"
#include "YBase64.h"

int CYCrypto_Sign::RSA_MD5_Sign(const std::string& sPEMFilePath, const std::string& sMsg, std::string& sSign)
{
	return RSA_MD5_Sign(sPEMFilePath, reinterpret_cast<const unsigned char*>(sMsg.data()), sMsg.length(), sSign);
}

int CYCrypto_Sign::RSA_MD5_SignVerify(const std::string& sPEMFilePath,  const std::string& sSign, const std::string& sMsg)
{
	return RSA_MD5_SignVerify(sPEMFilePath, sSign, reinterpret_cast<const unsigned char*>(sMsg.data()), sMsg.length());
}

int CYCrypto_Sign::RSA_MD5_Sign(const std::string& sPEMFilePath, const unsigned char* pSrc, int nSrcLen, std::string& sSign)
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
	CYMD5::Update(reinterpret_cast<const void *>(pSrc), nSrcLen, reinterpret_cast<char *>(pDigest), MD5_BUFFER_SIZE, false);

	int nOutLen = RSA_size(pPriKey);
	unsigned char *pDst = new unsigned char[nOutLen];
	memset(pDst, 0, nOutLen);

	unsigned int nRet(0);
	unsigned int nLen(0);
	nRet = RSA_sign(NID_md5, pDigest, MD5_BUFFER_SIZE, pDst, &nLen, pPriKey);
	if(nRet > 0){
		std::string sTmp(reinterpret_cast<char*>(pDst), nLen);
		CYBase64::Encode(sTmp, nLen, sSign);
	}

	if(pDst)
		delete []pDst;
	return (int)nLen;
}

int CYCrypto_Sign::RSA_MD5_SignVerify(const std::string& sPEMFilePath,  const std::string& sSign, const unsigned char *pSrc, int nSrcLen)
{
	unsigned char pDigest[MD5_BUFFER_SIZE];
	memset(pDigest, 0, MD5_BUFFER_SIZE);
	CYMD5::Update(reinterpret_cast<const void *>(pSrc), nSrcLen, reinterpret_cast<char *>(pDigest), MD5_BUFFER_SIZE, false);

	FILE* pPubKeyFile = fopen(sPEMFilePath.c_str(), "rb");
	if(pPubKeyFile == NULL)
		return 0;

	RSA *pPubKey = RSA_new();
	pPubKey = PEM_read_RSA_PUBKEY(pPubKeyFile, &pPubKey, NULL, NULL);

	fclose(pPubKeyFile);
	if(pPubKey == NULL)
		return 0;

	int nLen = sSign.length();
	unsigned char *pDecoded = new unsigned char[nLen];
	memset(pDecoded, 0, nLen);
	int nRetnLen = CYBase64::Decode(sSign, pDecoded, nLen);

	int nRet = RSA_verify(NID_md5, pDigest, MD5_BUFFER_SIZE, pDecoded, nRetnLen, pPubKey);
	if(pDecoded)
		delete []pDecoded;
	return nRet;
}

CYCrypto_Sign::CYCrypto_Sign()
{
}

CYCrypto_Sign::~CYCrypto_Sign()
{
}