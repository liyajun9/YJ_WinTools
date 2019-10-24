#pragma once
#include <string>
#include <openssl/rsa.h>

class CYCrypto_Sign{
public:
	static int RSA_MD5_Sign(const std::string& sPEMFilePath, const std::string& sMsg, std::string& sSign);							//return signature length
	static int RSA_MD5_SignVerify(const std::string& sPEMFilePath,  const std::string& sSign, const std::string& sMsg);	//return verify result 1:pass 0:fail

public:
	static int RSA_MD5_Sign(const std::string& sPEMFilePath, const unsigned char* pSrc, int nSrcLen, std::string& sSign);							//return signature length
	static int RSA_MD5_SignVerify(const std::string& sPEMFilePath,  const std::string& sSign, const unsigned char *pSrc, int nSrcLen); //return verify result 1:pass 0:fail

private:
	CYCrypto_Sign();
	~CYCrypto_Sign();
};