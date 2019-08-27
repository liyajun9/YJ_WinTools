#include "stdafx.h"
#include "YCryptoUtils.h"
#include "YCrypto_DES.h"
#include "YHash.h"
#include "YEncodings.h"

std::string CYCrypto_DES::DESKeyToHexString(const DES_cblock* pKey, bool isToUpperCase)
{
	return CharToHexString(reinterpret_cast<const void *>(pKey), 8, isToUpperCase);
}

bool CYCrypto_DES::HexStringToDESKey(const std::string& sSrc, bool isUpperCase, DES_cblock* pKey)
{
	if(sSrc.length() < 8) return false;

	HexStringToChar(sSrc, isUpperCase, reinterpret_cast<char*>(pKey), 8);
	return true;
}

std::string CYCrypto_DES::DESKeyToString(const DES_cblock* pKey)
{
	char key[9];memset(key, 0, 9);
	memcpy(key, pKey, 8);
	return std::string(key);
}

void CYCrypto_DES::GenerateKeyLikeJava(const std::string& sKey, DES_cblock* pKey)
{
	char MD5[33]; memset(MD5, 0, 33);
	CYHash::CalcMD5(sKey.c_str(), static_cast<unsigned int>(sKey.length()), MD5, 33, true);
	MD5[16] = '\0';

	HexStringToDESKey(std::string(MD5), true, pKey);
	DES_set_odd_parity(pKey);
}

void CYCrypto_DES::DES64_CBC_JavaLike(const std::string& sKey, const std::string& sIv,const std::string& sInData, unsigned int nCbLen, std::string& sOutData, bool bEncrypt)
{
	if(sKey.length() < 8 || sIv.length() < 8) return;

	DES_cblock key, iv;
	GenerateKeyLikeJava(sKey, &key);
	memcpy(&iv, sIv.c_str(), 8);

	std::string sResult;
	if(bEncrypt){
		DES_CBC(&key, &iv, reinterpret_cast<const void*>(sInData.c_str()), nCbLen, sResult, bEncrypt, padding_pkcs5);
		CYEncodings::Base64_Encode(sResult, sOutData);
	}else{
		CYEncodings::Base64_Decode(sInData, sResult);
		DES_CBC(&key, &iv, reinterpret_cast<const void*>(sResult.c_str()), static_cast<unsigned int>(sResult.length()), sOutData, bEncrypt, padding_pkcs5);
	}
}

void CYCrypto_DES::DES64_CBC(const std::string& sKey, const std::string& sIv, const std::string& sInData, unsigned int nCbLen, std::string& sOutData, bool bEncrypt, int paddingScheme)
{
	if(sKey.length() < 8 || sIv.length() < 8) return;

	DES_cblock key, iv;
	memcpy(&key, sKey.c_str(), 8);
	memcpy(&iv, sIv.c_str(), 8);

	std::string sResult;
	if(bEncrypt){
		DES_CBC(&key, &iv, reinterpret_cast<const void*>(sInData.c_str()), nCbLen, sResult, bEncrypt, padding_pkcs5);
		CYEncodings::Base64_Encode(sResult, sOutData);
	}else{
		CYEncodings::Base64_Decode(sInData, sResult);
		DES_CBC(&key, &iv, reinterpret_cast<const void*>(sResult.c_str()), static_cast<unsigned int>(sResult.length()), sOutData, bEncrypt, padding_pkcs5);
	}
}

void CYCrypto_DES::DES_CBC(const std::string& sKey, const std::string& sIv, const std::string& sInData, unsigned int nCbLen, std::string& sOutData, bool bEncrypt, int paddingScheme)
{
	if(sKey.length() < 8 || sIv.length() < 8) return;

	DES_cblock key, iv;
	memcpy(&key, sKey.c_str(), 8);
	memcpy(&iv, sIv.c_str(), 8);
	DES_CBC(&key, &iv, reinterpret_cast<const void*>(sInData.c_str()), nCbLen, sOutData, bEncrypt, paddingScheme);
}

void CYCrypto_DES::DES_CBC(DES_cblock* pKey, DES_cblock* pIv,const void* pInData, unsigned int nCbLen, std::string& sOutData, bool bEncrypt, int paddingScheme)
{
	//key
	DES_key_schedule schedule;
	DES_set_key_unchecked(pKey, &schedule);

	//padding for encryption
	unsigned int nLen(0); 
	unsigned char *pInput(0);
	if(bEncrypt){
		nLen = nCbLen + 8 - nCbLen % 8; //DES block size is 8
		pInput = new unsigned char[nLen];
		Padding(pInData, nCbLen, pInput, nLen, 8, paddingScheme);
	}else{
		nLen = nCbLen;
		pInput = reinterpret_cast<unsigned char*>(const_cast<void*>(pInData));
	}

	//encrypt
	int nMode = bEncrypt ? DES_ENCRYPT : DES_DECRYPT;
	unsigned char *pOutput = new unsigned char[nLen + 1]; memset(pOutput, 0, nLen + 1);
	unsigned int nCount = nLen / 8;

	DES_cbc_encrypt(pInput, pOutput, nLen, &schedule, pIv, nMode);

	//remove padding for decryption
	if(!bEncrypt)
		RemovePadding(pOutput, nLen, paddingScheme);

	sOutData = reinterpret_cast<char*>(pOutput);

	if(bEncrypt && pInput)
		delete []pInput;
	if(pOutput)
		delete []pOutput;	
}

void CYCrypto_DES::DES64_ECB(const std::string& sKey, const std::string& sInData, unsigned int nCbLen, std::string& sOutData, bool bEncrypt, int paddingScheme)
{
	if(sKey.length() < 8) return;

	DES_cblock key;
	memcpy(&key, sKey.c_str(), 8);

	std::string sResult;
	if(bEncrypt){
		DES_ECB(&key, reinterpret_cast<const char*>(sInData.c_str()), nCbLen, sResult, bEncrypt, paddingScheme);
		CYEncodings::Base64_Encode(sResult, sOutData);
	}else{
		CYEncodings::Base64_Decode(sInData, sResult);
		DES_ECB(&key, reinterpret_cast<const char*>(sResult.c_str()), static_cast<unsigned int>(sResult.length()), sOutData, bEncrypt, paddingScheme);
	}
}

void CYCrypto_DES::DES_ECB(const std::string& sKey, const std::string& sInData, unsigned int nCbLen, std::string& sOutData, bool bEncrypt, int paddingScheme)
{
	if(sKey.length() < 8) return;

	DES_cblock key;
	memcpy(&key, sKey.c_str(), 8);
	DES_ECB(&key, reinterpret_cast<const char*>(sInData.c_str()), nCbLen, sOutData, bEncrypt, paddingScheme);
}

void CYCrypto_DES::DES_ECB(DES_cblock* pKey, const void* pInData, unsigned int nCbLen, std::string& sOutData, bool bEncrypt, int paddingScheme)
{
	//key
	DES_key_schedule schedule;
	DES_set_key_unchecked(pKey, &schedule);

	//padding for encryption
	unsigned int nLen(0); 
	unsigned char *pInput(0);
	if(bEncrypt){
		nLen = nCbLen + 8 - nCbLen % 8; //DES block size is 8
		pInput = new unsigned char[nLen];
		Padding(pInData, nCbLen, pInput, nLen, 8, paddingScheme);
	}else{
		nLen = nCbLen;
		pInput = reinterpret_cast<unsigned char*>(const_cast<void*>(pInData));
	}

	//encrypt
	int nMode = bEncrypt ? DES_ENCRYPT : DES_DECRYPT;
	unsigned char *pOutput = new unsigned char[nLen + 1]; memset(pOutput, 0, nLen + 1);
	unsigned int nCount = nLen / 8;

	DES_cblock input, output;
	for(unsigned int i=0; i<nCount; i++){
		memset(input, 0, 8);
		memcpy(input, &(pInput[i * 8]), 8);
		memset(output, 0, 8);

		DES_ecb_encrypt(&input, &output, &schedule, nMode);
		memcpy(&(pOutput[i * 8]), output, 8);
	}

	//remove padding for decryption
	if(!bEncrypt)
		RemovePadding(pOutput, nLen, paddingScheme);

	sOutData = reinterpret_cast<char*>(pOutput);

	if(bEncrypt && pInput)
		delete []pInput;
	if(pOutput)
		delete []pOutput;
}