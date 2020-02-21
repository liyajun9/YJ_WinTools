#include "pch.h"
#include "SystemUtils.h"

int NS_Yutils::getNumberOfProcessors()
{
	SYSTEM_INFO sysInfo;
	GetSystemInfo(&sysInfo);

	return sysInfo.dwNumberOfProcessors;
}