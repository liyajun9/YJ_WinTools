#include "stdafx.h"
#include "YCrypto_AES.h"
#include "YCryptoUtils.h"
#include "YMD5.h"
#include "YBase64.h"

bool CYCrypto_AES::AES64_CBC_Encrypt(const std::string& sKey, const std::string& sIv,  const unsigned char* pSrc, int nSrcLen, std::string& sEncrypted, int paddingScheme/*= padding_pkcs7*/, int nKeyBits/* = 128*/)
{
	if(sKey.length() < AES_BLOCK_SIZE || sIv.length() < AES_BLOCK_SIZE) return false;

	AES_KEY key;
	if(0 != AES_set_encrypt_key(reinterpret_cast<const unsigned char*>(sKey.c_str()), nKeyBits, &key)) return false;	

	AES_cblock iv;
	memcpy(&iv, sIv.data(), AES_BLOCK_SIZE);

	//padding for encryption
	unsigned int nLen = (nSrcLen/AES_BLOCK_SIZE + 1) * AES_BLOCK_SIZE;
	unsigned char *pInput = new unsigned char[nLen]; memset(pInput, 0, nLen);
	nLen = Padding(pSrc, nSrcLen, pInput, nLen, AES_BLOCK_SIZE, paddingScheme);
	if(nLen <= 0) {
		if(pInput) delete []pInput;
		return false;
	}

	unsigned char *pOutput = new unsigned char[nLen]; memset(pOutput, 0, nLen);

	//encrypt
	AES_cbc_encrypt(pInput, pOutput, nLen, &key, iv, AES_ENCRYPT);
	CYBase64::Encode(pOutput, nLen, sEncrypted);

	if(pInput)	delete []pInput;
	if(pOutput) delete []pOutput;
	return true;
}

int CYCrypto_AES::AES64_CBC_Decrypt(const std::string& sKey, const std::string& sIv,  const std::string sSrc, unsigned char *pDecrypted, int nDecryptLen, int paddingScheme/*= padding_pkcs7*/, int nKeyBits/* = 128*/)
{
	if(sKey.length() < AES_BLOCK_SIZE || sIv.length() < AES_BLOCK_SIZE) return 0;

	AES_KEY key;
	if(0 != AES_set_decrypt_key(reinterpret_cast<const unsigned char*>(sKey.c_str()), nKeyBits, &key)) return 0;

	AES_cblock iv;
	memcpy(&iv, sIv.c_str(), AES_BLOCK_SIZE);

	int nLen = sSrc.length();
	unsigned char *pInput = new unsigned char[nLen]; memset(pInput, 0, nLen);
	nLen = CYBase64::Decode(sSrc, pInput, nLen);
	if(nLen <= 0 || nDecryptLen < nLen){
		if(pInput)	delete []pInput;
		return 0;
	}

	int nOutLen = AES_CBC_Decrypt(sKey, sIv, pInput, nLen, pDecrypted, nDecryptLen, paddingScheme, nKeyBits);
	if(pInput) delete []pInput;
	return nOutLen;
}

int CYCrypto_AES::AES64_CBC_Decrypt(const std::string& sKey, const std::string& sIv,  const std::string sSrc, std::string& sDecrypted, int paddingScheme/*= padding_pkcs7*/, int nKeyBits/* = 128*/)
{
	int nLen =sSrc.length();
	unsigned char *pDecrypted = new unsigned char[nLen]; memset(pDecrypted, 0, nLen);

	nLen = AES64_CBC_Decrypt(sKey, sIv, sSrc, pDecrypted, nLen, paddingScheme, nKeyBits);
	if(nLen > 0)
		sDecrypted = std::string(reinterpret_cast<char *>(pDecrypted), nLen);

	if(pDecrypted) delete []pDecrypted;
	return nLen;
}

int CYCrypto_AES::AES_CBC_Encrypt(const std::string& sKey, const std::string& sIv, const unsigned char* pSrc, int nSrcLen, unsigned char *pEncrypted, int nEncryptLen, int paddingScheme/*= padding_pkcs7*/, int nKeyBits/* = 128*/)
{
		if(sKey.length() < AES_BLOCK_SIZE || sIv.length() < AES_BLOCK_SIZE) return 0;
	
		AES_KEY key;
		if(0 != AES_set_encrypt_key(reinterpret_cast<const unsigned char*>(sKey.c_str()), nKeyBits, &key)) return 0;	
	
		AES_cblock iv;
		memcpy(&iv, sIv.data(), AES_BLOCK_SIZE);
		
		//padding for encryption
		int nLen = (nSrcLen/AES_BLOCK_SIZE + 1) * AES_BLOCK_SIZE;
		unsigned char *pInput = new unsigned char[nLen]; memset(pInput, 0, nLen);
		nLen = Padding(pSrc, nSrcLen, pInput, nLen, AES_BLOCK_SIZE, paddingScheme);
		if(nLen <= 0 || nEncryptLen < nLen) {
			if(pInput) delete []pInput;
			return 0;
		}
	
		//encrypt
		AES_cbc_encrypt(pInput, pEncrypted, nLen, &key, iv, AES_ENCRYPT);
	
		if(pInput)	delete []pInput;
		return nLen;
}

int CYCrypto_AES::AES_CBC_Decrypt(const std::string& sKey, const std::string& sIv, const unsigned char* pSrc, int nSrcLen, unsigned char *pDecrypted, int nDecryptLen, int paddingScheme/*= padding_pkcs7*/, int nKeyBits/* = 128*/)
{
		if(sKey.length() < AES_BLOCK_SIZE || sIv.length() < AES_BLOCK_SIZE) return 0;
	
		AES_KEY key;
		if(0 != AES_set_decrypt_key(reinterpret_cast<const unsigned char*>(sKey.c_str()), nKeyBits, &key)) return 0;
	
		AES_cblock iv;
		memcpy(&iv, sIv.c_str(), AES_BLOCK_SIZE);
	
		unsigned char *pOutput = new unsigned char[nSrcLen]; memset(pOutput, 0, nSrcLen);
		//decrypt
		AES_cbc_encrypt(pSrc, pOutput, nSrcLen, &key, iv, AES_DECRYPT);	
		
		//remove padding for decryption
		unsigned int nLen = RemovePadding(pOutput, nSrcLen, paddingScheme);
		if(nLen > 0)
			memcpy(pDecrypted, pOutput, nLen);
		if(pOutput) delete []pOutput;
	
		return nLen;
}

std::string CYCrypto_AES::AESKeyToHexString(const AES_KEY* pKey, bool isToUpperCase)
{
	return CharToHexString(reinterpret_cast<const void *>(pKey), AES_BLOCK_SIZE, isToUpperCase);
}

bool CYCrypto_AES::HexStringToAESKey(const std::string& sSrc, bool isUpperCase, AES_KEY* pKey)
{
	if(sSrc.length() < AES_BLOCK_SIZE) return false;

	HexStringToChar(sSrc, isUpperCase, reinterpret_cast<char*>(pKey), AES_BLOCK_SIZE);
	return true;
}

std::string CYCrypto_AES::AESKeyToString(const AES_KEY* pKey)
{
	char key[AES_BLOCK_SIZE + 1];memset(key, 0, AES_BLOCK_SIZE + 1);
	memcpy(key, pKey, AES_BLOCK_SIZE);
	return std::string(key);
}