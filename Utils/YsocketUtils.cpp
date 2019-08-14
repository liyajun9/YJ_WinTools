#include "stdafx.h"
#include "YsocketUtils.h"
#include <ws2tcpip.h>
#include "YCharEncodings.h"
#include <iptypes.h>
#include <winsock.h>

#define MAX_LEN_OF_IP 128
#define MAX_LEN_OF_PORT 16
#define RADIX_DECIMAL 10

int CYSocketUtils::GetWildcardAddr(int nPort, SOCKADDR *pAddr)
{
	return _GetFirstAddrInfo(tstring(_T("")), nPort, 0, AF_INET, 0, AI_PASSIVE|AI_NUMERICSERV, pAddr);
}

int CYSocketUtils::StringToAddr(std::wstring& sIP, int nPort, SOCKADDR *pAddr)
{
	return _GetFirstAddrInfo(sIP, nPort, 0, AF_INET, 0, AI_NUMERICSERV, pAddr);
}

int CYSocketUtils::GetPortFromAddr(SOCKADDR *pAddr)
{
	return ntohs(((SOCKADDR_IN*)pAddr)->sin_port);
}

tstring CYSocketUtils::GetIPFromAddr(SOCKADDR *pAddr)
{
	TCHAR pszIP[MAX_LEN_OF_IP];
	memset(pszIP, 0, MAX_LEN_OF_IP);
	InetNtop(AF_INET, reinterpret_cast<PVOID>(&((SOCKADDR_IN*)pAddr)->sin_addr),pszIP, MAX_LEN_OF_IP);
	//inet_ntop(AF_INET, reinterpret_cast<PVOID>(&((SOCKADDR_IN*)pAddr)->sin_addr), pszIP, MAX_LEN_OF_IP);

	return	tstring(pszIP);
}

tstring CYSocketUtils::GetFirstHostAddr()
{
	tstring sRet(_T(""));

	char pszHostName[MAX_HOSTNAME_LEN];
	memset(pszHostName, 0, MAX_HOSTNAME_LEN);
	int nRet = gethostname(pszHostName, MAX_HOSTNAME_LEN);
	if(nRet != NO_ERROR) 
		return sRet;

	hostent *pHostent = gethostbyname(pszHostName);
	in_addr addr;
	if(pHostent->h_addr_list[0] != 0){
		addr.s_addr = *(u_long *)pHostent->h_addr_list[0];
#if defined(_UNICODE)||defined(UNICODE)
		sRet = CYCharEncodings::MBToWChar(inet_ntoa(addr));
#else
		sRet = inet_ntoa(addr);
#endif
	}
	return sRet;
}

int CYSocketUtils::GetHostAddrList(std::vector<tstring>& sIPlist)
{
	char pszHostName[MAX_HOSTNAME_LEN];
	memset(pszHostName, 0, MAX_HOSTNAME_LEN);
	int nRet = gethostname(pszHostName, MAX_HOSTNAME_LEN);
	if(nRet != NO_ERROR) 
		return nRet;

	hostent *pHostent = gethostbyname(pszHostName);
	in_addr addr;
	int i(0);
	while(pHostent->h_addr_list[i] != 0){
		addr.s_addr = *(u_long *)pHostent->h_addr_list[i++];
#if defined(_UNICODE)||defined(UNICODE)
		sIPlist.push_back(CYCharEncodings::MBToWChar(inet_ntoa(addr)));
#else
		sIPlist.push_back(inet_ntoa(addr));
#endif	
	}
	return NO_ERROR;
}

tstring CYSocketUtils::GetHostName()
{
	char pszHostName[MAX_HOSTNAME_LEN];
	memset(pszHostName, 0, MAX_HOSTNAME_LEN);
	gethostname(pszHostName, MAX_HOSTNAME_LEN);
#if defined(_UNICODE)||defined(UNICODE)
	return CYCharEncodings::MBToWChar(std::string(pszHostName));
#else
	return std::string(pszHostName);
#endif
}

int CYSocketUtils::StringToIntPort(tstring& sPort)
{
	return _ttoi(sPort.c_str());
}

tstring CYSocketUtils::IntPortToWString(int nPort)
{
	TCHAR pszPort[MAX_LEN_OF_PORT];
	memset(pszPort, 0, MAX_LEN_OF_PORT);
	_itot_s(nPort, pszPort, RADIX_DECIMAL);
	return tstring(pszPort);
}

tstring  CYSocketUtils::IntPortToString(int nPort)
{
	TCHAR pszPort[MAX_LEN_OF_PORT];
	memset(pszPort, 0, MAX_LEN_OF_PORT);
	_itot_s(nPort, pszPort, RADIX_DECIMAL);
	return tstring(pszPort);
}

int CYSocketUtils::_GetFirstAddrInfo(tstring& sIP, int nPort, int protocol, int addr_family, int sock_type, int nflags, SOCKADDR *pAddr)
{
	std::string sTmpIP("");
	if(!sIP.empty())	
#if defined(_UNICODE)||defined(UNICODE)
		sTmpIP = CYCharEncodings::WCharToMB(sIP);
#else
		sTmpIP = sIP;
#endif

	char pszPort[MAX_LEN_OF_PORT];
	memset(pszPort, 0, MAX_LEN_OF_PORT);
	_itoa_s(nPort, pszPort, RADIX_DECIMAL);

	addrinfo *pResultAddr = NULL;
	addrinfo hints;
	memset(&hints, 0, sizeof(hints));
	hints.ai_protocol = protocol;
	hints.ai_family = addr_family;
	hints.ai_socktype = sock_type;
	hints.ai_flags = nflags;
	 
	int nRet = NO_ERROR;
	if(sTmpIP.empty())
		nRet = getaddrinfo(NULL, pszPort, &hints, &pResultAddr);
	else
		nRet = getaddrinfo(sTmpIP.c_str(), pszPort, &hints, &pResultAddr);

	if(nRet != NO_ERROR) 
		return nRet;

	pAddr->sa_family = pResultAddr->ai_addr->sa_family;
	memcpy(pAddr->sa_data, pResultAddr->ai_addr->sa_data, sizeof(pResultAddr->ai_addr->sa_data));
	freeaddrinfo(pResultAddr);

	return NO_ERROR;
}