#pragma once
#include <string>
#include <openssl/rsa.h>

class YSignature{
public:
	/*return: size of signature on success, 0 on failure*/
	static int RSA_MD5_Sign(const std::string& sPEMFilePath, const std::string& sMsg, std::string& sSign);	
	static int RSA_MD5_Sign(const std::string& sPEMFilePath, const char* pSrc, int nSrcLen, std::string& sSign);		
	static int RSA_MD5_Sign(const std::string& sPEMFilePath, const unsigned char* pSrc, int nSrcLen, std::string& sSign);					

	/*return: size of signature on success, 0 on failure*/
	static int RSA_MD5_SignVerify(const std::string& sPEMFilePath,  const std::string& sSign, const std::string& sMsg);	
	static int RSA_MD5_SignVerify(const std::string& sPEMFilePath,  const std::string& sSign, const char *pSrc, int nSrcLen); 
	static int RSA_MD5_SignVerify(const std::string& sPEMFilePath,  const std::string& sSign, const unsigned char *pSrc, int nSrcLen); 

private:
	YSignature();
	~YSignature();
};