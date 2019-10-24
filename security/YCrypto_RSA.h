//padding: PCKS#1 padding
#pragma once
#include <openssl/rsa.h>
#include <string>

class CYCrypto_RSA{
public:
	static bool PubKey_Encrypt64(const std::string& sPEMFilePath, const unsigned char* pSrc, int nSrcLen, std::string& sEncrypted);
	static bool PriKey_Decrypt64(const std::string& sPEMFilePath, const unsigned char *pSrc, int nSrcLen, std::string& sDecrypted);

public:
	static int PubKey_Encrypt(const std::string& sPEMFilePath, const unsigned char* pSrc, int nSrcLen, std::string& sEncrypted);
	static int PriKey_Decrypt(const std::string& sPEMFilePath, const unsigned char *pSrc, int nSrcLen, std::string& sDecrypted);

private:
	CYCrypto_RSA();
	~CYCrypto_RSA();
};