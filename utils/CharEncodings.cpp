#include "stdafx.h"
#include "CharEncodings.h"
#include <Windows.h>

std::wstring& NS_Yutils::WCharToWChar(std::wstring& str)
{
	return str;
}

std::string& NS_Yutils::MBToMB(std::string& str)
{
	return str;
}

int NS_Yutils::WCharToWChar(const wchar_t *pWChar, int nCchWChar, wchar_t *pOut, int nCchOut)
{
	if(!pWChar || !pOut || nCchWChar <= 0 || nCchOut <= 0 || nCchOut < nCchWChar)
		return 0;

	memset(pOut, 0, nCchOut * sizeof(wchar_t));
	int nLen = nCchWChar * sizeof(wchar_t);
	memcpy(pOut, pWChar, nLen);
	return nLen;
}

int NS_Yutils::MBToMB(const char *pMB, int nCchMB, char *pOut, int nCchOut)
{
	if(!pMB || !pOut || nCchMB <= 0 || nCchOut <= 0 || nCchOut < nCchMB)
		return 0;

	memset(pOut, 0, nCchOut * sizeof(char));
	int nLen = nCchMB * sizeof(char);
	memcpy(pOut, pMB, nLen);
	return nLen;
}

std::string NS_Yutils::WCharToUtf8(const std::wstring& str)
{
	std::string sRet = "";
	do 
	{
		int nLen = WideCharToMultiByte(CP_UTF8, 0, str.c_str(), -1, NULL, 0, NULL, NULL);
		if(nLen <= 0) break;

		char *pszMB = static_cast<char*>(calloc(nLen, sizeof(char)));
		if(!pszMB) break;

		nLen = WideCharToMultiByte(CP_UTF8, 0, str.c_str(), -1, pszMB, nLen, NULL, NULL);
		sRet = pszMB;
		free(pszMB);
	} while (0);

	return sRet;
}

std::wstring NS_Yutils::Utf8ToWChar(const std::string& str)
{
	std::wstring sRet = L"";
	do 
	{
		int nLen = MultiByteToWideChar(CP_UTF8, 0, str.c_str(), -1, NULL, 0);
		if(nLen <= 0) break;

		wchar_t *pszWC = static_cast<wchar_t*>(calloc(nLen, sizeof(wchar_t)));
		if(!pszWC) break;

		nLen = MultiByteToWideChar(CP_UTF8, 0, str.c_str(), -1, pszWC, nLen);
		sRet = pszWC;
		free(pszWC);
	} while (0);

	return sRet;
}

std::string NS_Yutils::MBToUtf8(const std::string& str)
{
	std::wstring wsStr = MBToWChar(str);
	if(wsStr.size()<=0) return "";
	return WCharToUtf8(wsStr);
}

std::string NS_Yutils::Utf8ToMB(const std::string& str)
{
	std::wstring wsStr = Utf8ToWChar(str);
	if(wsStr.size()<=0) return "";
	return WCharToMB(wsStr);
}

std::wstring NS_Yutils::MBToWChar(const std::string& str)
{
	std::wstring sRet = L"";
	do 
	{
		int nLen = MultiByteToWideChar(CP_ACP, 0, str.c_str(), -1, NULL, 0);
		if(nLen <= 0) break;

		wchar_t* pszWC = static_cast<wchar_t*>(calloc(nLen, sizeof(wchar_t)));
		if(!pszWC) break;

		nLen = MultiByteToWideChar(CP_ACP, 0, str.c_str(), -1, pszWC, nLen);
		sRet = pszWC;
		free(pszWC);
	} while (0);

	return sRet;
}

std::string NS_Yutils::WCharToMB(const std::wstring& str)
{
	std::string sRet = "";
	do 
	{
		int nLen = WideCharToMultiByte(CP_ACP, 0, str.c_str(), -1, NULL, 0, NULL, NULL);
		if(nLen <= 0) break;

		char *pszMB = static_cast<char*>(calloc(nLen, sizeof(char)));
		if(!pszMB) break;

		nLen = WideCharToMultiByte(CP_ACP, 0, str.c_str(), -1, pszMB, nLen, NULL, NULL);
		sRet = pszMB;
		free(pszMB);
	} while (0);

	return sRet;
}

int NS_Yutils::WCharToUtf8(const wchar_t *pWChar, int nCchWChar, char *pUtf8, int nCbUtf8)
{
	int nRet(0);
	do 
	{
		if(!pWChar || !pUtf8 || nCchWChar <= 0 || nCbUtf8 <= 0) break;

		int nLen = WideCharToMultiByte(CP_UTF8,  0, pWChar, nCchWChar, NULL, 0, NULL, NULL);
		if(nLen <= 0) break;
		if(nCbUtf8 < nLen + 1) break;

		nLen = WideCharToMultiByte(CP_UTF8, 0, pWChar, nCchWChar, pUtf8, nLen, NULL, NULL);
		pUtf8[nLen] = '\0';
		nRet = nLen + 1;
	} while (0);

	return nRet;
}

int NS_Yutils::WCharToMB(const wchar_t *pWChar, int nCchWChar, char *pMB, int nCbMB)
{
	int nRet(0);
	do 
	{
		if(!pWChar || !pMB || nCchWChar <= 0 || nCbMB <= 0) break;

		int nLen = WideCharToMultiByte(CP_ACP,  0, pWChar, nCchWChar, NULL, 0, NULL, NULL);
		if(nLen <= 0) break;
		if(nCbMB < nLen + 1) break;

		nLen = WideCharToMultiByte(CP_ACP, 0, pWChar, nCchWChar, pMB, nLen, NULL, NULL);
		pMB[nLen] = '\0';
		nRet = nLen + 1;
	} while (0);

	return nRet;
}

int NS_Yutils::MBToUtf8(const char *pMB, int nCbMB, char *pUtf, int nCbUtf)
{
	int nRet(0);
	do 
	{
		if(!pMB || !pUtf || nCbMB <= 0 || nCbUtf <= 0) break;

		int nLen = MultiByteToWideChar(CP_ACP,  0, pMB, nCbMB, NULL, 0);
		if(nLen <= 0) break;
		wchar_t *pszWide = static_cast<wchar_t*>(calloc(nLen, sizeof(wchar_t)));
		if(!pszWide) break;
		nLen = MultiByteToWideChar(CP_ACP, 0, pMB, nCbMB, pszWide, nLen);

		int nLenNew = WideCharToMultiByte(CP_UTF8, 0, pszWide, nLen, NULL, 0, NULL, NULL);
		if(nLenNew <= 0 || nCbUtf < nLenNew + 1){
			free(pszWide);		break;
		}
		nLen = WideCharToMultiByte(CP_UTF8, 0, pszWide, nLen, pUtf, nCbUtf, NULL, NULL);
		pUtf[nLen] = '\0';
		nRet = nLen + 1;
		free(pszWide);
	} while (0);

	return nRet;
}

int NS_Yutils::MBToWChar(const char *pMB, int nCbMB, wchar_t *pWChar, int nCchWChar)
{
	int nRet(0);
	do 
	{
		if(!pMB || !pWChar || nCbMB <= 0 || nCchWChar <= 0) break;

		int nLen = MultiByteToWideChar(CP_ACP,  0, pMB, nCbMB, NULL, 0);
		if(nLen <= 0) break;
		if(nCchWChar < nLen + 1) break;
		nLen = MultiByteToWideChar(CP_ACP, 0, pMB, nCbMB, pWChar, nCchWChar);
		pWChar[nLen] = L'\0';
		nRet = nLen + 1;
	} while (0);

	return nRet;
}

int NS_Yutils::Utf8ToWChar(const char *pUtf, int nCbUtf, wchar_t *pWChar, int nCchWChar)
{
	int nRet(0);
	do 
	{
		if(!pUtf || !pWChar || nCbUtf <= 0 || nCchWChar <= 0) break;

		int nLen = MultiByteToWideChar(CP_UTF8,  0, pUtf, nCbUtf, NULL, 0);
		if(nLen <= 0) break;
		if(nCchWChar < nLen + 1) break;
		nLen = MultiByteToWideChar(CP_UTF8, 0, pUtf, nCbUtf, pWChar, nCchWChar);
		pWChar[nLen] = L'\0';
		nRet = nLen + 1;
	} while (0);

	return nRet;
}

int NS_Yutils::Utf8ToMB(const char *pUTF, int nCbUtf, char *pMB, int nCbMB)
{
	int nRet(0);
	do 
	{
		if(!pUTF || !pMB || nCbUtf <= 0 || nCbMB <= 0) break;

		int nLen = MultiByteToWideChar(CP_UTF8,  0, pUTF, nCbUtf, NULL, 0);
		if(nLen <= 0) break;
		wchar_t *pszWide = static_cast<wchar_t*>(calloc(nLen, sizeof(wchar_t)));
		if(!pszWide) break;
		nLen = MultiByteToWideChar(CP_UTF8, 0, pUTF, nCbUtf, pszWide, nLen);

		int nLenNew = WideCharToMultiByte(CP_ACP, 0, pszWide, nLen, NULL, 0, NULL, NULL);
		if(nLenNew <= 0 || nCbMB < nLenNew + 1){
			free(pszWide);		break;
		}
		nLen = WideCharToMultiByte(CP_ACP, 0, pszWide, nLen, pMB, nCbMB, NULL, NULL);
		pMB[nLen] = '\0';
		nRet = nLen + 1;
		free(pszWide);
	} while (0);

	return nRet;
}

char NS_Yutils::CharToHex(unsigned char x) {
	return x > 9 ? x + 55 : x + 48;
}	