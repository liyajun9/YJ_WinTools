#include "stdafx.h"
#include "SystemUtils.h"

int NS_Yutils::GetNumberOfProcessors()
{
	SYSTEM_INFO sysInfo;
	GetSystemInfo(&sysInfo);

	return sysInfo.dwNumberOfProcessors;
}