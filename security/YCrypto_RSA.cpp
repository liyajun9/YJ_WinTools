#include "stdafx.h"
#include "YCrypto_RSA.h"
#include <openssl/pem.h>
#include "YBase64.h"

#pragma warning(disable:4996)

bool CYCrypto_RSA::PubKey_Encrypt64(const std::string& sPEMFilePath, const unsigned char* pSrc, int nSrcLen, std::string& sEncrypted)
{
	std::string sTmp;
	int nLen = PubKey_Encrypt(sPEMFilePath, pSrc, nSrcLen, sTmp);
	if(0 >= nLen)		return false;

	CYBase64::Encode(sTmp, nLen, sEncrypted);
	return true;
}

bool CYCrypto_RSA::PriKey_Decrypt64(const std::string& sPEMFilePath, const unsigned char *pSrc, int nSrcLen, std::string& sDecrypted)
{
	std::string sSrc(reinterpret_cast<const char *>(pSrc), nSrcLen);
	unsigned char *pDecoded = new unsigned char[nSrcLen];
	memset(pDecoded, 0, nSrcLen);
	int nLen = CYBase64::Decode(sSrc, pDecoded, nSrcLen);

	return PriKey_Decrypt(sPEMFilePath, pDecoded, nLen, sDecrypted) > 0;
}

int CYCrypto_RSA::PubKey_Encrypt(const std::string& sPEMFilePath, const unsigned char* pSrc, int nSrcLen, std::string& sEncrypted)
{
	sEncrypted.clear();
	FILE* pPubKeyFile = fopen(sPEMFilePath.c_str(), "rb");
	if(pPubKeyFile == NULL)
		return 0;

	RSA *pPubKey = RSA_new();
	pPubKey = PEM_read_RSA_PUBKEY(pPubKeyFile, &pPubKey, NULL, NULL);

	fclose(pPubKeyFile);
	if(pPubKey == NULL)
		return 0;

	int nRemain = nSrcLen;
	int nModulusLen = RSA_size(pPubKey);	//cipher text length
	unsigned char *pUnitDst= new unsigned char[nModulusLen];
	int nUnitLen = nModulusLen - 11; //PKCS#1 padding
		
	int nCurrLen = 0;
	int nPos = 0;
	int nOutLen = 0;

	while(nRemain > 0){
		if(nRemain > nUnitLen)
			nCurrLen = nUnitLen;
		else
			nCurrLen = nRemain;

		memset(pUnitDst, 0, nModulusLen);
		int nRes = RSA_public_encrypt(nCurrLen, pSrc + nPos, pUnitDst, pPubKey, RSA_PKCS1_PADDING);
		if(nRes < 0)
			break;

		sEncrypted.append(reinterpret_cast<char *>(pUnitDst), nRes);

		nRemain -= nCurrLen;
		nPos += nCurrLen;
		nOutLen += nRes;
	}
	if(pUnitDst)
		delete []pUnitDst;
	RSA_free(pPubKey);
	CRYPTO_cleanup_all_ex_data();
	return nOutLen;
}

int CYCrypto_RSA::PriKey_Decrypt(const std::string& sPEMFilePath, const unsigned char *pSrc, int nSrcLen, std::string& sDecrypted)
{
	sDecrypted.clear();
	FILE* pPriKeyFile = fopen(sPEMFilePath.c_str(), "r");
	if(pPriKeyFile == NULL)
		return 0;

	RSA *pPriKey = RSA_new();
	pPriKey = PEM_read_RSAPrivateKey(pPriKeyFile, NULL, NULL, NULL);
	fclose(pPriKeyFile);
	if(pPriKey == NULL)
		return 0;

	int nRemain = nSrcLen;
	int nModulusLen = RSA_size(pPriKey);  //cipherText unit length
	int nUnitLen = nModulusLen - 11; //PKCS#1 padding plainText unit length
	unsigned char *pUnitDst= new unsigned char[nUnitLen];

	int nCurrLen = 0;
	int nPos = 0;
	int nOutLen = 0;

	while(nRemain > 0){
		if(nRemain > nModulusLen)
			nCurrLen = nModulusLen;
		else
			nCurrLen = nRemain;

		memset(pUnitDst, 0, nUnitLen);
		int nRes = RSA_private_decrypt(nCurrLen, pSrc + nPos, pUnitDst, pPriKey, RSA_PKCS1_PADDING);
		if(nRes < 0)
			break;

		sDecrypted.append(reinterpret_cast<char *>(pUnitDst), nRes);

		nRemain -= nCurrLen;
		nPos += nCurrLen;
		nOutLen += nRes;
	}

	if(pUnitDst)
		delete []pUnitDst;
	RSA_free(pPriKey);
	CRYPTO_cleanup_all_ex_data();
	return nOutLen;
}