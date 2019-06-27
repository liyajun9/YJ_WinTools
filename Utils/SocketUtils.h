#pragma once
#include <vector>
namespace YJ_WinTools{


class CSocketUtils
{
public:
	//成功返回0
	static int GetAnyAddr(int nPort, SOCKADDR *pAddr);//获取本机用于bind和connect的通配符地址
	static int GetAddr(wstring& sIP, int nPort, SOCKADDR *pAddr);//将IP和port转为TCP sockaddr

	static wstring GetHostName();//获取主机名
	static wstring GetFirstHostAddr();//获取主机第一个地址
	static int GetHostAddrs(vector<string>& sIPlist);//获取主机地址列表

	static int GetPortFromAddr(SOCKADDR *pAddr);//从sockaddr取port
	static wstring GetIPFromAddr(SOCKADDR *pAddr);//从sockaddr取IP
	static int atoi_Port(wstring& sPort);	//端口号与字符串转换
	static wstring itoa_Port(int nPort); //端口号与字符串转换
	static string itow_Port(int nPort);  //端口号与字符串转换
private:
	static int _GetAddrInfo(wstring& sIP, int nPort, int protocol, int addr_family, int sock_type, int nflags,  SOCKADDR *pAddr);//对getaddrinfo的封装，且只返回第一个地址!!!

private:
	CSocketUtils(void)
	{
	}

	~CSocketUtils(void)
	{
	}
};

}
