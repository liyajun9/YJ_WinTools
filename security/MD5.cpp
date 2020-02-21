#include "pch.h"
#include "MD5.h"
#include <openssl/md5.h>

#pragma warning(disable: 4996)
#pragma comment(lib,"libcrypto.lib")
#pragma comment(lib,"libssl.lib")

std::string YMD5::Update(const std::string& sIn, bool toUpperCase /*= true*/)
{
	size_t nLen = sIn.length();
	return Update(sIn, nLen, toUpperCase);
}

std::string YMD5::Update(const std::string& sIn, size_t nLen, bool toUpperCase /*= true*/)
{
	unsigned char MD[MD5_DIGEST_LENGTH]; memset(&MD, 0, MD5_DIGEST_LENGTH);
	MD5_CTX ctx = {0};
	MD5_Init(&ctx);
	MD5_Update(&ctx, sIn.c_str(), nLen);
	MD5_Final(MD, &ctx);

	char szTmp[MD5_BUFFER_SIZE]; memset(szTmp, 0, MD5_BUFFER_SIZE);
	const char *fmt = toUpperCase ? "%02X" : "%02x";
	for (unsigned int i = 0; i < MD5_BUFFER_SIZE/2; i++){
		sprintf(szTmp + i * 2, fmt, MD[i]);
	}
	std::string sOut = szTmp;
	return sOut;
}

void YMD5::Update(const std::string& sIn, std::string& sOut,  bool toUpperCase/*= true*/)
{
	size_t nLen = sIn.length();
	Update(sIn, nLen, sOut, toUpperCase);
}

void YMD5::Update(const std::string& sIn, size_t nLen, std::string& sOut,  bool toUpperCase/*= true*/)
{
	unsigned char MD[MD5_DIGEST_LENGTH]; memset(&MD, 0, MD5_DIGEST_LENGTH);
	MD5_CTX ctx = {0};
	MD5_Init(&ctx);
	MD5_Update(&ctx, sIn.c_str(), nLen);
	MD5_Final(MD, &ctx);

	char szTmp[MD5_BUFFER_SIZE]; memset(szTmp, 0, MD5_BUFFER_SIZE);
	const char *fmt = toUpperCase ? "%02X" : "%02x";
	for (unsigned int  i = 0; i < MD5_BUFFER_SIZE/2; i++){
		sprintf(szTmp + i * 2, fmt, MD[i]);
	}
	sOut = szTmp;
}

void YMD5::Update(const void* pIn, unsigned int nCbLen, char* pszOut, unsigned int nCbOutLen, bool toUpperCase/*= true*/)
{
	if(nCbOutLen < MD5_BUFFER_SIZE)	return;

	unsigned char MD[MD5_DIGEST_LENGTH]; memset(&MD, 0, MD5_DIGEST_LENGTH);
	MD5_CTX ctx = {0};
	MD5_Init(&ctx);
	MD5_Update(&ctx, pIn, nCbLen);
	MD5_Final(MD, &ctx);

	const char *fmt = toUpperCase ? "%02X" : "%02x";
	for (unsigned int  i = 0; i < MD5_BUFFER_SIZE/2; i++){
		sprintf(pszOut + i * 2, fmt, MD[i]);
	}
}