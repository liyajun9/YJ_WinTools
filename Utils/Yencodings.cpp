#include "stdafx.h"
#include "Yencodings.h"
#include <Windows.h>

std::string CYEncodings::WCharToUtf8(const std::wstring& str)
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

std::wstring CYEncodings::Utf8ToWChar(const std::string& str)
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

std::string CYEncodings::MBToUtf8(const std::string& str)
{
	std::wstring wsStr = MBToWChar(str);
	if(wsStr.size()<=0) return "";
	return WCharToUtf8(wsStr);
}

std::string CYEncodings::Utf8ToMB(const std::string& str)
{
	std::wstring wsStr = Utf8ToWChar(str);
	if(wsStr.size()<=0) return "";
	return WCharToMB(wsStr);
}

std::wstring CYEncodings::MBToWChar(const std::string& str)
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

std::string CYEncodings::WCharToMB(const std::wstring& str)
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

int CYEncodings::WCharToUtf8(const wchar_t *pWChar, int nCchWChar, char *pUtf8, int nCbUtf8)
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

int CYEncodings::WCharToMB(const wchar_t *pWChar, int nCchWChar, char *pMB, int nCbMB)
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

int CYEncodings::MBToUtf8(const char *pMB, int nCbMB, char *pUtf, int nCbUtf)
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

int CYEncodings::MBToWChar(const char *pMB, int nCbMB, wchar_t *pWChar, int nCchWChar)
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

int CYEncodings::Utf8ToWChar(const char *pUtf, int nCbUtf, wchar_t *pWChar, int nCchWChar)
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

int CYEncodings::Utf8ToMB(const char *pUTF, int nCbUtf, char *pMB, int nCbMB)
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