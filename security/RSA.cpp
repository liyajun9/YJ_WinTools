#include "pch.h"
#include "RSA.h"
#include <openssl/pem.h>
#include "Base64.h"
#include <memory>
#include <vector>

#pragma warning(disable:4996)

bool YRsa::PriKey_Decrypt64(const std::string& sPEMFilePath, const std::string& sSrc, std::string& sDecrypted)
{
	const unsigned char* pSrc = reinterpret_cast<const unsigned char*>(sSrc.c_str());
	int nSrcLen = sSrc.length();

	return PriKey_Decrypt64(sPEMFilePath, pSrc, nSrcLen, sDecrypted);
}

bool YRsa::PriKey_Decrypt64(const std::string& sPEMFilePath, const char *pSrc, int nSrcLen, std::string& sDecrypted)
{
	return PriKey_Decrypt64(sPEMFilePath, reinterpret_cast<const unsigned char*>(pSrc), nSrcLen, sDecrypted);
}

bool YRsa::PriKey_Decrypt64(const std::string& sPEMFilePath, const unsigned char *pSrc, int nSrcLen, std::string& sDecrypted)
{
	std::string sSrc(reinterpret_cast<const char *>(pSrc), nSrcLen);
	std::vector<unsigned char> decodedVec(nSrcLen, 0);
	int nLen = YBase64::Decode(sSrc, &decodedVec[0], nSrcLen);

	bool bRet = PriKey_Decrypt(sPEMFilePath, &decodedVec[0], nLen, sDecrypted) > 0;
	return bRet;
}

bool YRsa::PubKey_Encrypt64(const std::string& sPEMFilePath, const std::string& sSrc, std::string& sEncrypted)
{
	const unsigned char* pSrc = reinterpret_cast<const unsigned char*>(sSrc.c_str());
	int nSrcLen = sSrc.length();

	return PubKey_Encrypt64(sPEMFilePath, pSrc, nSrcLen, sEncrypted);
}

bool YRsa::PubKey_Encrypt64(const std::string& sPEMFilePath, const char* pSrc, int nSrcLen, std::string& sEncrypted)
{
	return PubKey_Encrypt64(sPEMFilePath, reinterpret_cast<const unsigned char*>(pSrc), nSrcLen, sEncrypted);
}

bool YRsa::PubKey_Encrypt64(const std::string& sPEMFilePath, const unsigned char* pSrc, int nSrcLen, std::string& sEncrypted)
{
	std::string sTmp;
	int nLen = PubKey_Encrypt(sPEMFilePath, pSrc, nSrcLen, sTmp);
	if(0 >= nLen)		return false;

	YBase64::Encode(sTmp, nLen, sEncrypted);
	return true;
}

int YRsa::PriKey_Decrypt(const std::string& sPEMFilePath, const std::string& sSrc, std::string& sDecrypted)
{
	const unsigned char* pSrc = reinterpret_cast<const unsigned char*>(sSrc.c_str());
	int nSrcLen = sSrc.length();

	return PriKey_Decrypt(sPEMFilePath, pSrc, nSrcLen, sDecrypted);
}

int YRsa::PriKey_Decrypt(const std::string& sPEMFilePath, const char *pSrc, int nSrcLen, std::string& sDecrypted)
{
	return PriKey_Decrypt(sPEMFilePath, reinterpret_cast<const unsigned char*>(pSrc), nSrcLen, sDecrypted);
}

int YRsa::PriKey_Decrypt(const std::string& sPEMFilePath, const unsigned char *pSrc, int nSrcLen, std::string& sDecrypted)
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
	std::vector<unsigned char> unitDstVec(nUnitLen, 0);

	int nCurrLen = 0;
	int nPos = 0;
	int nOutLen = 0;

	while(nRemain > 0){
		if(nRemain > nModulusLen)
			nCurrLen = nModulusLen;
		else
			nCurrLen = nRemain;

		unitDstVec.assign(nUnitLen, 0);
		int nRes = RSA_private_decrypt(nCurrLen, pSrc + nPos, &unitDstVec[0], pPriKey, RSA_PKCS1_PADDING);
		if(nRes < 0)
			break;

		sDecrypted.append(reinterpret_cast<char *>(&unitDstVec[0]), nRes);

		nRemain -= nCurrLen;
		nPos += nCurrLen;
		nOutLen += nRes;
	}

	RSA_free(pPriKey);
	CRYPTO_cleanup_all_ex_data();
	return nOutLen;
}

int YRsa::PubKey_Encrypt(const std::string& sPEMFilePath, const std::string& sSrc, std::string& sEncrypted)
{
	const unsigned char* pSrc = reinterpret_cast<const unsigned char*>(sSrc.c_str());
	int nSrcLen = sSrc.length();

	return PubKey_Encrypt(sPEMFilePath, pSrc, nSrcLen, sEncrypted);
}

int YRsa::PubKey_Encrypt(const std::string& sPEMFilePath, const char* pSrc, int nSrcLen, std::string& sEncrypted)
{
	return PubKey_Encrypt(sPEMFilePath, reinterpret_cast<const unsigned char*>(pSrc), nSrcLen, sEncrypted);
}

int YRsa::PubKey_Encrypt(const std::string& sPEMFilePath, const unsigned char* pSrc, int nSrcLen, std::string& sEncrypted)
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
	std::vector<unsigned char> unitDstVec(nModulusLen, 0);
	int nUnitLen = nModulusLen - 11; //PKCS#1 padding

	int nCurrLen = 0;
	int nPos = 0;
	int nOutLen = 0;

	while(nRemain > 0){
		if(nRemain > nUnitLen)
			nCurrLen = nUnitLen;
		else
			nCurrLen = nRemain;

		unitDstVec.assign(nModulusLen, 0);
		int nRes = RSA_public_encrypt(nCurrLen, pSrc + nPos, &unitDstVec[0], pPubKey, RSA_PKCS1_PADDING);
		if(nRes < 0)
			break;

		sEncrypted.append(reinterpret_cast<char *>(&unitDstVec[0]), nRes);

		nRemain -= nCurrLen;
		nPos += nCurrLen;
		nOutLen += nRes;
	}
	RSA_free(pPubKey);
	CRYPTO_cleanup_all_ex_data();
	return nOutLen;
}