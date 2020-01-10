#include "stdafx.h"
#include "CryptoUtils.h"
#include "Crypto_DES.h"
#include "MD5.h"
#include "Base64.h"
#include <memory>

int YCrypto_DES::DES64_CBC_Decrypt_KeyMD5(const std::string& sKey, const std::string& sIv, const std::string& sSrc, std::string& sDecrypted, int paddingScheme/*= padding_scheme::padding_pkcs5*/)
{
	int nLen = sSrc.length() * 2;
	std::shared_ptr<unsigned char> spDecrypted(new unsigned char[nLen], std::default_delete<unsigned char[]>());
	memset(spDecrypted.get(), 0, nLen);

	nLen = DES64_CBC_Decrypt_KeyMD5(sKey, sIv, sSrc, spDecrypted.get(), nLen, paddingScheme);
	if(nLen > 0)
		sDecrypted = std::string(reinterpret_cast<char *>(spDecrypted.get()), nLen);

	return nLen;
}

int YCrypto_DES::DES64_CBC_Decrypt_KeyMD5(const std::string& sKey, const std::string& sIv, const std::string& sSrc, unsigned char *pDecrypted, int nDecryptLen, int paddingScheme/*= padding_scheme::padding_pkcs5*/)
{
	if(sKey.length() < DES_BLOCK_SIZE || sIv.length() < DES_BLOCK_SIZE) 
		return false;

	DES_cblock key = {}, iv = {};
	GetMD5AsKey(sKey, &key);
	memcpy(&iv, sIv.c_str(), DES_BLOCK_SIZE);

	return DES64_CBC_Decrypt(std::string(reinterpret_cast<char*>(&key)), std::string(reinterpret_cast<char *>(&iv)), sSrc, pDecrypted, nDecryptLen, paddingScheme);
}

int YCrypto_DES::DES64_ECB_Decrypt_KeyMD5(const std::string& sKey, const std::string& sSrc,  std::string& sDecrypted, int paddingScheme/*= padding_scheme::padding_pkcs5*/)
{
	int nLen = sSrc.length();
	std::shared_ptr<unsigned char> spDecrypted(new unsigned char[nLen], std::default_delete<unsigned char[]>());
	memset(spDecrypted.get(), 0, nLen);

	nLen = DES64_ECB_Decrypt_KeyMD5(sKey,  sSrc, spDecrypted.get(), nLen, paddingScheme);
	if(nLen > 0)
		sDecrypted = std::string(reinterpret_cast<char *>(spDecrypted.get()), nLen);

	return nLen;
}

int YCrypto_DES::DES64_ECB_Decrypt_KeyMD5(const std::string& sKey, const std::string& sSrc, unsigned char *pDecrypted, int nDecryptLen, int paddingScheme/*= padding_scheme::padding_pkcs5*/)
{
	if(sKey.length() < DES_BLOCK_SIZE ) 
		return false;

	DES_cblock key = {};
	GetMD5AsKey(sKey, &key);

	return DES64_ECB_Decrypt(std::string(reinterpret_cast<char*>(&key)), sSrc, pDecrypted, nDecryptLen, paddingScheme);
}

bool YCrypto_DES::DES64_CBC_Encrypt_KeyMD5(const std::string& sKey, const std::string& sIv,const unsigned char *pSrc, int nSrcLen, std::string& sEncrypted,  int paddingScheme /*= padding_scheme::padding_pkcs5*/)
{
	if(sKey.length() < DES_BLOCK_SIZE || sIv.length() < DES_BLOCK_SIZE) 
		return false;

	DES_cblock key = {}, iv = {};
	GetMD5AsKey(sKey, &key);
	memcpy(&iv, sIv.c_str(), DES_BLOCK_SIZE);

	return DES64_CBC_Encrypt(std::string(reinterpret_cast<char *>(&key), DES_BLOCK_SIZE), std::string(reinterpret_cast<char *>(&iv), DES_BLOCK_SIZE), pSrc, nSrcLen, sEncrypted, paddingScheme);
}

bool YCrypto_DES::DES64_ECB_Encrypt_KeyMD5(const std::string& sKey, const unsigned char *pSrc, int nSrcLen, std::string& sEncrypted,  int paddingScheme/*= padding_scheme::padding_pkcs5*/)
{
	if(sKey.length() < DES_BLOCK_SIZE ) 
		return false;

	DES_cblock key = {};
	GetMD5AsKey(sKey, &key);

	return DES64_ECB_Encrypt(std::string(reinterpret_cast<char*>(&key)), pSrc, nSrcLen, sEncrypted, paddingScheme);
}

int YCrypto_DES::DES64_CBC_Decrypt(const std::string& sKey, const std::string& sIv, const std::string& sSrc, std::string& sDecrypted, int paddingScheme/*= padding_scheme::padding_pkcs5*/)
{
	const unsigned char* pSrc = reinterpret_cast<const unsigned char*>(sSrc.c_str());
	int nSrcLen = sSrc.length();

	return DES64_CBC_Decrypt(sKey, sIv, pSrc, nSrcLen, sDecrypted, paddingScheme);
}

int YCrypto_DES::DES64_CBC_Decrypt(const std::string& sKey, const std::string& sIv, const char* pSrc, int nSrcLen, std::string& sDecrypted, int paddingScheme/*= padding_scheme::padding_pkcs5*/)
{
	return DES64_CBC_Decrypt(sKey, sIv, reinterpret_cast<const unsigned char*>(pSrc), nSrcLen, sDecrypted, paddingScheme);
}

int YCrypto_DES::DES64_CBC_Decrypt(const std::string& sKey, const std::string& sIv, const unsigned char* pSrc, int nSrcLen, std::string& sDecrypted, int paddingScheme/*= padding_scheme::padding_pkcs5*/)
{
	//prepare buffer size = nSrcLen, because cipher length must less than plain length for DES64
	std::shared_ptr<unsigned char> spDecrypted(new unsigned char[nSrcLen], std::default_delete<unsigned char[]>());
	memset(spDecrypted.get(), 0, nSrcLen);

	int nLen(0);
	nLen = DES64_CBC_Decrypt(sKey, sIv, pSrc, nSrcLen, spDecrypted.get(), nLen, paddingScheme);
	if(nLen > 0)
		sDecrypted = std::string(reinterpret_cast<char *>(spDecrypted.get()), nLen);

	return nLen;
}

int YCrypto_DES::DES64_CBC_Decrypt(const std::string& sKey, const std::string& sIv,  const std::string& sSrc, unsigned char *pDecrypted, int nDecryptLen, int paddingScheme/*= padding_scheme::padding_pkcs5*/)
{
	const unsigned char* pSrc = reinterpret_cast<const unsigned char*>(sSrc.c_str());
	int nSrcLen = sSrc.length();

	return DES64_CBC_Decrypt(sKey, sIv, pSrc, nSrcLen, pDecrypted, nDecryptLen, paddingScheme);
}

int YCrypto_DES::DES64_CBC_Decrypt(const std::string& sKey, const std::string& sIv,  const char *pSrc, int nSrcLen, unsigned char *pDecrypted, int nDecryptLen, int paddingScheme/*= padding_scheme::padding_pkcs5*/)
{
	return DES64_CBC_Decrypt(sKey, sIv, reinterpret_cast<const unsigned char*>(pSrc), nSrcLen, pDecrypted, nDecryptLen, paddingScheme);
}

int YCrypto_DES::DES64_CBC_Decrypt(const std::string& sKey, const std::string& sIv,  const unsigned char *pSrc, int nSrcLen, unsigned char *pDecrypted, int nDecryptLen, int paddingScheme/*= padding_scheme::padding_pkcs5*/)
{
	if(sKey.length() < DES_BLOCK_SIZE || sIv.length() < DES_BLOCK_SIZE) 
		return 0;

	DES_cblock key = {}, iv = {};
	memcpy(&key, sKey.c_str(), DES_BLOCK_SIZE);
	memcpy(&iv, sIv.c_str(), DES_BLOCK_SIZE);
	DES_key_schedule schedule;
	DES_set_key_unchecked(&key, &schedule);

	//prepare buffer size = nSrcLen for base64 decode result
	std::shared_ptr<unsigned char> spInput(new unsigned char[nSrcLen], std::default_delete<unsigned char[]>());
	memset(spInput.get(), 0, nSrcLen);
	int nLen(0);
	nLen = YBase64::Decode(pSrc, nSrcLen, spInput.get(), nSrcLen);
	if(nLen <= 0 || nDecryptLen < nLen)
		return 0;

	//decrypt
	int nOutLen = DES_CBC_Decrypt(&key, &iv, spInput.get(), nLen, pDecrypted, nDecryptLen, paddingScheme);

	return nOutLen;
}

int YCrypto_DES::DES64_ECB_Decrypt(const std::string& sKey, const std::string& sSrc,  std::string& sDecrypted, int paddingScheme/*= padding_scheme::padding_pkcs5*/)
{
	const unsigned char* pSrc = reinterpret_cast<const unsigned char*>(sSrc.c_str());
	int nSrcLen = sSrc.length();

	return DES64_ECB_Decrypt(sKey, pSrc, nSrcLen, sDecrypted, paddingScheme);
}

int YCrypto_DES::DES64_ECB_Decrypt(const std::string& sKey, const char* pSrc, int nSrcLen,  std::string& sDecrypted, int paddingScheme/*= padding_scheme::padding_pkcs5*/)
{
	return DES64_ECB_Decrypt(sKey, reinterpret_cast<const unsigned char*>(pSrc), nSrcLen, sDecrypted, paddingScheme);
}

int YCrypto_DES::DES64_ECB_Decrypt(const std::string& sKey, const unsigned char* pSrc, int nSrcLen,  std::string& sDecrypted, int paddingScheme/*= padding_scheme::padding_pkcs5*/)
{
	//prepare buffer size = nSrcLen, because cipher length must less than plain length for DES64
	std::shared_ptr<unsigned char> spDecrypted(new unsigned char[nSrcLen], std::default_delete<unsigned char[]>());
	memset(spDecrypted.get(), 0, nSrcLen);

	int nLen(0);
	nLen = DES64_ECB_Decrypt(sKey,  pSrc, nSrcLen, spDecrypted.get(), nSrcLen, paddingScheme);
	if(nLen > 0)
		sDecrypted = std::string(reinterpret_cast<char *>(spDecrypted.get()), nLen);

	return nLen;
}

int YCrypto_DES::DES64_ECB_Decrypt(const std::string& sKey, const std::string& sSrc, unsigned char *pDecrypted, int nDecryptLen, int paddingScheme /*= padding_pkcs5*/)
{
	const unsigned char* pSrc = reinterpret_cast<const unsigned char*>(sSrc.c_str());
	int nSrcLen = sSrc.length();

	return DES64_ECB_Decrypt(sKey, pSrc, nSrcLen, pDecrypted, nDecryptLen, paddingScheme);
}

int YCrypto_DES::DES64_ECB_Decrypt(const std::string& sKey, const char* pSrc, int nSrcLen, unsigned char *pDecrypted, int nDecryptLen, int paddingScheme /*= padding_pkcs5*/)
{
	return DES64_ECB_Decrypt(sKey, reinterpret_cast<const unsigned char*>(pSrc), nSrcLen, pDecrypted, nDecryptLen, paddingScheme);
}

int YCrypto_DES::DES64_ECB_Decrypt(const std::string& sKey, const unsigned char* pSrc, int nSrcLen, unsigned char *pDecrypted, int nDecryptLen, int paddingScheme/*= padding_scheme::padding_pkcs5*/)
{
	if(sKey.length() < DES_BLOCK_SIZE) 
		return 0;

	//prepare buffer size = nSrcLen, because base64 decode result has a less length
	std::shared_ptr<unsigned char> spInput(new unsigned char[nSrcLen], std::default_delete<unsigned char[]>());
	memset(spInput.get(), 0, nSrcLen);
	int nLen(0); 
	nLen = YBase64::Decode(pSrc, nSrcLen, spInput.get(), nSrcLen); 
	if(nLen <= 0 || nDecryptLen < nLen)
		return 0;

	DES_cblock key = {};
	memcpy(&key, sKey.c_str(), DES_BLOCK_SIZE);

	int nOutLen = DES_ECB_Decrypt(&key, spInput.get(), nLen, pDecrypted, nDecryptLen, paddingScheme);

	return nOutLen;
}

bool YCrypto_DES::DES64_CBC_Encrypt(const std::string& sKey, const std::string& sIv, const std::string& sSrc, std::string& sEncrypted,  int paddingScheme /*= padding_pkcs5*/)
{
	const unsigned char* pSrc = reinterpret_cast<const unsigned char*>(sSrc.c_str());
	int nSrcLen = sSrc.length();

	return DES64_CBC_Encrypt(sKey, sIv, pSrc, nSrcLen, sEncrypted, paddingScheme);
}

bool YCrypto_DES::DES64_CBC_Encrypt(const std::string& sKey, const std::string& sIv, const char *pSrc, int nSrcLen, std::string& sEncrypted,  int paddingScheme /*= padding_pkcs5*/)
{
	return DES64_CBC_Encrypt(sKey, sIv, reinterpret_cast<const unsigned char*>(pSrc), nSrcLen, sEncrypted, paddingScheme);
}

bool YCrypto_DES::DES64_CBC_Encrypt(const std::string& sKey, const std::string& sIv,const unsigned char *pSrc, int nSrcLen, std::string& sEncrypted,  int paddingScheme/*= padding_scheme::padding_pkcs5*/)
{
	if(sKey.length() < DES_BLOCK_SIZE || sIv.length() < DES_BLOCK_SIZE) return false;

	DES_cblock key = {}, iv = {};
	memcpy(&key, sKey.c_str(), DES_BLOCK_SIZE);
	memcpy(&iv, sIv.c_str(), DES_BLOCK_SIZE);
	DES_key_schedule schedule;
	DES_set_key_unchecked(&key, &schedule);

	//padding for encryption
	unsigned int nLen  = (nSrcLen/DES_BLOCK_SIZE + 1) * DES_BLOCK_SIZE;
	std::shared_ptr<unsigned char> spInput(new unsigned char[nLen], std::default_delete<unsigned char[]>());
	nLen = Padding(pSrc, nSrcLen, spInput.get(), nLen, DES_BLOCK_SIZE, paddingScheme);
	if(nLen <= 0) 
		return false;

	std::shared_ptr<unsigned char> spOutput(new unsigned char[nLen], std::default_delete<unsigned char[]>());
	memset(spOutput.get(), 0, nLen);

	//decrypt
	DES_cbc_encrypt(spInput.get(), spOutput.get(), nLen, &schedule, &iv, DES_ENCRYPT);

	YBase64::Encode(spOutput.get(), nLen, sEncrypted);

	return true;
}

bool YCrypto_DES::DES64_ECB_Encrypt(const std::string& sKey, const std::string& sSrc, std::string& sEncrypted,  int paddingScheme /*= padding_pkcs5*/)
{
	const unsigned char* pSrc = reinterpret_cast<const unsigned char*>(sSrc.c_str());
	int nSrcLen = sSrc.length();

	return DES64_ECB_Encrypt(sKey, pSrc, nSrcLen, sEncrypted, paddingScheme);
}

bool YCrypto_DES::DES64_ECB_Encrypt(const std::string& sKey, const char *pSrc, int nSrcLen, std::string& sEncrypted,  int paddingScheme /*= padding_pkcs5*/)
{
	return DES64_ECB_Encrypt(sKey, reinterpret_cast<const unsigned char*>(pSrc), nSrcLen, sEncrypted, paddingScheme);
}

bool YCrypto_DES::DES64_ECB_Encrypt(const std::string& sKey, const unsigned char *pSrc, int nSrcLen, std::string& sEncrypted,  int paddingScheme/*= padding_scheme::padding_pkcs5*/)
{
	if(sKey.length() < DES_BLOCK_SIZE) 
		return false;

	DES_cblock key = {};
	memcpy(&key, sKey.c_str(), DES_BLOCK_SIZE);
	DES_key_schedule schedule;
	DES_set_key_unchecked(&key, &schedule);

	//padding
	unsigned int nLen = (nSrcLen / DES_BLOCK_SIZE + 1) * DES_BLOCK_SIZE;
	std::shared_ptr<unsigned char> spInput(new unsigned char[nLen], std::default_delete<unsigned char[]>());
	nLen = Padding(pSrc, nSrcLen, spInput.get(), nLen, DES_BLOCK_SIZE, paddingScheme);
	if(nLen <= 0)
		return false;

	std::shared_ptr<unsigned char> spEncrypted(new unsigned char[nLen], std::default_delete<unsigned char[]>());

	//encrypt
	unsigned int nCount = nLen / DES_BLOCK_SIZE;
	DES_cblock input = {}, output = {};
	for(unsigned int i=0; i<nCount; i++){
		memcpy(input, &(spInput.get()[i * DES_BLOCK_SIZE]), DES_BLOCK_SIZE);
		DES_ecb_encrypt(&input, &output, &schedule, DES_ENCRYPT);
		memcpy(&(spEncrypted.get()[i * DES_BLOCK_SIZE]), output, DES_BLOCK_SIZE);
	}

	YBase64::Encode(spEncrypted.get(), nLen, sEncrypted);

	return true;
}

int YCrypto_DES::DES_CBC_Decrypt(const std::string& sKey, const std::string& sIv, const std::string& sSrc, unsigned char *pDecrypted, int nDecryptLen, int paddingScheme/*= padding_scheme::padding_pkcs5*/)
{
	const unsigned char* pSrc = reinterpret_cast<const unsigned char*>(sSrc.c_str());
	int nSrcLen = sSrc.length();

	return DES_CBC_Decrypt(sKey, sIv, pSrc, nSrcLen, pDecrypted, nDecryptLen, paddingScheme);
}

int YCrypto_DES::DES_CBC_Decrypt(const std::string& sKey, const std::string& sIv, const char *pSrc, int nSrcLen, unsigned char *pDecrypted, int nDecryptLen, int paddingScheme/*= padding_scheme::padding_pkcs5*/)
{
	return DES_CBC_Decrypt(sKey, sIv, reinterpret_cast<const unsigned char*>(pSrc), nSrcLen, pDecrypted, nDecryptLen, paddingScheme);
}

int YCrypto_DES::DES_CBC_Decrypt(const std::string& sKey, const std::string& sIv, const unsigned char *pSrc, int nSrcLen, unsigned char *pDecrypted, int nDecryptLen, int paddingScheme/*= padding_scheme::padding_pkcs5*/)
{
	if(sKey.length() < DES_BLOCK_SIZE || sIv.length() < DES_BLOCK_SIZE)
		return 0;

	DES_cblock desKey = {};
	DES_cblock desIv = {};
	memcpy(&desKey, sKey.data(), DES_BLOCK_SIZE);
	memcpy(&desIv, sIv.data(), DES_BLOCK_SIZE);

	return DES_CBC_Decrypt(&desKey, &desIv, pSrc, nSrcLen, pDecrypted, nDecryptLen, paddingScheme);
}

int YCrypto_DES::DES_CBC_Decrypt(const_DES_cblock* pKey, DES_cblock* pIv, const unsigned char *pSrc, int nSrcLen, unsigned char *pDecrypted, int nDecryptLen, int paddingScheme/*= padding_scheme::padding_pkcs5*/)
{
	DES_key_schedule schedule;
	DES_set_key_unchecked(pKey, &schedule);

	//decrypt
	std::shared_ptr<unsigned char> spOutput(new unsigned char[nSrcLen], std::default_delete<unsigned char[]>());

	DES_cbc_encrypt(pSrc, spOutput.get(), nSrcLen, &schedule, pIv, DES_DECRYPT);

	//remove padding for decryption
	int nLen = RemovePadding(spOutput.get(), nSrcLen, paddingScheme);
	if(nLen <= 0 || nDecryptLen < nLen) 
		return 0;

	memcpy(pDecrypted, spOutput.get(), nLen);

	return nLen;
}

int YCrypto_DES::DES_ECB_Decrypt(const std::string& sKey, const std::string& sSrc, unsigned char *pDecrypted, int nDecryptLen, int paddingScheme/*= padding_scheme::padding_pkcs5*/)
{
	const unsigned char* pSrc = reinterpret_cast<const unsigned char*>(sSrc.c_str());
	int nSrcLen = sSrc.length();

	return DES_ECB_Decrypt(sKey, pSrc, nSrcLen, pDecrypted, nDecryptLen, paddingScheme);
}

int YCrypto_DES::DES_ECB_Decrypt(const std::string& sKey, const char *pSrc, int nSrcLen, unsigned char *pDecrypted, int nDecryptLen, int paddingScheme/*= padding_scheme::padding_pkcs5*/)
{
	return DES_ECB_Decrypt(sKey, reinterpret_cast<const unsigned char*>(pSrc), nSrcLen, pDecrypted, nDecryptLen, paddingScheme);
}

int YCrypto_DES::DES_ECB_Decrypt(const std::string& sKey, const unsigned char *pSrc, int nSrcLen, unsigned char *pDecrypted, int nDecryptLen, int paddingScheme/*= padding_scheme::padding_pkcs5*/)
{
	if(sKey.length() < DES_BLOCK_SIZE)
		return 0;

	DES_cblock desKey = {};
	memcpy(&desKey, sKey.data(), DES_BLOCK_SIZE);

	return DES_ECB_Decrypt(&desKey, pSrc, nSrcLen, pDecrypted, nDecryptLen, paddingScheme);
}

int YCrypto_DES::DES_ECB_Decrypt(const_DES_cblock* pKey, const unsigned char *pSrc, int nSrcLen, unsigned char *pDecrypted, int nDecryptLen, int paddingScheme/*= padding_scheme::padding_pkcs5*/)
{
	DES_key_schedule schedule;
	DES_set_key_unchecked(pKey, &schedule);

	std::shared_ptr<unsigned char> spOutput(new unsigned char[nSrcLen], std::default_delete<unsigned char[]>());
	memset(spOutput.get(), 0, nSrcLen);
	//decrypt
	unsigned int nCount = nSrcLen / DES_BLOCK_SIZE;

	DES_cblock input, output;
	for(unsigned int i=0; i<nCount; i++){
		memset(input, 0, DES_BLOCK_SIZE);
		memcpy(input, &(pSrc[i * DES_BLOCK_SIZE]), DES_BLOCK_SIZE);
		memset(output, 0, DES_BLOCK_SIZE);

		DES_ecb_encrypt(&input, &output, &schedule, DES_DECRYPT);
		memcpy(&(spOutput.get()[i * DES_BLOCK_SIZE]), output, DES_BLOCK_SIZE);
	}

	//remove padding for decryption
	int nLen = RemovePadding(spOutput.get(), nSrcLen, paddingScheme);
	if(nLen <= 0 || nDecryptLen < nLen) 
		return 0;

	memcpy(pDecrypted, spOutput.get(), nLen);
	return nLen;
}

int YCrypto_DES::DES_CBC_Encrypt(const std::string& sKey, const std::string& sIv, const std::string& sSrc, unsigned char *pEncrypted, int nEncryptLen, int paddingScheme/*= padding_scheme::padding_pkcs5*/)
{
	const unsigned char* pSrc = reinterpret_cast<const unsigned char*>(sSrc.c_str());
	int nSrcLen = sSrc.length();

	return DES_CBC_Encrypt(sKey, sIv, pSrc, nSrcLen, pEncrypted, nEncryptLen, paddingScheme);
}

int YCrypto_DES::DES_CBC_Encrypt(const std::string& sKey, const std::string& sIv, const char *pSrc, int nSrcLen, unsigned char *pEncrypted, int nEncryptLen, int paddingScheme/*= padding_scheme::padding_pkcs5*/)
{
	return DES_CBC_Encrypt(sKey, sIv, reinterpret_cast<const unsigned char*>(pSrc), nSrcLen, pEncrypted, nEncryptLen, paddingScheme);
}

int YCrypto_DES::DES_CBC_Encrypt(const std::string& sKey, const std::string& sIv, const unsigned char *pSrc, int nSrcLen, unsigned char *pEncrypted, int nEncryptLen, int paddingScheme/*= padding_scheme::padding_pkcs5*/)
{
	if(sKey.length() < DES_BLOCK_SIZE || sIv.length() < DES_BLOCK_SIZE)
		return 0;

	DES_cblock desKey = {};
	DES_cblock desIv = {};
	memcpy(&desKey, sKey.data(), DES_BLOCK_SIZE);
	memcpy(&desIv, sIv.data(), DES_BLOCK_SIZE);

	return DES_CBC_Encrypt(&desKey, &desIv, pSrc, nSrcLen, pEncrypted, nEncryptLen, paddingScheme);
}

int YCrypto_DES::DES_CBC_Encrypt(DES_cblock* pKey, DES_cblock* pIv, const unsigned char *pSrc, int nSrcLen, unsigned char *pEncrypted, int nEncryptLen, int paddingScheme/*= padding_scheme::padding_pkcs5*/)
{
	DES_key_schedule schedule;
	DES_set_key_unchecked(pKey, &schedule);

	//padding for encryption
	int nLen  = (nSrcLen/DES_BLOCK_SIZE + 1) * DES_BLOCK_SIZE;
	std::shared_ptr<unsigned char> spInput(new unsigned char[nLen], std::default_delete<unsigned char[]>());
	nLen = Padding(pSrc, nSrcLen, spInput.get(), nLen, DES_BLOCK_SIZE, paddingScheme);
	if(nLen <= 0 || nEncryptLen < nLen)
		return 0;

	//encrypt
	DES_cbc_encrypt(spInput.get(), pEncrypted, nLen, &schedule, pIv, DES_ENCRYPT);

	return nLen;
}

int YCrypto_DES::DES_ECB_Encrypt(const std::string& sKey, const std::string& sSrc, unsigned char *pEncrypted, int nEncryptLen, int paddingScheme /*= padding_pkcs5*/)
{
	const unsigned char* pSrc = reinterpret_cast<const unsigned char*>(sSrc.c_str());
	int nSrcLen = sSrc.length();

	return DES_ECB_Encrypt(sKey, pSrc, nSrcLen, pEncrypted, nEncryptLen, paddingScheme);
}

int YCrypto_DES::DES_ECB_Encrypt(const std::string& sKey, const char *pSrc, int nSrcLen, unsigned char *pEncrypted, int nEncryptLen, int paddingScheme/* = padding_pkcs5*/)
{
	return DES_ECB_Encrypt(sKey, reinterpret_cast<const unsigned char*>(pSrc), nSrcLen, pEncrypted, nEncryptLen, paddingScheme);
}

int YCrypto_DES::DES_ECB_Encrypt(const std::string& sKey, const unsigned char *pSrc, int nSrcLen, unsigned char *pEncrypted, int nEncryptLen, int paddingScheme /*= padding_pkcs5*/)
{
	if(sKey.length() < DES_BLOCK_SIZE)
		return 0;

	DES_cblock desKey = {};
	memcpy(&desKey, sKey.data(), DES_BLOCK_SIZE);

	return DES_ECB_Encrypt(&desKey, pSrc, nSrcLen, pEncrypted, nEncryptLen, paddingScheme);
}

int YCrypto_DES::DES_ECB_Encrypt(const_DES_cblock* pKey, const unsigned char *pSrc, int nSrcLen, unsigned char *pEncrypted, int nEncryptLen, int paddingScheme/*= padding_scheme::padding_pkcs5*/)
{
	DES_key_schedule schedule;
	DES_set_key_unchecked(pKey, &schedule);

	//padding for encryption
	int nLen = (nSrcLen/DES_BLOCK_SIZE + 1) * DES_BLOCK_SIZE;
	std::shared_ptr<unsigned char> spInput(new unsigned char[nLen], std::default_delete<unsigned char[]>());
	nLen = Padding(pSrc, nSrcLen, spInput.get(), nLen, DES_BLOCK_SIZE, paddingScheme);

	if(nLen <= 0 || nEncryptLen < nLen) 
		return 0;

	//encrypt
	unsigned int nCount = nLen / DES_BLOCK_SIZE;
	DES_cblock input, output;
	for(unsigned int i=0; i<nCount; i++){
		memset(input, 0, DES_BLOCK_SIZE);
		memcpy(input, &(spInput.get()[i * DES_BLOCK_SIZE]), DES_BLOCK_SIZE);
		memset(output, 0, DES_BLOCK_SIZE);

		DES_ecb_encrypt(&input, &output, &schedule, DES_ENCRYPT);
		memcpy(&(pEncrypted[i * DES_BLOCK_SIZE]), output, DES_BLOCK_SIZE);
	}
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