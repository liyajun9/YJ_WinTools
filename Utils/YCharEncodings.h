// Frequently used charset transfer tools
//	Support: MultiByte, UniCode, UTF8
// author:liyajun
#pragma once
#include <string>

namespace NS_Yutils{

//input: std::string or std::wstring
std::string WCharToUtf8(const std::wstring& str);
std::string WCharToMB(const std::wstring& str);

std::string MBToUtf8(const std::string& str);
std::wstring MBToWChar(const std::string& str);

std::wstring Utf8ToWChar(const std::string& str);	
std::string Utf8ToMB(const std::string& str);

//input: character-array and character-count(excluding the terminate)
int WCharToUtf8(const wchar_t *pWChar, int nCchWChar, char *pUtf8, int nCbUtf8);
int WCharToMB(const wchar_t *pWChar, int nCchWChar, char *pMB, int nCbMB);

int MBToUtf8(const char *pMB, int nCbMB, char *pUtf, int nCbUtf);
int MBToWChar(const char *pMB, int nCbMB, wchar_t *pWChar, int nCchWChar);

int Utf8ToWChar(const char *pUtf, int nCbUtf, wchar_t *pWChar, int nCchWChar);
int Utf8ToMB(const char *pUTF, int nCbUtf, char *pMB, int nCbMB);


//character transfer to hex style. example: a -> 'a'
char CharToHex(unsigned char x); 

};
