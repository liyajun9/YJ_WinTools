#include "stdafx.h"
#include "YTimeUtils.h"
#include <time.h>
#include <sys\timeb.h>
#include <tchar.h>
#pragma warning(disable:4996)

tstring NS_Yutils::GetCurrDate(DATE_FORMAT dformat)
{
	time_t t(0);
	time(&t);
	tm *pTm = localtime(&t);

	TCHAR pszTmp[32]; memset(pszTmp, 0, 32);
	switch (dformat)
	{
	case Date_Format_0:
		_stprintf(pszTmp, _T("%04d-%02d-%02d"), pTm->tm_year + 1900, pTm->tm_mon + 1, pTm->tm_mday);
		break;
	case Date_Format_1:
		_stprintf(pszTmp, _T("%02d-%02d-%02d"), (pTm->tm_year + 1900)%1000, pTm->tm_mon + 1, pTm->tm_mday);
		break;
	case Date_Format_2:
		_stprintf(pszTmp, _T("%04d%02d%02d"), pTm->tm_year + 1900, pTm->tm_mon + 1, pTm->tm_mday);
		break;
	case Date_Format_3:
		_stprintf(pszTmp, _T("%02d%02d%02d"), (pTm->tm_year + 1900)%1000, pTm->tm_mon + 1, pTm->tm_mday);
		break;
	case Date_Format_4:
		_stprintf(pszTmp, _T("%04d %02d %02d"), pTm->tm_year + 1900, pTm->tm_mon + 1, pTm->tm_mday);
		break;
	case Date_Format_5:
		_stprintf(pszTmp, _T("%02d %02d %02d"), (pTm->tm_year + 1900)%1000, pTm->tm_mon + 1, pTm->tm_mday);
		break;
	case Date_Format_6:
		_stprintf(pszTmp, _T("%04d/%02d/%02d"), pTm->tm_year + 1900, pTm->tm_mon + 1, pTm->tm_mday);
		break;
	case Date_Format_7:
		_stprintf(pszTmp, _T("%02d/%02d/%02d"), (pTm->tm_year + 1900)%1000, pTm->tm_mon + 1, pTm->tm_mday);
		break;
	case Date_Format_8:
		_stprintf(pszTmp, _T("%02d/%02d/%04d"), pTm->tm_mon + 1, pTm->tm_mday, pTm->tm_year + 1900);
		break;
	case Date_Format_9:
		_stprintf(pszTmp, _T("%02d/%02d/%02d"), pTm->tm_mon + 1, pTm->tm_mday, (pTm->tm_year + 1900)%1000);
		break;
	case Date_Format_10:
		_stprintf(pszTmp, _T("%02d/%02d/%04d"), pTm->tm_mday, pTm->tm_mon + 1, pTm->tm_year + 1900);
		break;
	case Date_Format_11:
		_stprintf(pszTmp, _T("%02d/%02d/%02d"), pTm->tm_mday, pTm->tm_mon + 1, (pTm->tm_year + 1900)%1000);
		break;
	default:
		_stprintf(pszTmp, _T("invalid DateFormat"));
	}
	return tstring(pszTmp);
}

tstring NS_Yutils::GetCurrTime(bool bMilliSeconds)
{
	timeb tb;
	ftime(&tb);

	tm *pTm = localtime(&tb.time);

	TCHAR pszTmp[32]; memset(pszTmp, 0, 32);
	if(bMilliSeconds)
		_stprintf(pszTmp, _T("%02d:%02d:%02d.%03d"), pTm->tm_hour, pTm->tm_min, pTm->tm_sec, tb.millitm);
	else
		_stprintf(pszTmp, _T("%02d:%02d:%02d"), pTm->tm_hour, pTm->tm_min, pTm->tm_sec);

	return tstring(pszTmp);
}

tstring NS_Yutils::GetCurrDateTime(DATE_FORMAT dformat, bool bMilliSeconds)
{
	return GetCurrDate(dformat) + _T(" ") + GetCurrTime(bMilliSeconds);
}

tstring NS_Yutils::GetAddedDate(int nAddedDays, DATE_FORMAT dformat)
{
	time_t t(0);
	time(&t);
	t += 24 * 3600 * nAddedDays;
	tm *pTm = localtime(&t);

	TCHAR pszTmp[32]; memset(pszTmp, 0, 32);
	switch (dformat)
	{
	case Date_Format_0:
		_stprintf(pszTmp, _T("%04d-%02d-%02d"), pTm->tm_year + 1900, pTm->tm_mon + 1, pTm->tm_mday);
		break;
	case Date_Format_1:
		_stprintf(pszTmp, _T("%02d-%02d-%02d"), (pTm->tm_year + 1900)%1000, pTm->tm_mon + 1, pTm->tm_mday);
		break;
	case Date_Format_2:
		_stprintf(pszTmp, _T("%04d%02d%02d"), pTm->tm_year + 1900, pTm->tm_mon + 1, pTm->tm_mday);
		break;
	case Date_Format_3:
		_stprintf(pszTmp, _T("%02d%02d%02d"), (pTm->tm_year + 1900)%1000, pTm->tm_mon + 1, pTm->tm_mday);
		break;
	case Date_Format_4:
		_stprintf(pszTmp, _T("%04d %02d %02d"), pTm->tm_year + 1900, pTm->tm_mon + 1, pTm->tm_mday);
		break;
	case Date_Format_5:
		_stprintf(pszTmp, _T("%02d %02d %02d"), (pTm->tm_year + 1900)%1000, pTm->tm_mon + 1, pTm->tm_mday);
		break;
	case Date_Format_7:
		_stprintf(pszTmp, _T("%02d/%02d/%02d"), (pTm->tm_year + 1900)%1000, pTm->tm_mon + 1, pTm->tm_mday);
		break;
	case Date_Format_8:
		_stprintf(pszTmp, _T("%02d/%02d/%04d"), pTm->tm_mon + 1, pTm->tm_mday, pTm->tm_year + 1900);
		break;
	case Date_Format_9:
		_stprintf(pszTmp, _T("%02d/%02d/%02d"), pTm->tm_mon + 1, pTm->tm_mday, (pTm->tm_year + 1900)%1000);
		break;
	case Date_Format_10:
		_stprintf(pszTmp, _T("%02d/%02d/%04d"), pTm->tm_mday, pTm->tm_mon + 1, pTm->tm_year + 1900);
		break;
	case Date_Format_11:
		_stprintf(pszTmp, _T("%02d/%02d/%02d"), pTm->tm_mday, pTm->tm_mon + 1, (pTm->tm_year + 1900)%1000);
		break;

	}
	return tstring(pszTmp);
}