#pragma once

#include <string>
#include <iostream>
using namespace std;
#ifndef _tstring
#ifdef _UNICODE
#define _tstring wstring
#else
#define _tstring string
#endif
#endif

#include <WinSock2.h>
#include <IPTypes.h>
#ifndef _WINDOWS_
#define WIN32_LEAN_AND_MEAN	//to avoid include winsock.h in windows.h
#include <Windows.h>
#undef WIN32_LEAN_AND_MEAN
#endif


#include ".\Exceptions\Exception.h"
#include ".\Exceptions\Win32Exception.h"
#include ".\Utils\Trace.h"
#include ".\Utils\Encodings.h"

using namespace YJ_WinTools;