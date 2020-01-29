// socket utils
// most method return NO_ERROR(0L) on success
// author:liyajun
#pragma once
#include <vector>
#include <winsock.h>
#include "ttype.h"

namespace NS_Yutils
{
//get addresses
tstring GetHostName();
int GetHostAddrList(std::vector<tstring>& sIPlist);
tstring GetFirstHostAddr();
int GetWildcardAddr(int nPort, SOCKADDR *pAddr);

//parse ip, port from SOCKADDR
tstring GetIPFromAddr(SOCKADDR *pAddr);
int GetPortFromAddr(SOCKADDR *pAddr);

//ip, port conversions
int StringToAddr(tstring& sIP, int nPort, SOCKADDR *pAddr);
int StringToIntPort(tstring& sPort);	
tstring IntPortToWString(int nPort); 
tstring IntPortToString(int nPort);  

int _GetFirstAddrInfo(tstring& sIP, int nPort, int protocol, int addr_family, int sock_type, int nflags,  SOCKADDR *pAddr);//return NO_ERROR(0) on success
};
