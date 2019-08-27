#include "stdafx.h"
#include "YHash.h"
#include <openssl/md5.h>

#pragma warning(disable: 4996)
#pragma comment(lib,"libcrypto.lib")
#pragma comment(lib,"libssl.lib")

using namespace std;
std::string CYHash::CalcMD5(const std::string& sIn, size_t nLen, bool isToUpperCase)
{
	unsigned char MD[MD5_DIGEST_LENGTH]; memset(&MD, 0, MD5_DIGEST_LENGTH);
	MD5_CTX ctx = {0};
	MD5_Init(&ctx);
	MD5_Update(&ctx, sIn.c_str(), nLen);
	MD5_Final(MD, &ctx);

	char szTmp[33]; memset(szTmp, 0, 33);
	const char *fmt = isToUpperCase ? "%02X" : "%02x";
	for (unsigned int i = 0; i < 16; i++){
		sprintf(szTmp + i * 2, fmt, MD[i]);
	}
	string sOut = szTmp;
	return sOut;
}
void CYHash::CalcMD5(const std::string& sIn, size_t nLen, std::string& sOut,  bool isToUpperCase)
{
	unsigned char MD[MD5_DIGEST_LENGTH]; memset(&MD, 0, MD5_DIGEST_LENGTH);
	MD5_CTX ctx = {0};
	MD5_Init(&ctx);
	MD5_Update(&ctx, sIn.c_str(), nLen);
	MD5_Final(MD, &ctx);

	char szTmp[33]; memset(szTmp, 0, 33);
	const char *fmt = isToUpperCase ? "%02X" : "%02x";
	for (unsigned int  i = 0; i < 16; i++){
		sprintf(szTmp + i * 2, fmt, MD[i]);
	}
	sOut = szTmp;
}

void CYHash::CalcMD5(const void* pIn, unsigned int nCbLen, char* pszOut, unsigned int nCbOutLen, bool isToUpperCase)
{
	if(nCbOutLen < 33)	return;

	unsigned char MD[MD5_DIGEST_LENGTH]; memset(&MD, 0, MD5_DIGEST_LENGTH);
	MD5_CTX ctx = {0};
	MD5_Init(&ctx);
	MD5_Update(&ctx, pIn, nCbLen);
	MD5_Final(MD, &ctx);

	const char *fmt = isToUpperCase ? "%02X" : "%02x";
	for (unsigned int  i = 0; i < 16; i++){
		sprintf(pszOut + i * 2, fmt, MD[i]);
	}
}