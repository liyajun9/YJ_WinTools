// socket utils
// most method return NO_ERROR(0L) on success
// author:liyajun
#pragma once
#include <vector>
#include <winsock.h>

class CYsocketUtils
{
public:	
	//get addresses
	static std::wstring GetHostName();
	static int GetHostAddrList(std::vector<std::string>& sIPlist);
	static std::wstring GetFirstHostAddr();
	static int GetWildcardAddr(int nPort, SOCKADDR *pAddr);

	//parse ip, port from SOCKADDR
	static std::wstring GetIPFromAddr(SOCKADDR *pAddr);
	static int GetPortFromAddr(SOCKADDR *pAddr);

	//ip, port conversions
	static int StringToAddr(std::wstring& sIP, int nPort, SOCKADDR *pAddr);
	static int StringToIntPort(std::wstring& sPort);	
	static std::wstring IntPortToWString(int nPort); 
	static std::string IntPortToString(int nPort);  

private:
	static int _GetFirstAddrInfo(std::wstring& sIP, int nPort, int protocol, int addr_family, int sock_type, int nflags,  SOCKADDR *pAddr);//return NO_ERROR(0) on success

private:
	CYsocketUtils(void){}
	~CYsocketUtils(void){}
};
