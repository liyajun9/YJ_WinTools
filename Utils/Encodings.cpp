#include "stdafx.h"
#include "Encodings.h"

namespace YJ_WinTools{

	string CEncodings::WideChar2Utf8(const wstring& str)
	{
		string sRet = "";
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
	wstring CEncodings::Utf82WideChar(const string& str)
	{
		wstring sRet = L"";
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
	string CEncodings::MultiByte2Utf8(const string& str)
	{
		wstring wsStr = MultiByte2WideChar(str);
		if(wsStr.size()<=0) return "";
		return WideChar2Utf8(wsStr);
	}
	string CEncodings::Utf82MultiByte(const string& str)
	{
		wstring wsStr = Utf82WideChar(str);
		if(wsStr.size()<=0) return "";
		return WideChar2MultiByte(wsStr);
	}

	wstring CEncodings::MultiByte2WideChar(const string& str)
	{
		wstring sRet = L"";
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
	string CEncodings::WideChar2MultiByte(const wstring& str)
	{
		string sRet = "";
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

	int CEncodings::WideChar2Utf8(const wchar_t *pszUNICODE, int nCchUNICODE, char *pszUTF, int nCbUTF)
	{
		int nRet(0);
		do 
		{
			if(!pszUNICODE || !pszUTF || nCchUNICODE <= 0 || nCbUTF <= 0) break;

			int nLen = WideCharToMultiByte(CP_UTF8,  0, pszUNICODE, nCchUNICODE, NULL, 0, NULL, NULL);
			if(nLen <= 0) break;
			if(nCbUTF < nLen + 1) break;

			nLen = WideCharToMultiByte(CP_UTF8, 0, pszUNICODE, nCchUNICODE, pszUTF, nLen, NULL, NULL);
			pszUTF[nLen] = '\0';
			nRet = nLen + 1;
		} while (0);

		return nRet;
	}

	int CEncodings::WideChar2MultiByte(const wchar_t *pszUNICODE, int nCchUNICODE, char *pszANSI, int nCbANSI)
	{
		int nRet(0);
		do 
		{
			if(!pszUNICODE || !pszANSI || nCchUNICODE <= 0 || nCbANSI <= 0) break;

			int nLen = WideCharToMultiByte(CP_ACP,  0, pszUNICODE, nCchUNICODE, NULL, 0, NULL, NULL);
			if(nLen <= 0) break;
			if(nCbANSI < nLen + 1) break;

			nLen = WideCharToMultiByte(CP_ACP, 0, pszUNICODE, nCchUNICODE, pszANSI, nLen, NULL, NULL);
			pszANSI[nLen] = '\0';
			nRet = nLen + 1;
		} while (0);

		return nRet;
	}

	int CEncodings::MultiByte2Utf8(const char *pszANSI, int nCbANSI, char *pszUTF, int nCbUTF)
	{
		int nRet(0);
		do 
		{
			if(!pszANSI || !pszUTF || nCbANSI <= 0 || nCbUTF <= 0) break;

			int nLen = MultiByteToWideChar(CP_ACP,  0, pszANSI, nCbANSI, NULL, 0);
			if(nLen <= 0) break;
			wchar_t *pszWide = static_cast<wchar_t*>(calloc(nLen, sizeof(wchar_t)));
			if(!pszWide) break;
			nLen = MultiByteToWideChar(CP_ACP, 0, pszANSI, nCbANSI, pszWide, nLen);

			int nLenNew = WideCharToMultiByte(CP_UTF8, 0, pszWide, nLen, NULL, 0, NULL, NULL);
			if(nLenNew <= 0 || nCbUTF < nLenNew + 1){
				free(pszWide);		break;
			}
			nLen = WideCharToMultiByte(CP_UTF8, 0, pszWide, nLen, pszUTF, nCbUTF, NULL, NULL);
			pszUTF[nLen] = '\0';
			nRet = nLen + 1;
			free(pszWide);
		} while (0);

		return nRet;
	}
	int CEncodings::MultiByte2WideChar(const char *pszANSI, int nCbANSI, wchar_t *pszUNICODE, int nCchUNICODE)
	{
		int nRet(0);
		do 
		{
			if(!pszANSI || !pszUNICODE || nCbANSI <= 0 || nCchUNICODE <= 0) break;

			int nLen = MultiByteToWideChar(CP_ACP,  0, pszANSI, nCbANSI, NULL, 0);
			if(nLen <= 0) break;
			if(nCchUNICODE < nLen + 1) break;
			nLen = MultiByteToWideChar(CP_ACP, 0, pszANSI, nCbANSI, pszUNICODE, nCchUNICODE);
			pszUNICODE[nLen] = L'\0';
			nRet = nLen + 1;
		} while (0);

		return nRet;
	}

	int CEncodings::Utf82WideChar(const char *pszUTF, int nCbUTF, wchar_t *pszUNICODE, int nCchUNICODE)
	{
		int nRet(0);
		do 
		{
			if(!pszUTF || !pszUNICODE || nCbUTF <= 0 || nCchUNICODE <= 0) break;

			int nLen = MultiByteToWideChar(CP_UTF8,  0, pszUTF, nCbUTF, NULL, 0);
			if(nLen <= 0) break;
			if(nCchUNICODE < nLen + 1) break;
			nLen = MultiByteToWideChar(CP_UTF8, 0, pszUTF, nCbUTF, pszUNICODE, nCchUNICODE);
			pszUNICODE[nLen] = L'\0';
			nRet = nLen + 1;
		} while (0);

		return nRet;
	}
	int CEncodings::Utf82MultiByte(const char *pszUTF, int nCbUTF, char *pszANSI, int nCbANSI)
	{
		int nRet(0);
		do 
		{
			if(!pszUTF || !pszANSI || nCbUTF <= 0 || nCbANSI <= 0) break;

			int nLen = MultiByteToWideChar(CP_UTF8,  0, pszUTF, nCbUTF, NULL, 0);
			if(nLen <= 0) break;
			wchar_t *pszWide = static_cast<wchar_t*>(calloc(nLen, sizeof(wchar_t)));
			if(!pszWide) break;
			nLen = MultiByteToWideChar(CP_UTF8, 0, pszUTF, nCbUTF, pszWide, nLen);

			int nLenNew = WideCharToMultiByte(CP_ACP, 0, pszWide, nLen, NULL, 0, NULL, NULL);
			if(nLenNew <= 0 || nCbANSI < nLenNew + 1){
				free(pszWide);		break;
			}
			nLen = WideCharToMultiByte(CP_ACP, 0, pszWide, nLen, pszANSI, nCbANSI, NULL, NULL);
			pszANSI[nLen] = '\0';
			nRet = nLen + 1;
			free(pszWide);
		} while (0);

		return nRet;
	}

}