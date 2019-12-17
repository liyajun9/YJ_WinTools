#include "stdafx.h"
#include "CryptoUtils.h"
#include "Crypto_DES.h"
#include "MD5.h"
#include "Base64.h"

bool YCrypto_DES::DES64_CBC_Encrypt_MD5AsKey(const std::string& sKey, const std::string& sIv,const unsigned char *pSrc, int nSrcLen, std::string& sEncrypted,  int paddingScheme)
{
	if(sKey.length() < DES_BLOCK_SIZE || sIv.length() < DES_BLOCK_SIZE) return false;

	DES_cblock key, iv;
	GetMD5AsKey(sKey, &key);
	memcpy(&iv, sIv.c_str(), DES_BLOCK_SIZE);

	return DES64_CBC_Encrypt(std::string(reinterpret_cast<char *>(&key), DES_BLOCK_SIZE), std::string(reinterpret_cast<char *>(&iv), DES_BLOCK_SIZE), pSrc, nSrcLen, sEncrypted, paddingScheme);
}

bool YCrypto_DES::DES64_CBC_Encrypt(const std::string& sKey, const std::string& sIv,const unsigned char *pSrc, int nSrcLen, std::string& sEncrypted,  int paddingScheme)
{
	if(sKey.length() < DES_BLOCK_SIZE || sIv.length() < DES_BLOCK_SIZE) return false;

	DES_cblock key, iv;
	memcpy(&key, sKey.c_str(), DES_BLOCK_SIZE);
	memcpy(&iv, sIv.c_str(), DES_BLOCK_SIZE);
	DES_key_schedule schedule;
	DES_set_key_unchecked(&key, &schedule);

	//padding for encryption
	unsigned int nLen  = (nSrcLen/DES_BLOCK_SIZE + 1) * DES_BLOCK_SIZE;
	unsigned char *pInput = new unsigned char[nLen];
	nLen = Padding(pSrc, nSrcLen, pInput, nLen, DES_BLOCK_SIZE, paddingScheme);
	if(nLen <= 0) {
		if(pInput) delete []pInput;
		return false;
	}

	unsigned char *pOutput = new unsigned char[nLen]; memset(pOutput, 0, nLen);

	//decrypt
	DES_cbc_encrypt(pInput, pOutput, nLen, &schedule, &iv, DES_ENCRYPT);

	YBase64::Encode(pOutput, nLen, sEncrypted);

	if(pInput)
		delete []pInput;	
	if(pOutput)
		delete []pOutput;
	return true;
}

int YCrypto_DES::DES64_CBC_Decrypt_MD5AsKey(const std::string& sKey, const std::string& sIv, const std::string& sSrc, std::string& sDecrypted, int paddingScheme)
{
	int nLen = sSrc.length() * 2;
	unsigned char *pDecrypted = new unsigned char[nLen]; memset(pDecrypted, 0, nLen);

	nLen = DES64_CBC_Decrypt_MD5AsKey(sKey, sIv, sSrc, pDecrypted, nLen, paddingScheme);
	if(nLen > 0)
		sDecrypted = std::string(reinterpret_cast<char *>(pDecrypted), nLen);

	if(pDecrypted) delete []pDecrypted;
	return nLen;
}

int YCrypto_DES::DES64_CBC_Decrypt_MD5AsKey(const std::string& sKey, const std::string& sIv, const std::string& sSrc, unsigned char *pDecrypted, int nDecryptLen, int paddingScheme)
{
	if(sKey.length() < DES_BLOCK_SIZE || sIv.length() < DES_BLOCK_SIZE) return false;

	DES_cblock key, iv;
	GetMD5AsKey(sKey, &key);
	memcpy(&iv, sIv.c_str(), DES_BLOCK_SIZE);

	return DES64_CBC_Decrypt(std::string(reinterpret_cast<char*>(&key)), std::string(reinterpret_cast<char *>(&iv)), sSrc, pDecrypted, nDecryptLen, paddingScheme);
}

int YCrypto_DES::DES64_CBC_Decrypt(const std::string& sKey, const std::string& sIv, const std::string& sSrc, std::string& sDecrypted, int paddingScheme)
{
	int nLen = sSrc.length();
	unsigned char *pDecrypted = new unsigned char[nLen]; memset(pDecrypted, 0, nLen);

	nLen = DES64_CBC_Decrypt(sKey, sIv, sSrc, pDecrypted, nLen, paddingScheme);
	if(nLen > 0)
		sDecrypted = std::string(reinterpret_cast<char *>(pDecrypted), nLen);

	if(pDecrypted) delete []pDecrypted;
	return nLen;
}

int YCrypto_DES::DES64_CBC_Decrypt(const std::string& sKey, const std::string& sIv, const std::string& sSrc, unsigned char *pDecrypted, int nDecryptLen, int paddingScheme)
{
	if(sKey.length() < DES_BLOCK_SIZE || sIv.length() < DES_BLOCK_SIZE) return 0;

	DES_cblock key, iv;
	memcpy(&key, sKey.c_str(), DES_BLOCK_SIZE);
	memcpy(&iv, sIv.c_str(), DES_BLOCK_SIZE);
	DES_key_schedule schedule;
	DES_set_key_unchecked(&key, &schedule);

	int nLen = sSrc.length();
	unsigned char *pInput = new unsigned char[nLen]; memset(pInput, 0, nLen);
	nLen = YBase64::Decode(sSrc, pInput, nLen);
	if(nLen <= 0 || nDecryptLen < nLen){
		if(pInput)	delete []pInput;
		return 0;
	}

	//decrypt
	int nOutLen = DES_CBC_Decrypt(&key, &iv, pInput, nLen, pDecrypted, nDecryptLen, paddingScheme);

	if(pInput)	delete []pInput;
	return nOutLen;
}

int YCrypto_DES::DES_CBC_Encrypt(DES_cblock* pKey, DES_cblock* pIv, const unsigned char *pSrc, int nSrcLen, unsigned char *pEncrypted, int nEncryptLen, int paddingScheme)
{
	DES_key_schedule schedule;
	DES_set_key_unchecked(pKey, &schedule);

	//padding for encryption
	int nLen  = (nSrcLen/DES_BLOCK_SIZE + 1) * DES_BLOCK_SIZE;
	unsigned char *pInput = new unsigned char[nLen];
	nLen = Padding(pSrc, nSrcLen, pInput, nLen, DES_BLOCK_SIZE, paddingScheme);
	if(nLen <= 0 || nEncryptLen < nLen){ 
		if(pInput) delete []pInput;
		return 0;
	}

	//encrypt
	DES_cbc_encrypt(pInput, pEncrypted, nLen, &schedule, pIv, DES_ENCRYPT);

	if(pInput)	delete []pInput;	
	return nLen;
}

int YCrypto_DES::DES_CBC_Decrypt(const_DES_cblock* pKey, DES_cblock* pIv, const unsigned char *pSrc, int nSrcLen, unsigned char *pDecrypted, int nDecryptLen, int paddingScheme)
{
	DES_key_schedule schedule;
	DES_set_key_unchecked(pKey, &schedule);

	//decrypt
	unsigned char *pOutput = new unsigned char[nSrcLen]; memset(pOutput, 0, nSrcLen); 

	DES_cbc_encrypt(pSrc, pOutput, nSrcLen, &schedule, pIv, DES_DECRYPT);

	//remove padding for decryption
	int nLen = RemovePadding(pOutput, nSrcLen, paddingScheme);
	if(nLen <= 0 || nDecryptLen < nLen) {
		if(pOutput) delete []pOutput;
		return 0;
	}

	memcpy(pDecrypted, pOutput, nLen);

	if(pOutput)
		delete []pOutput;	
	return nLen;
}

bool YCrypto_DES::DES64_ECB_Encrypt_MD5AsKey(const std::string& sKey, const unsigned char *pSrc, int nSrcLen, std::string& sEncrypted,  int paddingScheme)
{
		if(sKey.length() < DES_BLOCK_SIZE ) return false;
	
		DES_cblock key;
		GetMD5AsKey(sKey, &key);

		return DES64_ECB_Encrypt(std::string(reinterpret_cast<char*>(&key)), pSrc, nSrcLen, sEncrypted, paddingScheme);
}

bool YCrypto_DES::DES64_ECB_Encrypt(const std::string& sKey, const unsigned char *pSrc, int nSrcLen, std::string& sEncrypted,  int paddingScheme)
{
	if(sKey.length() < DES_BLOCK_SIZE) return false;

	DES_cblock key;
	memcpy(&key, sKey.c_str(), DES_BLOCK_SIZE);
	DES_key_schedule schedule;
	DES_set_key_unchecked(&key, &schedule);

	//padding for encryption
	unsigned int nLen = (nSrcLen/DES_BLOCK_SIZE + 1) * DES_BLOCK_SIZE;
	unsigned char *pInput = new unsigned char[nLen];
	nLen = Padding(pSrc, nSrcLen, pInput, nLen, DES_BLOCK_SIZE, paddingScheme);
	if(nLen <= 0){ 
		if(pInput) delete []pInput;
		return false;
	}

	unsigned char *pEncrypted = new unsigned char[nLen];

	//encrypt
	unsigned int nCount = nLen / DES_BLOCK_SIZE;
	DES_cblock input, output;
	for(unsigned int i=0; i<nCount; i++){
		memset(input, 0, DES_BLOCK_SIZE);
		memcpy(input, &(pInput[i * DES_BLOCK_SIZE]), DES_BLOCK_SIZE);
		memset(output, 0, DES_BLOCK_SIZE);

		DES_ecb_encrypt(&input, &output, &schedule, DES_ENCRYPT);
		memcpy(&(pEncrypted[i * DES_BLOCK_SIZE]), output, DES_BLOCK_SIZE);
	}

	YBase64::Encode(pEncrypted, nLen, sEncrypted);

	if(pInput)	delete []pInput;
	if(pEncrypted)	delete []pEncrypted;
	return true;
}

int YCrypto_DES::DES64_ECB_Decrypt_MD5AsKey(const std::string& sKey, const std::string& sSrc,  std::string& sDecrypted, int paddingScheme)
{
	int nLen = sSrc.length();
	unsigned char *pDecrypted = new unsigned char[nLen]; memset(pDecrypted, 0, nLen);

	nLen = DES64_ECB_Decrypt_MD5AsKey(sKey,  sSrc, pDecrypted, nLen, paddingScheme);
	if(nLen > 0)
		sDecrypted = std::string(reinterpret_cast<char *>(pDecrypted), nLen);

	if(pDecrypted) delete []pDecrypted;
	return nLen;
}

int YCrypto_DES::DES64_ECB_Decrypt_MD5AsKey(const std::string& sKey, const std::string& sSrc, unsigned char *pDecrypted, int nDecryptLen, int paddingScheme)
{
	if(sKey.length() < DES_BLOCK_SIZE ) return false;

	DES_cblock key;
	GetMD5AsKey(sKey, &key);

	return DES64_ECB_Decrypt(std::string(reinterpret_cast<char*>(&key)), sSrc, pDecrypted, nDecryptLen, paddingScheme);
}

int YCrypto_DES::DES64_ECB_Decrypt(const std::string& sKey, const std::string& sSrc,  std::string& sDecrypted, int paddingScheme)
{
	int nLen = sSrc.length();
	unsigned char *pDecrypted = new unsigned char[nLen]; memset(pDecrypted, 0, nLen);

	nLen = DES64_ECB_Decrypt(sKey,  sSrc, pDecrypted, nLen, paddingScheme);
	if(nLen > 0)
		sDecrypted = std::string(reinterpret_cast<char *>(pDecrypted), nLen);

	if(pDecrypted) delete []pDecrypted;
	return nLen;
}

int YCrypto_DES::DES64_ECB_Decrypt(const std::string& sKey, const std::string& sSrc, unsigned char *pDecrypted, int nDecryptLen, int paddingScheme)
{
	if(sKey.length() < DES_BLOCK_SIZE) return 0;

	int nLen = sSrc.length(); 
	unsigned char *pInput = new unsigned char[nLen]; memset(pInput, 0, nLen);
	nLen = YBase64::Decode(sSrc, pInput, nLen);
	if(nLen <= 0 || nDecryptLen < nLen){
		if(pInput)	delete []pInput;
		return 0;
	}

	DES_cblock key;
	memcpy(&key, sKey.c_str(), DES_BLOCK_SIZE);

	int nOutLen = DES_ECB_Decrypt(&key, pInput, nLen, pDecrypted, nDecryptLen, paddingScheme);

	if(pInput)	delete []pInput;
	return nOutLen;
}

int YCrypto_DES::DES_ECB_Decrypt(const_DES_cblock* pKey, const unsigned char *pSrc, int nSrcLen, unsigned char *pDecrypted, int nDecryptLen, int paddingScheme)
{
	DES_key_schedule schedule;
	DES_set_key_unchecked(pKey, &schedule);

	unsigned char *pOutput = new unsigned char[nSrcLen]; memset(pOutput, 0, nSrcLen);
	//decrypt
	unsigned int nCount = nSrcLen / DES_BLOCK_SIZE;

	DES_cblock input, output;
	for(unsigned int i=0; i<nCount; i++){
		memset(input, 0, DES_BLOCK_SIZE);
		memcpy(input, &(pSrc[i * DES_BLOCK_SIZE]), DES_BLOCK_SIZE);
		memset(output, 0, DES_BLOCK_SIZE);

		DES_ecb_encrypt(&input, &output, &schedule, DES_DECRYPT);
		memcpy(&(pOutput[i * DES_BLOCK_SIZE]), output, DES_BLOCK_SIZE);
	}

	//remove padding for decryption
	int nLen = RemovePadding(pOutput, nSrcLen, paddingScheme);
	if(nLen <= 0 || nDecryptLen < nLen) {
		if(pOutput) delete []pOutput;
		return 0;
	}

	memcpy(pDecrypted, pOutput, nLen);
	if(pOutput)
		delete []pOutput;
	return nLen;
}

int YCrypto_DES::DES_ECB_Encrypt(const_DES_cblock* pKey, const unsigned char *pSrc, int nSrcLen, unsigned char *pEncrypted, int nEncryptLen, int paddingScheme)
{
	DES_key_schedule schedule;
	DES_set_key_unchecked(pKey, &schedule);

	//padding for encryption
	int nLen = (nSrcLen/DES_BLOCK_SIZE + 1) * DES_BLOCK_SIZE;
	unsigned char *pInput = new unsigned char[nLen];
	nLen = Padding(pSrc, nSrcLen, pInput, nLen, DES_BLOCK_SIZE, paddingScheme);

	if(nLen <= 0 || nEncryptLen < nLen) {
		if(pInput) delete []pInput;
		return 0;
	}

	//encrypt
	unsigned int nCount = nLen / DES_BLOCK_SIZE;
	DES_cblock input, output;
	for(unsigned int i=0; i<nCount; i++){
		memset(input, 0, DES_BLOCK_SIZE);
		memcpy(input, &(pInput[i * DES_BLOCK_SIZE]), DES_BLOCK_SIZE);
		memset(output, 0, DES_BLOCK_SIZE);

		DES_ecb_encrypt(&input, &output, &schedule, DES_ENCRYPT);
		memcpy(&(pEncrypted[i * DES_BLOCK_SIZE]), output, DES_BLOCK_SIZE);
	}
	if(pInput)
		delete []pInput;
	return nLen;
}

std::string YCrypto_DES::DESKeyToHexString(const_DES_cblock* pKey, bool isToUpperCase)
{
	return CharToHexString(reinterpret_cast<const void *>(pKey), DES_BLOCK_SIZE, isToUpperCase);
}

bool YCrypto_DES::HexStringToDESKey(const std::string& sSrc, bool isUpperCase, DES_cblock* pKey)
{
	if(sSrc.length() < DES_BLOCK_SIZE) return false;

	HexStringToChar(sSrc, isUpperCase, reinterpret_cast<char*>(pKey), DES_BLOCK_SIZE);
	return true;
}

std::string YCrypto_DES::DESKeyToString(const_DES_cblock* pKey)
{
	char key[DES_BLOCK_SIZE + 1];memset(key, 0, DES_BLOCK_SIZE + 1);
	memcpy(key, pKey, DES_BLOCK_SIZE);
	return std::string(key);
}

void YCrypto_DES::GetMD5AsKey(const std::string& sKey, DES_cblock* pKey)
{
	char MD5[33]; memset(MD5, 0, 33);
	YMD5::Update(sKey.c_str(), static_cast<unsigned int>(sKey.length()), MD5, 33, true);
	MD5[16] = '\0';

	HexStringToDESKey(std::string(MD5), true, pKey);
	DES_set_odd_parity(pKey);
}