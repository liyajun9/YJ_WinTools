#include "stdafx.h"
#include "SocketUtils.h"
#include <ws2tcpip.h>
#include "Encodings.h"

#define MAX_IP_ADDRESS 128
#define MAX_PORT 16
#define RADIX_DECIMAL 10

namespace YJ_WinTools{

int CSocketUtils::GetAnyAddr(int nPort, SOCKADDR *pAddr)
{
	return _GetAddrInfo(wstring(_T("")), nPort, 0, AF_INET, 0, AI_PASSIVE|AI_NUMERICSERV, pAddr);
}

int CSocketUtils::GetAddr(wstring& sIP, int nPort, SOCKADDR *pAddr)
{
	return _GetAddrInfo(sIP, nPort, 0, AF_INET, 0, AI_NUMERICSERV, pAddr);
}

int CSocketUtils::GetPortFromAddr(SOCKADDR *pAddr)
{
	return ntohs(((SOCKADDR_IN*)pAddr)->sin_port);
}

wstring CSocketUtils::GetIPFromAddr(SOCKADDR *pAddr)
{
	char pszIP[MAX_IP_ADDRESS];
	memset(pszIP, 0, MAX_IP_ADDRESS);
	inet_ntop(AF_INET, reinterpret_cast<PVOID>(&((SOCKADDR_IN*)pAddr)->sin_addr), pszIP, MAX_IP_ADDRESS);
	string sIP(pszIP);

	return	CEncodings::MultiByte2WideChar(sIP);
}

wstring CSocketUtils::GetFirstHostAddr()
{
	wstring sRet(_T(""));
	char pszHostName[MAX_HOSTNAME_LEN];
	memset(pszHostName, 0, MAX_HOSTNAME_LEN);
	int nRet = gethostname(pszHostName, MAX_HOSTNAME_LEN);
	if(nRet != NO_ERROR) return sRet;

	hostent *pHostent = gethostbyname(pszHostName);
	in_addr addr;
	string sIP;
	if(pHostent->h_addr_list[0] != 0){
		addr.s_addr = *(u_long *)pHostent->h_addr_list[0];
		sRet = CEncodings::MultiByte2WideChar(inet_ntoa(addr));
	}
	return sRet;
}

int CSocketUtils::GetHostAddrs(vector<string>& sIPlist)
{
	char pszHostName[MAX_HOSTNAME_LEN];
	memset(pszHostName, 0, MAX_HOSTNAME_LEN);
	int nRet = gethostname(pszHostName, MAX_HOSTNAME_LEN);
	if(nRet != NO_ERROR) return nRet;

	hostent *pHostent = gethostbyname(pszHostName);
	in_addr addr;
	int i(0);
	while(pHostent->h_addr_list[i] != 0){
		addr.s_addr = *(u_long *)pHostent->h_addr_list[i++];
		sIPlist.push_back(inet_ntoa(addr));		
	}
	return NO_ERROR;

	//addrinfo *pResultAddr = NULL;
	//addrinfo hints;
	//memset(&hints, 0, sizeof(hints));
	//hints.ai_family = AF_INET;
	//hints.ai_protocol = IPPROTO_TCP | IPPROTO_UDP;
	//hints.ai_socktype = SOCK_STREAM | SOCK_DGRAM;
	//int nRet =  getaddrinfo(pszHostName, NULL, &hints, &pResultAddr);
	//if(nRet != NO_ERROR) return nRet;

	//sockaddresses.clear();
	//for(addrinfo *ptr = pResultAddr; ptr != NULL; ptr = pResultAddr->ai_next){
	//	SOCKADDR sa;
	//	memset(&sa, 0, sizeof(sa));
	//	sa.sa_family = ptr->ai_addr->sa_family;
	//	memcpy(sa.sa_data, ptr->ai_addr->sa_data, sizeof(ptr->ai_addr->sa_data));
	//	sockaddresses.push_back(sa);
	//}
	//freeaddrinfo(pResultAddr);
	//return NO_ERROR;
}

wstring CSocketUtils::GetHostName()
{
	char pszHostName[MAX_HOSTNAME_LEN];
	memset(pszHostName, 0, MAX_HOSTNAME_LEN);
	gethostname(pszHostName, MAX_HOSTNAME_LEN);
	return CEncodings::MultiByte2WideChar(string(pszHostName));
}

int CSocketUtils::atoi_Port(wstring& sPort)
{
	return _wtoi(sPort.c_str());
}

wstring CSocketUtils::itoa_Port(int nPort)
{
	wchar_t pszPort[MAX_PORT];
	memset(pszPort, 0, MAX_PORT);
	_itot_s(nPort, pszPort, RADIX_DECIMAL);
	return wstring(pszPort);
}

string  CSocketUtils::itow_Port(int nPort)
{
	char pszPort[MAX_PORT];
	memset(pszPort, 0, MAX_PORT);
	_itoa_s(nPort, pszPort, RADIX_DECIMAL);
	return string(pszPort);
}

//³É¹¦·µ»Ø0
int CSocketUtils::_GetAddrInfo(wstring& sIP, int nPort, int protocol, int addr_family, int sock_type, int nflags, SOCKADDR *pAddr)
{
	string sip("");
	if(!sIP.empty())	sip = CEncodings::WideChar2MultiByte(sIP);

	char pszPort[MAX_PORT];
	memset(pszPort, 0, MAX_PORT);
	_itoa_s(nPort, pszPort, RADIX_DECIMAL);

	addrinfo *pResultAddr = NULL;
	addrinfo hints;
	memset(&hints, 0, sizeof(hints));
	hints.ai_protocol = protocol;
	hints.ai_family = addr_family;
	hints.ai_socktype = sock_type;
	hints.ai_flags = nflags;
	 
	int nRet = NO_ERROR;
	if(sip.empty())
		nRet = getaddrinfo(NULL, pszPort, &hints, &pResultAddr);
	else
		nRet = getaddrinfo(sip.c_str(), pszPort, &hints, &pResultAddr);
	if(nRet != NO_ERROR) return nRet;

	pAddr->sa_family = pResultAddr->ai_addr->sa_family;
	memcpy(pAddr->sa_data, pResultAddr->ai_addr->sa_data, sizeof(pResultAddr->ai_addr->sa_data));
	freeaddrinfo(pResultAddr);

	return NO_ERROR;
}

}