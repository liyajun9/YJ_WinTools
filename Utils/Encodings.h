//���Ǿ� 2018/3/27
//Toolbox of encoding/decoding
#pragma once

namespace YJ_WinTools{

class CEncodings{
public:
	//ʹ�ñ�׼��string�ı���ת��
	static string WideChar2Utf8(const wstring& str);
	static string WideChar2MultiByte(const wstring& str);

	static string MultiByte2Utf8(const string& str);
	static wstring MultiByte2WideChar(const string& str);

	static wstring Utf82WideChar(const string& str);	
	static string Utf82MultiByte(const string& str);

	//ʹ���ַ�����ı���ת��,����ת������ֽ���(����'\0')
	static int WideChar2Utf8(const wchar_t *pszUNICODE, int nCchUNICODE, char *pszUTF, int nCbUTF);//nCchUNICODEΪҪת�����ַ���(����'\0'), nCbUTFΪ��������ֽ���
	static int WideChar2MultiByte(const wchar_t *pszUNICODE, int nCchUNICODE, char *pszANSI, int nCbANSI);//nCchUNICODEΪҪת�����ַ���(����'\0'), nCbANSIΪ��������ֽ���

	static int MultiByte2Utf8(const char *pszANSI, int nCbANSI, char *pszUTF, int nCbUTF);//nCbANSIΪ��������ʵ���ֽ���(����'\0'), nCbUTFΪ��������ֽ���
	static int MultiByte2WideChar(const char *pszANSI, int nCbANSI, wchar_t *pszUNICODE, int nCchUNICODE);//nCbANSIΪ��������ʵ���ֽ���(����'\0'), nCchUNICODEΪ��������ַ���(wchar_t����)

	static int Utf82WideChar(const char *pszUTF, int nCbUTF, wchar_t *pszUNICODE, int nCchUNICODE);//nCbUTFΪ��������ʵ���ֽ���(����'\0'), nCchUNICODEΪ��������ַ���(wchar_t����)
	static int Utf82MultiByte(const char *pszUTF, int nCbUTF, char *pszANSI, int nCbANSI);//nCbUTFΪ��������ʵ���ֽ���(����'\0'), nCbANSIΪ��������ֽ���

	static char ToHex(unsigned char x){
		return x > 9 ? x + 55 : x + 48;
	}	

};

}
