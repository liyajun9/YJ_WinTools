//padding: PCKS#1 padding
#pragma once
#include <openssl/rsa.h>
#include <string>

class YCrypto_RSA{
public: //with base64
	static bool PubKey_Encrypt64(const std::string& sPEMFilePath, const std::string& sSrc, std::string& sEncrypted);
	static bool PubKey_Encrypt64(const std::string& sPEMFilePath, const char* pSrc, int nSrcLen, std::string& sEncrypted);
	static bool PubKey_Encrypt64(const std::string& sPEMFilePath, const unsigned char* pSrc, int nSrcLen, std::string& sEncrypted);

	static bool PriKey_Decrypt64(const std::string& sPEMFilePath, const std::string& sSrc, std::string& sDecrypted);
	static bool PriKey_Decrypt64(const std::string& sPEMFilePath, const char *pSrc, int nSrcLen, std::string& sDecrypted);
	static bool PriKey_Decrypt64(const std::string& sPEMFilePath, const unsigned char *pSrc, int nSrcLen, std::string& sDecrypted);

public:
	static int PubKey_Encrypt(const std::string& sPEMFilePath, const std::string& sSrc, std::string& sEncrypted);
	static int PubKey_Encrypt(const std::string& sPEMFilePath, const char* pSrc, int nSrcLen, std::string& sEncrypted);
	static int PubKey_Encrypt(const std::string& sPEMFilePath, const unsigned char* pSrc, int nSrcLen, std::string& sEncrypted);

	static int PriKey_Decrypt(const std::string& sPEMFilePath, const std::string& sSrc, std::string& sDecrypted);
	static int PriKey_Decrypt(const std::string& sPEMFilePath, const char *pSrc, int nSrcLen, std::string& sDecrypted);
	static int PriKey_Decrypt(const std::string& sPEMFilePath, const unsigned char *pSrc, int nSrcLen, std::string& sDecrypted);

private:
	YCrypto_RSA();
	~YCrypto_RSA();
};