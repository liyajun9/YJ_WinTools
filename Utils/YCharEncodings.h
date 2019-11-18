// Frequently used charset transfer tools
//	Support: MultiByte, UniCode, UTF8
// author:liyajun
#pragma once
#include <string>
#include "..\Log\tstring.h"

#if defined(_UNICODE) || defined(UNICODE)
#define MBToTString			NS_Yutils::MBToWChar
#define	WCharToTString	    NS_Yutils::WCharToWChar
#define Utf8ToTString			NS_Yutils::Utf8ToWChar
#define TStringToMB			NS_Yutils::WCharToMB
#define TStringToWChar		NS_Yutils::WCharToWChar
#define TStringToUtf8			NS_Yutils::WCharToUtf8	
#define MBToTChar				NS_Yutils::MBToWChar
#define WCharToTChar		NS_Yutils::WCharToWChar			
#define Utf8ToTChar			NS_Yutils::Utf8ToWChar
#define TCharToMB				NS_Yutils::WCharToMB
#define TCharToWChar		NS_Yutils::WCharToWChar
#define TCharToUtf8			NS_Yutils::WCharToUtf8
#else
#define MBToTString			NS_Yutils::MBToMB
#define	WCharToTString		NS_Yutils::WCharToMB
#define Utf8ToTString			NS_Yutils::Utf8ToMB
#define TStringToMB			NS_Yutils::MBToMB
#define TStringToWChar		NS_Yutils::MBToWChar
#define TStringToUtf8			NS_Yutils::WCharToUtf8
#define MBToTChar				NS_Yutils::MBToMB			
#define WCharToTChar		NS_Yutils::WCharToMB
#define Utf8ToTChar			NS_Yutils::Utf8ToMB
#define TCharToMB				NS_Yutils::MBToMB
#define TCharToWChar		NS_Yutils::MBToWChar
#define TCharToUtf8			NS_Yutils::MBToUtf8
#endif


namespace NS_Yutils{
//Compatible functions
std::wstring& WCharToWChar(std::wstring& str);
std::string& MBToMB(std::string& str);
int WCharToWChar(const wchar_t *pWChar, int nCchWChar, wchar_t *pOut, int nCchOut);
int MBToMB(const char *pMB, int nCchMB, char *pOut, int nCchOut);

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
