#pragma once
#include <vector>
namespace YJ_WinTools{


class CSocketUtils
{
public:
	//�ɹ�����0
	static int GetAnyAddr(int nPort, SOCKADDR *pAddr);//��ȡ��������bind��connect��ͨ�����ַ
	static int GetAddr(wstring& sIP, int nPort, SOCKADDR *pAddr);//��IP��portתΪTCP sockaddr

	static wstring GetHostName();//��ȡ������
	static wstring GetFirstHostAddr();//��ȡ������һ����ַ
	static int GetHostAddrs(vector<string>& sIPlist);//��ȡ������ַ�б�

	static int GetPortFromAddr(SOCKADDR *pAddr);//��sockaddrȡport
	static wstring GetIPFromAddr(SOCKADDR *pAddr);//��sockaddrȡIP
	static int atoi_Port(wstring& sPort);	//�˿ں����ַ���ת��
	static wstring itoa_Port(int nPort); //�˿ں����ַ���ת��
	static string itow_Port(int nPort);  //�˿ں����ַ���ת��
private:
	static int _GetAddrInfo(wstring& sIP, int nPort, int protocol, int addr_family, int sock_type, int nflags,  SOCKADDR *pAddr);//��getaddrinfo�ķ�װ����ֻ���ص�һ����ַ!!!

private:
	CSocketUtils(void)
	{
	}

	~CSocketUtils(void)
	{
	}
};

}
