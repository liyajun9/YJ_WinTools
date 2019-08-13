// Frequently used charset transfer tools
//	Support: MultiByte, UniCode, UTF8
// author:liyajun
#pragma once
#include <string>

class CYCharEncodings{
public:
	//input: std::string or std::wstring
	static std::string WCharToUtf8(const std::wstring& str);
	static std::string WCharToMB(const std::wstring& str);

	static std::string MBToUtf8(const std::string& str);
	static std::wstring MBToWChar(const std::string& str);

	static std::wstring Utf8ToWChar(const std::string& str);	
	static std::string Utf8ToMB(const std::string& str);

	//input: character-array and character-count(excluding the terminate)
	static int WCharToUtf8(const wchar_t *pWChar, int nCchWChar, char *pUtf8, int nCbUtf8);
	static int WCharToMB(const wchar_t *pWChar, int nCchWChar, char *pMB, int nCbMB);

	static int MBToUtf8(const char *pMB, int nCbMB, char *pUtf, int nCbUtf);
	static int MBToWChar(const char *pMB, int nCbMB, wchar_t *pWChar, int nCchWChar);

	static int Utf8ToWChar(const char *pUtf, int nCbUtf, wchar_t *pWChar, int nCchWChar);
	static int Utf8ToMB(const char *pUTF, int nCbUtf, char *pMB, int nCbMB);

public:
	//character transfer to hex style. example: a -> 'a'
	static char CharToHex(unsigned char x){
		return x > 9 ? x + 55 : x + 48;
	}	

};
