//李亚军 2018/3/27
//Toolbox of encoding/decoding
#pragma once

namespace YJ_WinTools{

class CEncodings{
public:
	//使用标准库string的编码转换
	static string WideChar2Utf8(const wstring& str);
	static string WideChar2MultiByte(const wstring& str);

	static string MultiByte2Utf8(const string& str);
	static wstring MultiByte2WideChar(const string& str);

	static wstring Utf82WideChar(const string& str);	
	static string Utf82MultiByte(const string& str);

	//使用字符数组的编码转换,返回转换后的字节数(包含'\0')
	static int WideChar2Utf8(const wchar_t *pszUNICODE, int nCchUNICODE, char *pszUTF, int nCbUTF);//nCchUNICODE为要转换的字符数(不含'\0'), nCbUTF为输出缓存字节数
	static int WideChar2MultiByte(const wchar_t *pszUNICODE, int nCchUNICODE, char *pszANSI, int nCbANSI);//nCchUNICODE为要转换的字符数(不含'\0'), nCbANSI为输出缓存字节数

	static int MultiByte2Utf8(const char *pszANSI, int nCbANSI, char *pszUTF, int nCbUTF);//nCbANSI为输入数据实际字节数(不含'\0'), nCbUTF为输出缓存字节数
	static int MultiByte2WideChar(const char *pszANSI, int nCbANSI, wchar_t *pszUNICODE, int nCchUNICODE);//nCbANSI为输入数据实际字节数(不含'\0'), nCchUNICODE为输出缓存字符数(wchar_t个数)

	static int Utf82WideChar(const char *pszUTF, int nCbUTF, wchar_t *pszUNICODE, int nCchUNICODE);//nCbUTF为输入数据实际字节数(不含'\0'), nCchUNICODE为输出缓存字符数(wchar_t个数)
	static int Utf82MultiByte(const char *pszUTF, int nCbUTF, char *pszANSI, int nCbANSI);//nCbUTF为输入数据实际字节数(不含'\0'), nCbANSI为输出缓存字节数

	static char ToHex(unsigned char x){
		return x > 9 ? x + 55 : x + 48;
	}	

};

}
