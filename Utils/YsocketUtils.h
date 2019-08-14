// socket utils
// most method return NO_ERROR(0L) on success
// author:liyajun
#pragma once
#include <vector>
#include <winsock.h>
#include "..\Log\tstring.h"

class CYSocketUtils
{
public:	
	//get addresses
	static tstring GetHostName();
	static int GetHostAddrList(std::vector<tstring>& sIPlist);
	static tstring GetFirstHostAddr();
	static int GetWildcardAddr(int nPort, SOCKADDR *pAddr);

	//parse ip, port from SOCKADDR
	static tstring GetIPFromAddr(SOCKADDR *pAddr);
	static int GetPortFromAddr(SOCKADDR *pAddr);

	//ip, port conversions
	static int StringToAddr(tstring& sIP, int nPort, SOCKADDR *pAddr);
	static int StringToIntPort(tstring& sPort);	
	static tstring IntPortToWString(int nPort); 
	static tstring IntPortToString(int nPort);  

private:
	static int _GetFirstAddrInfo(tstring& sIP, int nPort, int protocol, int addr_family, int sock_type, int nflags,  SOCKADDR *pAddr);//return NO_ERROR(0) on success

private:
	CYSocketUtils(void){}
	~CYSocketUtils(void){}
};
