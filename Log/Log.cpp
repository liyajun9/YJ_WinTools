#include "stdafx.h"
#include "Log.h"

#pragma warning(disable:4482)
#pragma warning(disable:4996)

YLog yLog(_T("log"), true,  YLog::ELogItem::DATETIME | YLog::ELogItem::THREADID, 3);

YLog::YLog(tstring sLogFileDirectory, bool bAutoEndline ,int loggableItem, int nExpireLogDays):
m_sDirectory(sLogFileDirectory),m_bAutoEndline(bAutoEndline),m_loggableItem(loggableItem), m_nExpireLogDays(nExpireLogDays)
{
	InitializeCriticalSection(&m_cs);
	m_sCurrDate = GetCurrDate(NS_Yutils::Date_Format_3);
	tstring sPath;

	if(m_sDirectory.empty()){
		sPath = m_sCurrDate + _T(".log");
	}else{
		_tmkdir(m_sDirectory.c_str());
		sPath = m_sDirectory + _T("\\") + m_sCurrDate + _T(".log");
	}
#if defined(UNICODE) || defined(_UNICODE)		
	m_stream.open((NS_Yutils::WCharToMB(sPath)).c_str(), std::ofstream::out|std::ofstream::app|std::ios::binary);
#else
	m_stream.open(sPath.c_str(), std::ofstream::out|std::ofstream::app|std::ios::binary);
#endif
}

YLog::~YLog()
{
	m_stream.close();
	DeleteCriticalSection(&m_cs);
}

void YLog::LogInfo(const char* pszData, ...)
{
	if(!(LOG_LEVEL & ELogType::Info)) return;

	std::string sData;
	va_list argList;
	va_start(argList, pszData);
	size_t nSize = _vscprintf(pszData, argList);
	if(sData.capacity() < (nSize + 1))
		sData.resize(nSize + 1);

	vsprintf((char*)sData.data(), pszData, argList);
	va_end(argList);

#if defined(UNICODE) || defined(_UNICODE)		
	std::wstring sDataTmp = NS_Yutils::MBToWChar(sData);
	write(sDataTmp.c_str(), ELogType::Info);
#else
	write(sData.c_str(), ELogType::Info);
#endif
}

void YLog::LogInfo(const wchar_t* pwszData, ...)
{
	if(!(LOG_LEVEL & ELogType::Info)) return;

	std::wstring sData;
	va_list argList;
	va_start(argList, pwszData);
	size_t nSize = _vscwprintf(pwszData, argList);
	if(sData.capacity() < (nSize + 2))
		sData.resize(nSize + 2);

	vswprintf((wchar_t*)sData.data(), pwszData, argList);
	va_end(argList);

#if defined(UNICODE) || defined(_UNICODE)
	write(sData.c_str(), ELogType::Info);
#else
	std::string sDataTmp = WCharToMB(sData);
	write(sDataTmp.c_str(), ELogType::Info);
#endif
}

void YLog::LogDebug(const char* pszData, ...)
{
	if(!(LOG_LEVEL & ELogType::Debug)) return;

	std::string sData;
	va_list argList;
	va_start(argList, pszData);
	size_t nSize = _vscprintf(pszData, argList);
	if(sData.capacity() < (nSize + 1))
		sData.resize(nSize + 1);

	vsprintf((char*)sData.data(), pszData, argList);
	va_end(argList);

#if defined(UNICODE) || defined(_UNICODE)		
	std::wstring sDataTmp = NS_Yutils::MBToWChar(sData);
	write(sDataTmp.c_str(), ELogType::Debug);
#else
	write(sData.c_str(), ELogType::Debug);
#endif
}

void YLog::LogDebug(const wchar_t* pwszData, ...)
{
	if(!(LOG_LEVEL & ELogType::Debug)) return;

	std::wstring sData;
	va_list argList;
	va_start(argList, pwszData);
	size_t nSize = _vscwprintf(pwszData, argList);
	if(sData.capacity() < (nSize + 2))
		sData.resize(nSize + 2);

	vswprintf((wchar_t*)sData.data(), pwszData, argList);
	va_end(argList);

#if defined(UNICODE) || defined(_UNICODE)
	write(sData.c_str(), ELogType::Debug);
#else
	std::string sDataTmp = WCharToMB(sData);
	write(sDataTmp.c_str(), ELogType::Debug);
#endif
}

void YLog::LogWarn(const char* pszData, ...)
{
	if(!(LOG_LEVEL & ELogType::Warn)) return;

	std::string sData;
	va_list argList;
	va_start(argList, pszData);
	size_t nSize = _vscprintf(pszData, argList);
	if(sData.capacity() < (nSize + 1))
		sData.resize(nSize + 1);

	vsprintf((char*)sData.data(), pszData, argList);
	va_end(argList);

#if defined(UNICODE) || defined(_UNICODE)		
	std::wstring sDataTmp = NS_Yutils::MBToWChar(sData);
	write(sDataTmp.c_str(), ELogType::Warn);
#else
	write(sData.c_str(), ELogType::Warn);
#endif
}

void YLog::LogWarn(const wchar_t* pwszData, ...)
{
	if(!(LOG_LEVEL & ELogType::Warn)) return;

	std::wstring sData;
	va_list argList;
	va_start(argList, pwszData);
	size_t nSize = _vscwprintf(pwszData, argList);
	if(sData.capacity() < (nSize + 2))
		sData.resize(nSize + 2);

	vswprintf((wchar_t*)sData.data(), pwszData, argList);
	va_end(argList);

#if defined(UNICODE) || defined(_UNICODE)
	write(sData.c_str(), ELogType::Warn);
#else
	std::string sDataTmp = WCharToMB(sData);
	write(sDataTmp.c_str(), ELogType::Warn);
#endif
}

void YLog::LogError(const char* pszData, ...)
{
	if(!(LOG_LEVEL & ELogType::Error)) return;

	std::string sData;
	va_list argList;
	va_start(argList, pszData);
	size_t nSize = _vscprintf(pszData, argList);
	if(sData.capacity() < (nSize + 1))
		sData.resize(nSize + 1);

	vsprintf((char*)sData.data(), pszData, argList);
	va_end(argList);

#if defined(UNICODE) || defined(_UNICODE)		
	std::wstring sDataTmp = NS_Yutils::MBToWChar(sData);
	write(sDataTmp.c_str(), ELogType::Error);
#else
	write(sData.c_str(), ELogType::Error);
#endif
}

void YLog::LogError(const wchar_t* pwszData, ...)
{
	if(!(LOG_LEVEL & ELogType::Error)) return;

	std::wstring sData;
	va_list argList;
	va_start(argList, pwszData);
	size_t nSize = _vscwprintf(pwszData, argList);
	if(sData.capacity() < (nSize + 2))
		sData.resize(nSize + 2);

	vswprintf((wchar_t*)sData.data(), pwszData, argList);
	va_end(argList);

#if defined(UNICODE) || defined(_UNICODE)
	write(sData.c_str(), ELogType::Error);
#else
	std::string sDataTmp = WCharToMB(sData);
	write(sDataTmp.c_str(), ELogType::Error);
#endif
}

void YLog::LogFatal(const char* pszData, ...)
{
	if(!(LOG_LEVEL & ELogType::Fatal)) return;

	std::string sData;
	va_list argList;
	va_start(argList, pszData);
	size_t nSize = _vscprintf(pszData, argList);
	if(sData.capacity() < (nSize + 1))
		sData.resize(nSize + 1);

	vsprintf((char*)sData.data(), pszData, argList);
	va_end(argList);

#if defined(UNICODE) || defined(_UNICODE)		
	std::wstring sDataTmp = NS_Yutils::MBToWChar(sData);
	write(sDataTmp.c_str(), ELogType::Fatal);
#else
	write(sData.c_str(), ELogType::Fatal);
#endif
}

void YLog::LogFatal(const wchar_t* pwszData, ...)
{
	if(!(LOG_LEVEL & ELogType::Fatal)) return;

	std::wstring sData;
	va_list argList;
	va_start(argList, pwszData);
	size_t nSize = _vscwprintf(pwszData, argList);
	if(sData.capacity() < (nSize + 2))
		sData.resize(nSize + 2);

	vswprintf((wchar_t*)sData.data(), pwszData, argList);
	va_end(argList);

#if defined(UNICODE) || defined(_UNICODE)
	write(sData.c_str(), ELogType::Fatal);
#else
	std::string sDataTmp = WCharToMB(sData);
	write(sDataTmp.c_str(), ELogType::Fatal);
#endif
}

void YLog::Log(ELogType logType, const char* pszData, ...)
{
	if(!(LOG_LEVEL & logType)) return;

	std::string sData;
	va_list argList;
	va_start(argList, pszData);
	size_t nSize = _vscprintf(pszData, argList);
	if(sData.capacity() < (nSize + 1))
		sData.resize(nSize + 1);

	vsprintf((char*)sData.data(), pszData, argList);
	va_end(argList);

#if defined(UNICODE) || defined(_UNICODE)		
	std::wstring sDataTmp = NS_Yutils::MBToWChar(sData);
	write(sDataTmp.c_str(), logType);
#else
	write(sData.c_str(), logType);
#endif
}

void YLog::Log(ELogType logType, const wchar_t* pwszData, ...)
{
	if(!(LOG_LEVEL & logType)) return;

	std::wstring sData;
	va_list argList;
	va_start(argList, pwszData);
	size_t nSize = _vscwprintf(pwszData, argList);
	if(sData.capacity() < (nSize + 2))
		sData.resize(nSize + 2);

	vswprintf((wchar_t*)sData.data(), pwszData, argList);
	va_end(argList);

#if defined(UNICODE) || defined(_UNICODE)
	write(sData.c_str(), logType);
#else
	std::string sDataTmp = WCharToMB(sData);
	write(sDataTmp.c_str(), logType);
#endif
}

void YLog::write(const TCHAR* pData, ELogType logLevel)
{
	YCriticalSection cs(m_cs);

	static bool bIsFirstRun = true;
	bool bIsNewDay = false;

	tstring sCurrDate = GetCurrDate(NS_Yutils::Date_Format_3);
	 bIsNewDay = m_sCurrDate.compare(sCurrDate)!=0;

	if(bIsFirstRun || bIsNewDay){//delete expired log files
		DeleteExpiredOrInvalidLog();
	}

	if(bIsNewDay){ //refresh m_stream
		m_sCurrDate = sCurrDate;
		m_stream.close();
		tstring sPath;
		sPath = m_sDirectory + _T("\\") + m_sCurrDate + _T(".log");
#if defined(UNICODE) || defined(_UNICODE)		
		m_stream.open((NS_Yutils::WCharToMB(sPath)).c_str(), std::ofstream::out|std::ofstream::app|std::ios::binary);
#else
		m_stream.open(sPath.c_str(), std::ofstream::out|std::ofstream::app|std::ios::binary);
#endif
		if(!m_stream)
			return;

		const std::locale cn_loc("chs");
		m_stream.imbue(cn_loc);
	}

	m_strstr.clear();
	m_strstr.str(_T(""));
	if(bIsFirstRun){ //write header
		m_strstr << _T("\r\n********************************New Log*********************************") << std::endl;
		bIsFirstRun = false;
	}	

	if(m_loggableItem & static_cast<int>(DATETIME)){
		m_strstr<<GetCurrDateTime(NS_Yutils::Date_Format_3, true);
	}
	if(m_loggableItem & static_cast<int>(THREADID)){
		m_strstr<<_T("[")<<GetCurrentThreadId()<<_T("]");
	}
	switch (logLevel)
	{
	case Debug:
		m_strstr<<_T("[debug]");
		break;
	case Info:
		m_strstr<<_T("[info]");
		break;
	case Warn:
		m_strstr<<_T("[warn]");
		break;
	case Error:
		m_strstr<<_T("[error]");
		break;
	case Fatal:
		m_strstr<<_T("[fatal]");
		break;
	default:
		m_strstr<<_T("[unknown]");
		break;
	}
	if(m_bAutoEndline)
		m_strstr<<_T(" ")<<pData<<std::endl;
	else
		m_strstr<<_T(" ")<<pData;

	m_stream<<m_strstr.str()<<std::flush;
}

void YLog::DeleteExpiredOrInvalidLog()
{
	HANDLE hFind = INVALID_HANDLE_VALUE;
	WIN32_FIND_DATA ffd;

	tstring sWildcard = m_sDirectory;
	sWildcard.append(_T("\\*.*"));
	hFind = FindFirstFile(sWildcard.c_str(), &ffd);
	if(hFind == INVALID_HANDLE_VALUE)
		return;

	TCHAR pszFile[MAX_PATH];
	tstring::size_type nLen = m_sDirectory.length();
	memset(pszFile, 0, MAX_PATH);
	memcpy(pszFile, m_sDirectory.c_str(),nLen);
	do{
		if(_tcscmp(ffd.cFileName, _T(".")) != 0 && _tcscmp(ffd.cFileName, _T("..")) != 0){
			if(ffd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY){
				continue;
			}else{
				if(!IsFreshValidLog(ffd.cFileName)){
					memset(pszFile + nLen, 0, MAX_PATH - nLen);
					memcpy(pszFile + nLen, _T("\\"), 1);
					memcpy(pszFile + nLen + 1, ffd.cFileName, _tcslen(ffd.cFileName));
					_tremove(pszFile);
				}
			}
		}
	}while(FindNextFile(hFind, &ffd) != 0);

	FindClose(hFind);
	hFind = INVALID_HANDLE_VALUE;
}

bool YLog::IsFreshValidLog(tstring sFileName)
{
	tstring::size_type nPos = sFileName.find_last_of(_T('.'));
	if(nPos != tstring::npos){
		sFileName = sFileName.substr(0,nPos);
	}

	if(sFileName.length() == 6){
		if(sFileName.find_first_not_of(_T("0123456789")) == tstring::npos){
			tstring sExpireDate = NS_Yutils::GetAddedDate(0 - m_nExpireLogDays, NS_Yutils::Date_Format_3);
			if(sFileName.compare(sExpireDate) > 0)
				return true;
		}
	}
	 return false;
}