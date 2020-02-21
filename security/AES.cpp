#include "pch.h"
#include "AES.h"
#include "CipherUtils.h"
#include "MD5.h"
#include "Base64.h"
#include <memory>
#include <vector>

bool YAes::AES64_CBC_Encrypt(const std::string& sKey, const std::string& sIv,  const std::string& sSrc, std::string& sEncrypted, int paddingScheme/*= padding_pkcs7*/, int nKeyBits/* = 128*/)
{
	const unsigned char* pSrc = reinterpret_cast<const unsigned char*>(sSrc.c_str());
	int nSrcLen = sSrc.length();
	return AES64_CBC_Encrypt(sKey, sIv, pSrc, nSrcLen, sEncrypted, paddingScheme, nKeyBits);
}

bool YAes::AES64_CBC_Encrypt(const std::string& sKey, const std::string& sIv,  const char* pSrc, int nSrcLen, std::string& sEncrypted, int paddingScheme/*= padding_pkcs7*/, int nKeyBits/* = 128*/)
{
	return AES64_CBC_Encrypt(sKey, sIv, reinterpret_cast<const unsigned char*>(pSrc), nSrcLen, sEncrypted, paddingScheme, nKeyBits);
}

int YAes::AES64_CBC_Decrypt(const std::string& sKey, const std::string& sIv,  const std::string sSrc, unsigned char *pDecrypted, int nDecryptLen, int paddingScheme/*= padding_pkcs7*/, int nKeyBits/* = 128*/)
{
	const unsigned char* pSrc = reinterpret_cast<const unsigned char*>(sSrc.c_str());
	int nSrcLen = sSrc.length();
	return AES64_CBC_Decrypt(sKey, sIv, pSrc, nSrcLen, pDecrypted, nDecryptLen, paddingScheme, nKeyBits);
}

int YAes::AES64_CBC_Decrypt(const std::string& sKey, const std::string& sIv,  const char* pSrc, int nSrcLen, unsigned char *pDecrypted, int nDecryptLen, int paddingScheme/*= padding_pkcs7*/, int nKeyBits/* = 128*/)
{
	return AES64_CBC_Decrypt(sKey, sIv, reinterpret_cast<const unsigned char*>(pSrc), nSrcLen, pDecrypted, nDecryptLen, paddingScheme, nKeyBits);
}

int YAes::AES64_CBC_Decrypt(const std::string& sKey, const std::string& sIv,  const std::string sSrc, std::string& sDecrypted, int paddingScheme/*= padding_pkcs7*/, int nKeyBits/* = 128*/)
{
	const unsigned char* pSrc = reinterpret_cast<const unsigned char*>(sSrc.c_str());
	int nSrcLen = sSrc.length();
	return AES64_CBC_Decrypt(sKey, sIv, pSrc, nSrcLen, sDecrypted, paddingScheme, nKeyBits);
}

int YAes::AES64_CBC_Decrypt(const std::string& sKey, const std::string& sIv,  const char* pSrc, int  nSrcLen, std::string& sDecrypted, int paddingScheme/*= padding_pkcs7*/, int nKeyBits/* = 128*/)
{
	return AES64_CBC_Decrypt(sKey, sIv, reinterpret_cast<const unsigned char*>(pSrc), nSrcLen, sDecrypted, paddingScheme, nKeyBits);
}

int YAes::AES64_CBC_Decrypt(const std::string& sKey, const std::string& sIv,  const unsigned char* pSrc, int  nSrcLen, std::string& sDecrypted, int paddingScheme/*= padding_pkcs7*/, int nKeyBits/* = 128*/)
{
	std::vector<unsigned char> decryptedVec(nSrcLen, 0);

	int nLen(0);
	nLen = AES64_CBC_Decrypt(sKey, sIv, pSrc, nSrcLen, &decryptedVec[0], nSrcLen, paddingScheme, nKeyBits);
	if(nLen > 0)
		sDecrypted = std::string(reinterpret_cast<char *>(&decryptedVec[0]), nLen);

	return nLen;
}

int YAes::AES_CBC_Encrypt(const std::string& sKey, const std::string& sIv, const std::string& sSrc, unsigned char *pEncrypted, int nEncryptLen, int paddingScheme/*= padding_pkcs7*/, int nKeyBits/* = 128*/)
{
	const unsigned char* pSrc = reinterpret_cast<const unsigned char*>(sSrc.c_str());
	int nSrcLen = sSrc.length();
	return AES_CBC_Encrypt(sKey, sIv, pSrc, nSrcLen, pEncrypted, nEncryptLen, paddingScheme, nKeyBits);
}

int YAes::AES_CBC_Encrypt(const std::string& sKey, const std::string& sIv, const char* pSrc, int nSrcLen, unsigned char *pEncrypted, int nEncryptLen, int paddingScheme/*= padding_pkcs7*/, int nKeyBits/* = 128*/)
{
	return AES_CBC_Encrypt(sKey, sIv, reinterpret_cast<const unsigned char*>(pSrc), nSrcLen, pEncrypted, nEncryptLen, paddingScheme, nKeyBits);
}

int YAes::AES_CBC_Decrypt(const std::string& sKey, const std::string& sIv, const std::string& sSrc, unsigned char *pDecrypted, int nDecryptLen, int paddingScheme/*= padding_pkcs7*/, int nKeyBits/* = 128*/)
{
	const unsigned char* pSrc = reinterpret_cast<const unsigned char*>(sSrc.c_str());
	int nSrcLen = sSrc.length();
	return AES_CBC_Decrypt(sKey, sIv, pSrc, nSrcLen, pDecrypted, nDecryptLen, paddingScheme, nKeyBits);
}

int YAes::AES_CBC_Decrypt(const std::string& sKey, const std::string& sIv, const char* pSrc, int nSrcLen, unsigned char *pDecrypted, int nDecryptLen, int paddingScheme/*= padding_pkcs7*/, int nKeyBits/* = 128*/)
{
	return AES_CBC_Decrypt(sKey, sIv, reinterpret_cast<const unsigned char*>(pSrc), nSrcLen, pDecrypted, nDecryptLen, paddingScheme, nKeyBits);
}

bool YAes::AES64_CBC_Encrypt(const std::string& sKey, const std::string& sIv,  const unsigned char* pSrc, int nSrcLen, std::string& sEncrypted, int paddingScheme/*= padding_pkcs7*/, int nKeyBits/* = 128*/)
{
	if(sKey.length() < AES_BLOCK_SIZE || sIv.length() < AES_BLOCK_SIZE) return false;

	AES_KEY key = {};
	if(0 != AES_set_encrypt_key(reinterpret_cast<const unsigned char*>(sKey.c_str()), nKeyBits, &key)) return false;	

	AES_cblock iv = {};
	memcpy(&iv, sIv.data(), AES_BLOCK_SIZE);

	//padding for encryption
	unsigned int nLen = (nSrcLen/AES_BLOCK_SIZE + 1) * AES_BLOCK_SIZE;
	std::vector<unsigned char> inputVec(nLen, 0);
	nLen = Padding(pSrc, nSrcLen, &inputVec[0], nLen, AES_BLOCK_SIZE, paddingScheme);
	if(nLen <= 0) 
		return false;

	std::vector<unsigned char> outputVec(nLen, 0);

	//encrypt
	AES_cbc_encrypt(&inputVec[0], &outputVec[0], nLen, &key, iv, AES_ENCRYPT);
	YBase64::Encode(&outputVec[0], nLen, sEncrypted);

	return true;
}

int YAes::AES64_CBC_Decrypt(const std::string& sKey, const std::string& sIv,  const unsigned char* pSrc, int nSrcLen, unsigned char *pDecrypted, int nDecryptLen, int paddingScheme/*= padding_pkcs7*/, int nKeyBits/* = 128*/)
{
	if(sKey.length() < AES_BLOCK_SIZE || sIv.length() < AES_BLOCK_SIZE) return 0;

	AES_KEY key = {};
	if(0 != AES_set_decrypt_key(reinterpret_cast<const unsigned char*>(sKey.c_str()), nKeyBits, &key)) return 0;

	AES_cblock iv = {};
	memcpy(&iv, sIv.c_str(), AES_BLOCK_SIZE);

	//prepare buffer size = nSrcLen, because base64 decode result has a less length
	std::vector<unsigned char> inputVec(nSrcLen, 0);

	int nLen(0);
	nLen = YBase64::Decode(pSrc, nSrcLen, &inputVec[0], nSrcLen);
	if(nLen <= 0 || nDecryptLen < nLen)
		return 0;

	int nOutLen = AES_CBC_Decrypt(sKey, sIv, &inputVec[0], nLen, pDecrypted, nDecryptLen, paddingScheme, nKeyBits);
	return nOutLen;
}

int YAes::AES_CBC_Encrypt(const std::string& sKey, const std::string& sIv, const unsigned char* pSrc, int nSrcLen, unsigned char *pEncrypted, int nEncryptLen, int paddingScheme/*= padding_pkcs7*/, int nKeyBits/* = 128*/)
{
	if(sKey.length() < AES_BLOCK_SIZE || sIv.length() < AES_BLOCK_SIZE) return 0;

	AES_KEY key = {};
	if(0 != AES_set_encrypt_key(reinterpret_cast<const unsigned char*>(sKey.c_str()), nKeyBits, &key)) return 0;	

	AES_cblock iv = {};
	memcpy(&iv, sIv.data(), AES_BLOCK_SIZE);

	//padding for encryption
	int nLen = (nSrcLen / AES_BLOCK_SIZE + 1) * AES_BLOCK_SIZE;
	std::vector<unsigned char> inputVec(nLen, 0);
	nLen = Padding(pSrc, nSrcLen, &inputVec[0], nLen, AES_BLOCK_SIZE, paddingScheme);
	if (nLen <= 0 || nEncryptLen < nLen)
		return 0;

	//encrypt
	AES_cbc_encrypt(&inputVec[0], pEncrypted, nLen, &key, iv, AES_ENCRYPT);
	return nLen;
}

int YAes::AES_CBC_Decrypt(const std::string& sKey, const std::string& sIv, const unsigned char* pSrc, int nSrcLen, unsigned char *pDecrypted, int nDecryptLen, int paddingScheme/*= padding_pkcs7*/, int nKeyBits/* = 128*/)
{
		if(sKey.length() < AES_BLOCK_SIZE || sIv.length() < AES_BLOCK_SIZE) return 0;
	
		AES_KEY key = {};
		if(0 != AES_set_decrypt_key(reinterpret_cast<const unsigned char*>(sKey.c_str()), nKeyBits, &key)) return 0;
	
		AES_cblock iv = {};
		memcpy(&iv, sIv.c_str(), AES_BLOCK_SIZE);
	
		std::vector<unsigned char> outputVec(nSrcLen, 0);

		//decrypt
		AES_cbc_encrypt(pSrc, &outputVec[0], nSrcLen, &key, iv, AES_DECRYPT);
		
		//remove padding for decryption
		unsigned int nLen = RemovePadding(&outputVec[0], nSrcLen, paddingScheme);
		if(nLen > 0)
			memcpy(pDecrypted, &outputVec[0], nLen);
	
		return nLen;
}

std::string YAes::AESKeyToHexString(const AES_KEY* pKey, bool isToUpperCase)
{
	return CharToHexString(reinterpret_cast<const void *>(pKey), AES_BLOCK_SIZE, isToUpperCase);
}

bool YAes::HexStringToAESKey(const std::string& sSrc, bool isUpperCase, AES_KEY* pKey)
{
	if(sSrc.length() < AES_BLOCK_SIZE) return false;

	HexStringToChar(sSrc, isUpperCase, reinterpret_cast<char*>(pKey), AES_BLOCK_SIZE);
	return true;
}

std::string YAes::AESKeyToString(const AES_KEY* pKey)
{
	char key[AES_BLOCK_SIZE + 1];memset(key, 0, AES_BLOCK_SIZE + 1);
	memcpy(key, pKey, AES_BLOCK_SIZE);
	return std::string(key);
}