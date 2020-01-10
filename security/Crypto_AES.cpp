#include "stdafx.h"
#include "Crypto_AES.h"
#include "CryptoUtils.h"
#include "MD5.h"
#include "Base64.h"
#include <memory>

bool YCrypto_AES::AES64_CBC_Encrypt(const std::string& sKey, const std::string& sIv,  const std::string& sSrc, std::string& sEncrypted, int paddingScheme/*= padding_pkcs7*/, int nKeyBits/* = 128*/)
{
	const unsigned char* pSrc = reinterpret_cast<const unsigned char*>(sSrc.c_str());
	int nSrcLen = sSrc.length();
	return AES64_CBC_Encrypt(sKey, sIv, pSrc, nSrcLen, sEncrypted, paddingScheme, nKeyBits);
}

bool YCrypto_AES::AES64_CBC_Encrypt(const std::string& sKey, const std::string& sIv,  const char* pSrc, int nSrcLen, std::string& sEncrypted, int paddingScheme/*= padding_pkcs7*/, int nKeyBits/* = 128*/)
{
	return AES64_CBC_Encrypt(sKey, sIv, reinterpret_cast<const unsigned char*>(pSrc), nSrcLen, sEncrypted, paddingScheme, nKeyBits);
}

bool YCrypto_AES::AES64_CBC_Encrypt(const std::string& sKey, const std::string& sIv,  const unsigned char* pSrc, int nSrcLen, std::string& sEncrypted, int paddingScheme/*= padding_pkcs7*/, int nKeyBits/* = 128*/)
{
	if(sKey.length() < AES_BLOCK_SIZE || sIv.length() < AES_BLOCK_SIZE) return false;

	AES_KEY key;
	if(0 != AES_set_encrypt_key(reinterpret_cast<const unsigned char*>(sKey.c_str()), nKeyBits, &key)) return false;	

	AES_cblock iv;
	memcpy(&iv, sIv.data(), AES_BLOCK_SIZE);

	//padding for encryption
	unsigned int nLen = (nSrcLen/AES_BLOCK_SIZE + 1) * AES_BLOCK_SIZE;
	std::shared_ptr<unsigned char> spInput(new unsigned char[nLen], std::default_delete<unsigned char[]>());
	memset(spInput.get(), 0, nLen);
	nLen = Padding(pSrc, nSrcLen, spInput.get(), nLen, AES_BLOCK_SIZE, paddingScheme);
	if(nLen <= 0) 
		return false;

	std::shared_ptr<unsigned char> spOutput(new unsigned char[nLen], std::default_delete<unsigned char[]>());
	 memset(spOutput.get(), 0, nLen);

	//encrypt
	AES_cbc_encrypt(spInput.get(), spOutput.get(), nLen, &key, iv, AES_ENCRYPT);
	YBase64::Encode(spOutput.get(), nLen, sEncrypted);

	return true;
}

int YCrypto_AES::AES64_CBC_Decrypt(const std::string& sKey, const std::string& sIv,  const std::string sSrc, unsigned char *pDecrypted, int nDecryptLen, int paddingScheme/*= padding_pkcs7*/, int nKeyBits/* = 128*/)
{
	const unsigned char* pSrc = reinterpret_cast<const unsigned char*>(sSrc.c_str());
	int nSrcLen = sSrc.length();
	return AES64_CBC_Decrypt(sKey, sIv, pSrc, nSrcLen, pDecrypted, nDecryptLen, paddingScheme, nKeyBits);
}

int YCrypto_AES::AES64_CBC_Decrypt(const std::string& sKey, const std::string& sIv,  const char* pSrc, int nSrcLen, unsigned char *pDecrypted, int nDecryptLen, int paddingScheme/*= padding_pkcs7*/, int nKeyBits/* = 128*/)
{
	return AES64_CBC_Decrypt(sKey, sIv, reinterpret_cast<const unsigned char*>(pSrc), nSrcLen, pDecrypted, nDecryptLen, paddingScheme, nKeyBits);
}

int YCrypto_AES::AES64_CBC_Decrypt(const std::string& sKey, const std::string& sIv,  const unsigned char* pSrc, int nSrcLen, unsigned char *pDecrypted, int nDecryptLen, int paddingScheme/*= padding_pkcs7*/, int nKeyBits/* = 128*/)
{
	if(sKey.length() < AES_BLOCK_SIZE || sIv.length() < AES_BLOCK_SIZE) return 0;

	AES_KEY key;
	if(0 != AES_set_decrypt_key(reinterpret_cast<const unsigned char*>(sKey.c_str()), nKeyBits, &key)) return 0;

	AES_cblock iv;
	memcpy(&iv, sIv.c_str(), AES_BLOCK_SIZE);

	//prepare buffer size = nSrcLen, because base64 decode result has a less length
	std::shared_ptr<unsigned char> spInput(new unsigned char[nSrcLen], std::default_delete<unsigned char[]>());
	memset(spInput.get(), 0, nSrcLen);
	int nLen = YBase64::Decode(pSrc, nSrcLen, spInput.get(), nLen);
	if(nLen <= 0 || nDecryptLen < nLen)
		return 0;

	int nOutLen = AES_CBC_Decrypt(sKey, sIv, spInput.get(), nLen, pDecrypted, nDecryptLen, paddingScheme, nKeyBits);
	return nOutLen;
}

int YCrypto_AES::AES64_CBC_Decrypt(const std::string& sKey, const std::string& sIv,  const std::string sSrc, std::string& sDecrypted, int paddingScheme/*= padding_pkcs7*/, int nKeyBits/* = 128*/)
{
	const unsigned char* pSrc = reinterpret_cast<const unsigned char*>(sSrc.c_str());
	int nSrcLen = sSrc.length();
	return AES64_CBC_Decrypt(sKey, sIv, pSrc, nSrcLen, sDecrypted, paddingScheme, nKeyBits);
}

int YCrypto_AES::AES64_CBC_Decrypt(const std::string& sKey, const std::string& sIv,  const char* pSrc, int  nSrcLen, std::string& sDecrypted, int paddingScheme/*= padding_pkcs7*/, int nKeyBits/* = 128*/)
{
	return AES64_CBC_Decrypt(sKey, sIv, reinterpret_cast<const unsigned char*>(pSrc), nSrcLen, sDecrypted, paddingScheme, nKeyBits);
}

int YCrypto_AES::AES64_CBC_Decrypt(const std::string& sKey, const std::string& sIv,  const unsigned char* pSrc, int  nSrcLen, std::string& sDecrypted, int paddingScheme/*= padding_pkcs7*/, int nKeyBits/* = 128*/)
{
	std::shared_ptr<unsigned char> spDecrypted(new unsigned char[nSrcLen], std::default_delete<unsigned char[]>());
	memset(spDecrypted.get(), 0, nSrcLen);

	int nLen = AES64_CBC_Decrypt(sKey, sIv, pSrc, nSrcLen, spDecrypted.get(), nLen, paddingScheme, nKeyBits);
	if(nLen > 0)
		sDecrypted = std::string(reinterpret_cast<char *>(spDecrypted.get()), nLen);

	return nLen;
}

int YCrypto_AES::AES_CBC_Encrypt(const std::string& sKey, const std::string& sIv, const std::string& sSrc, unsigned char *pEncrypted, int nEncryptLen, int paddingScheme/*= padding_pkcs7*/, int nKeyBits/* = 128*/)
{
	const unsigned char* pSrc = reinterpret_cast<const unsigned char*>(sSrc.c_str());
	int nSrcLen = sSrc.length();
	return AES_CBC_Encrypt(sKey, sIv, pSrc, nSrcLen, pEncrypted, nEncryptLen, paddingScheme, nKeyBits);
}

int YCrypto_AES::AES_CBC_Encrypt(const std::string& sKey, const std::string& sIv, const char* pSrc, int nSrcLen, unsigned char *pEncrypted, int nEncryptLen, int paddingScheme/*= padding_pkcs7*/, int nKeyBits/* = 128*/)
{
	return AES_CBC_Encrypt(sKey, sIv, reinterpret_cast<const unsigned char*>(pSrc), nSrcLen, pEncrypted, nEncryptLen, paddingScheme, nKeyBits);
}

int YCrypto_AES::AES_CBC_Encrypt(const std::string& sKey, const std::string& sIv, const unsigned char* pSrc, int nSrcLen, unsigned char *pEncrypted, int nEncryptLen, int paddingScheme/*= padding_pkcs7*/, int nKeyBits/* = 128*/)
{
		if(sKey.length() < AES_BLOCK_SIZE || sIv.length() < AES_BLOCK_SIZE) return 0;
	
		AES_KEY key;
		if(0 != AES_set_encrypt_key(reinterpret_cast<const unsigned char*>(sKey.c_str()), nKeyBits, &key)) return 0;	
	
		AES_cblock iv;
		memcpy(&iv, sIv.data(), AES_BLOCK_SIZE);
		
		//padding for encryption
		int nLen = (nSrcLen/AES_BLOCK_SIZE + 1) * AES_BLOCK_SIZE;
		std::shared_ptr<unsigned char> spInput(new unsigned char[nLen], std::default_delete<unsigned char[]>());
		memset(spInput.get(), 0, nLen);
		nLen = Padding(pSrc, nSrcLen, spInput.get(), nLen, AES_BLOCK_SIZE, paddingScheme);
		if(nLen <= 0 || nEncryptLen < nLen) 
			return 0;
	
		//encrypt
		AES_cbc_encrypt(spInput.get(), pEncrypted, nLen, &key, iv, AES_ENCRYPT);
	
		return nLen;
}

int YCrypto_AES::AES_CBC_Decrypt(const std::string& sKey, const std::string& sIv, const std::string& sSrc, unsigned char *pDecrypted, int nDecryptLen, int paddingScheme/*= padding_pkcs7*/, int nKeyBits/* = 128*/)
{
	const unsigned char* pSrc = reinterpret_cast<const unsigned char*>(sSrc.c_str());
	int nSrcLen = sSrc.length();
	return AES_CBC_Decrypt(sKey, sIv, pSrc, nSrcLen, pDecrypted, nDecryptLen, paddingScheme, nKeyBits);
}

int YCrypto_AES::AES_CBC_Decrypt(const std::string& sKey, const std::string& sIv, const char* pSrc, int nSrcLen, unsigned char *pDecrypted, int nDecryptLen, int paddingScheme/*= padding_pkcs7*/, int nKeyBits/* = 128*/)
{
	return AES_CBC_Decrypt(sKey, sIv, reinterpret_cast<const unsigned char*>(pSrc), nSrcLen, pDecrypted, nDecryptLen, paddingScheme, nKeyBits);
}

int YCrypto_AES::AES_CBC_Decrypt(const std::string& sKey, const std::string& sIv, const unsigned char* pSrc, int nSrcLen, unsigned char *pDecrypted, int nDecryptLen, int paddingScheme/*= padding_pkcs7*/, int nKeyBits/* = 128*/)
{
		if(sKey.length() < AES_BLOCK_SIZE || sIv.length() < AES_BLOCK_SIZE) return 0;
	
		AES_KEY key;
		if(0 != AES_set_decrypt_key(reinterpret_cast<const unsigned char*>(sKey.c_str()), nKeyBits, &key)) return 0;
	
		AES_cblock iv;
		memcpy(&iv, sIv.c_str(), AES_BLOCK_SIZE);
	
		std::shared_ptr<unsigned char> spOutput(new unsigned char[nSrcLen], std::default_delete<unsigned char[]>());
		memset(spOutput.get(), 0, nSrcLen);
		//decrypt
		AES_cbc_encrypt(pSrc, spOutput.get(), nSrcLen, &key, iv, AES_DECRYPT);	
		
		//remove padding for decryption
		unsigned int nLen = RemovePadding(spOutput.get(), nSrcLen, paddingScheme);
		if(nLen > 0)
			memcpy(pDecrypted, spOutput.get(), nLen);
	
		return nLen;
}

std::string YCrypto_AES::AESKeyToHexString(const AES_KEY* pKey, bool isToUpperCase)
{
	return CharToHexString(reinterpret_cast<const void *>(pKey), AES_BLOCK_SIZE, isToUpperCase);
}

bool YCrypto_AES::HexStringToAESKey(const std::string& sSrc, bool isUpperCase, AES_KEY* pKey)
{
	if(sSrc.length() < AES_BLOCK_SIZE) return false;

	HexStringToChar(sSrc, isUpperCase, reinterpret_cast<char*>(pKey), AES_BLOCK_SIZE);
	return true;
}

std::string YCrypto_AES::AESKeyToString(const AES_KEY* pKey)
{
	char key[AES_BLOCK_SIZE + 1];memset(key, 0, AES_BLOCK_SIZE + 1);
	memcpy(key, pKey, AES_BLOCK_SIZE);
	return std::string(key);
}