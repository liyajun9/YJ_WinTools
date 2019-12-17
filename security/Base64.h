#pragma once
#include <string>

#define BASE64_ENCODE_NEEDSIZE(x)	(x % 3 == 0 ? x / 3 * 4 : (x / 3 + 1) * 4)

class YBase64{
/*Fast-use methods*/
public:
	static std::string Encode(const unsigned char *pSrc, int nSrcLen);
	static std::string Encode(const std::string sSrc, int nSrcLen);

public:
	/*Encode: input binary array*/
	static void Encode(const unsigned char *pSrc, int nSrcLen, std::string& sEncoded);

	/*Encode: input text string*/
	static void Encode(const std::string sSrc, int nSrcLen, std::string& sEncoded);

	/*Decode
		return: 0 - decode failed.  > 0  length of output data
		remark: pDecoded should be big enough otherwise result will be truncated
	*/
	static int Decode(const std::string& sSrc, unsigned char* pDecoded, int nDecodedLen);

private:
	YBase64(){}
	~YBase64(){}

	static inline bool is_base64(unsigned char c)
	{
		return (isalnum(c) || (c == '+' || c == '/'));
	}
};