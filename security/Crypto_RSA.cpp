#include "stdafx.h"
#include "Crypto_RSA.h"
#include <openssl/pem.h>
#include "Base64.h"
#include <memory>

#pragma warning(disable:4996)

bool YCrypto_RSA::PriKey_Decrypt64(const std::string& sPEMFilePath, const std::string& sSrc, std::string& sDecrypted)
{
	const unsigned char* pSrc = reinterpret_cast<const unsigned char*>(sSrc.c_str());
	int nSrcLen = sSrc.length();

	return PriKey_Decrypt64(sPEMFilePath, pSrc, nSrcLen, sDecrypted);
}

bool YCrypto_RSA::PriKey_Decrypt64(const std::string& sPEMFilePath, const char *pSrc, int nSrcLen, std::string& sDecrypted)
{
	return PriKey_Decrypt64(sPEMFilePath, reinterpret_cast<const unsigned char*>(pSrc), nSrcLen, sDecrypted);
}

bool YCrypto_RSA::PriKey_Decrypt64(const std::string& sPEMFilePath, const unsigned char *pSrc, int nSrcLen, std::string& sDecrypted)
{
	std::string sSrc(reinterpret_cast<const char *>(pSrc), nSrcLen);
	std::shared_ptr<unsigned char> spDecoded(new unsigned char[nSrcLen], std::default_delete<unsigned char[]>());
	memset(spDecoded.get(), 0, nSrcLen);
	int nLen = YBase64::Decode(sSrc, spDecoded.get(), nSrcLen);

	bool bRet = PriKey_Decrypt(sPEMFilePath, spDecoded.get(), nLen, sDecrypted) > 0;
	return bRet;
}

bool YCrypto_RSA::PubKey_Encrypt64(const std::string& sPEMFilePath, const std::string& sSrc, std::string& sEncrypted)
{
	const unsigned char* pSrc = reinterpret_cast<const unsigned char*>(sSrc.c_str());
	int nSrcLen = sSrc.length();

	return PubKey_Encrypt64(sPEMFilePath, pSrc, nSrcLen, sEncrypted);
}

bool YCrypto_RSA::PubKey_Encrypt64(const std::string& sPEMFilePath, const char* pSrc, int nSrcLen, std::string& sEncrypted)
{
	return PubKey_Encrypt64(sPEMFilePath, reinterpret_cast<const unsigned char*>(pSrc), nSrcLen, sEncrypted);
}

bool YCrypto_RSA::PubKey_Encrypt64(const std::string& sPEMFilePath, const unsigned char* pSrc, int nSrcLen, std::string& sEncrypted)
{
	std::string sTmp;
	int nLen = PubKey_Encrypt(sPEMFilePath, pSrc, nSrcLen, sTmp);
	if(0 >= nLen)		return false;

	YBase64::Encode(sTmp, nLen, sEncrypted);
	return true;
}

int YCrypto_RSA::PriKey_Decrypt(const std::string& sPEMFilePath, const std::string& sSrc, std::string& sDecrypted)
{
	const unsigned char* pSrc = reinterpret_cast<const unsigned char*>(sSrc.c_str());
	int nSrcLen = sSrc.length();

	return PriKey_Decrypt(sPEMFilePath, pSrc, nSrcLen, sDecrypted);
}

int YCrypto_RSA::PriKey_Decrypt(const std::string& sPEMFilePath, const char *pSrc, int nSrcLen, std::string& sDecrypted)
{
	return PriKey_Decrypt(sPEMFilePath, reinterpret_cast<const unsigned char*>(pSrc), nSrcLen, sDecrypted);
}

int YCrypto_RSA::PriKey_Decrypt(const std::string& sPEMFilePath, const unsigned char *pSrc, int nSrcLen, std::string& sDecrypted)
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
	std::shared_ptr<unsigned char> spUnitDst(new unsigned char[nUnitLen], std::default_delete<unsigned char[]>());

	int nCurrLen = 0;
	int nPos = 0;
	int nOutLen = 0;

	while(nRemain > 0){
		if(nRemain > nModulusLen)
			nCurrLen = nModulusLen;
		else
			nCurrLen = nRemain;

		memset(spUnitDst.get(), 0, nUnitLen);
		int nRes = RSA_private_decrypt(nCurrLen, pSrc + nPos, spUnitDst.get(), pPriKey, RSA_PKCS1_PADDING);
		if(nRes < 0)
			break;

		sDecrypted.append(reinterpret_cast<char *>(spUnitDst.get()), nRes);

		nRemain -= nCurrLen;
		nPos += nCurrLen;
		nOutLen += nRes;
	}

	RSA_free(pPriKey);
	CRYPTO_cleanup_all_ex_data();
	return nOutLen;
}

int YCrypto_RSA::PubKey_Encrypt(const std::string& sPEMFilePath, const std::string& sSrc, std::string& sEncrypted)
{
	const unsigned char* pSrc = reinterpret_cast<const unsigned char*>(sSrc.c_str());
	int nSrcLen = sSrc.length();

	return PubKey_Encrypt(sPEMFilePath, pSrc, nSrcLen, sEncrypted);
}

int YCrypto_RSA::PubKey_Encrypt(const std::string& sPEMFilePath, const char* pSrc, int nSrcLen, std::string& sEncrypted)
{
	return PubKey_Encrypt(sPEMFilePath, reinterpret_cast<const unsigned char*>(pSrc), nSrcLen, sEncrypted);
}

int YCrypto_RSA::PubKey_Encrypt(const std::string& sPEMFilePath, const unsigned char* pSrc, int nSrcLen, std::string& sEncrypted)
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
	std::shared_ptr<unsigned char> spUnitDst(new unsigned char[nModulusLen], std::default_delete<unsigned char[]>());
	int nUnitLen = nModulusLen - 11; //PKCS#1 padding

	int nCurrLen = 0;
	int nPos = 0;
	int nOutLen = 0;

	while(nRemain > 0){
		if(nRemain > nUnitLen)
			nCurrLen = nUnitLen;
		else
			nCurrLen = nRemain;

		memset(spUnitDst.get(), 0, nModulusLen);
		int nRes = RSA_public_encrypt(nCurrLen, pSrc + nPos, spUnitDst.get(), pPubKey, RSA_PKCS1_PADDING);
		if(nRes < 0)
			break;

		sEncrypted.append(reinterpret_cast<char *>(spUnitDst.get()), nRes);

		nRemain -= nCurrLen;
		nPos += nCurrLen;
		nOutLen += nRes;
	}
	RSA_free(pPubKey);
	CRYPTO_cleanup_all_ex_data();
	return nOutLen;
}