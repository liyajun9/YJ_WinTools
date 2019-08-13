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
	return _GetFirstAddrInfo(std::wstring(L""), nPort, 0, AF_INET, 0, AI_PASSIVE|AI_NUMERICSERV, pAddr);
}

int CYSocketUtils::StringToAddr(std::wstring& sIP, int nPort, SOCKADDR *pAddr)
{
	return _GetFirstAddrInfo(sIP, nPort, 0, AF_INET, 0, AI_NUMERICSERV, pAddr);
}

int CYSocketUtils::GetPortFromAddr(SOCKADDR *pAddr)
{
	return ntohs(((SOCKADDR_IN*)pAddr)->sin_port);
}

std::wstring CYSocketUtils::GetIPFromAddr(SOCKADDR *pAddr)
{
	char pszIP[MAX_LEN_OF_IP];
	memset(pszIP, 0, MAX_LEN_OF_IP);
	inet_ntop(AF_INET, reinterpret_cast<PVOID>(&((SOCKADDR_IN*)pAddr)->sin_addr), pszIP, MAX_LEN_OF_IP);
	std::string sIP(pszIP);

	return	CYCharEncodings::MBToWChar(sIP);
}

std::wstring CYSocketUtils::GetFirstHostAddr()
{
	std::wstring sRet(L"");
	char pszHostName[MAX_HOSTNAME_LEN];
	memset(pszHostName, 0, MAX_HOSTNAME_LEN);
	int nRet = gethostname(pszHostName, MAX_HOSTNAME_LEN);
	if(nRet != NO_ERROR) 
		return sRet;

	hostent *pHostent = gethostbyname(pszHostName);
	in_addr addr;
	std::string sIP;
	if(pHostent->h_addr_list[0] != 0){
		addr.s_addr = *(u_long *)pHostent->h_addr_list[0];
		sRet = CYCharEncodings::MBToWChar(inet_ntoa(addr));
	}
	return sRet;
}

int CYSocketUtils::GetHostAddrList(std::vector<std::string>& sIPlist)
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
		sIPlist.push_back(inet_ntoa(addr));		
	}
	return NO_ERROR;
}

std::wstring CYSocketUtils::GetHostName()
{
	char pszHostName[MAX_HOSTNAME_LEN];
	memset(pszHostName, 0, MAX_HOSTNAME_LEN);
	gethostname(pszHostName, MAX_HOSTNAME_LEN);
	return CYCharEncodings::MBToWChar(std::string(pszHostName));
}

int CYSocketUtils::StringToIntPort(std::wstring& sPort)
{
	return _wtoi(sPort.c_str());
}

std::wstring CYSocketUtils::IntPortToWString(int nPort)
{
	wchar_t pszPort[MAX_LEN_OF_PORT];
	memset(pszPort, 0, MAX_LEN_OF_PORT);
	_itow(nPort, pszPort, RADIX_DECIMAL);
	return std::wstring(pszPort);
}

std::string  CYSocketUtils::IntPortToString(int nPort)
{
	char pszPort[MAX_LEN_OF_PORT];
	memset(pszPort, 0, MAX_LEN_OF_PORT);
	_itoa_s(nPort, pszPort, RADIX_DECIMAL);
	return std::string(pszPort);
}

int CYSocketUtils::_GetFirstAddrInfo(std::wstring& sIP, int nPort, int protocol, int addr_family, int sock_type, int nflags, SOCKADDR *pAddr)
{
	std::string sTmpIP("");
	if(!sIP.empty())	
		sTmpIP = CYCharEncodings::WCharToMB(sIP);

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