#include "stdafx.h"
#include "YLog.h"

#pragma warning(disable:4482)
#pragma warning(disable:4996)

using namespace NS_Yutils;

//Creat a global instance
CYLogger theLogger(_T("Logs"), false,  static_cast<int>(CYLogger::LogItem::DateTime) | static_cast<int>(CYLogger::LogItem::ThreadId), 3);

CYLogger::CYLogger(tstring sLogFileDirectory, bool bAutoEndline ,int loggableItem, int nExpireLogDays):
m_sDirectory(sLogFileDirectory),m_bAutoEndline(bAutoEndline),m_loggableItem(loggableItem), m_nExpireLogDays(nExpireLogDays)
{
	InitializeCriticalSection(&m_cs);
	m_sCurrDate = GetCurrDate(Date_Format_3);
	tstring sPath;

	if(m_sDirectory.empty()){
		sPath = m_sCurrDate + _T(".log");
	}else{
		_tmkdir(m_sDirectory.c_str());
		sPath = m_sDirectory + _T("\\") + m_sCurrDate + _T(".log");
	}
#if defined(UNICODE) || defined(_UNICODE)		
	m_stream.open((WCharToMB(sPath)).c_str(), std::ofstream::out|std::ofstream::app|std::ios::binary);
#else
	m_stream.open(sPath, std::ofstream::out|std::ofstream::app|std::ios::binary);
#endif
}

CYLogger::~CYLogger()
{
	m_stream.close();
	DeleteCriticalSection(&m_cs);
}

void CYLogger::LogInfo(const char* pszData, ...)
{
	std::string sData;
	va_list argList;
	va_start(argList, pszData);
	size_t nSize = _vscprintf(pszData, argList);
	if(sData.capacity() < (nSize + 1))
		sData.resize(nSize + 1);

	vsprintf((char*)sData.data(), pszData, argList);
	va_end(argList);

#if defined(UNICODE) || defined(_UNICODE)		
	std::wstring sDataTmp = MBToWChar(sData);
	write(sDataTmp.c_str(), LogLevel::Info);
#else
	write(sData.c_str(), LogLevel::Info);
#endif
}

void CYLogger::LogInfo(const wchar_t* pwszData, ...)
{
	std::wstring sData;
	va_list argList;
	va_start(argList, pwszData);
	size_t nSize = _vscwprintf(pwszData, argList);
	if(sData.capacity() < (nSize + 2))
		sData.resize(nSize + 2);

	vswprintf((wchar_t*)sData.data(), pwszData, argList);
	va_end(argList);

#if defined(UNICODE) || defined(_UNICODE)
	write(sData.c_str(), LogLevel::Info);
#else
	std::string sDataTmp = WCharToMB(sData);
	write(sDataTmp.c_str(), LogLevel::Info);
#endif
}

void CYLogger::LogDebug(const char* pszData, ...)
{
	std::string sData;
	va_list argList;
	va_start(argList, pszData);
	size_t nSize = _vscprintf(pszData, argList);
	if(sData.capacity() < (nSize + 1))
		sData.resize(nSize + 1);

	vsprintf((char*)sData.data(), pszData, argList);
	va_end(argList);

#if defined(UNICODE) || defined(_UNICODE)		
	std::wstring sDataTmp = MBToWChar(sData);
	write(sDataTmp.c_str(), LogLevel::Debug);
#else
	write(sData.c_str(), LogLevel::Debug);
#endif
}

void CYLogger::LogDebug(const wchar_t* pwszData, ...)
{
	std::wstring sData;
	va_list argList;
	va_start(argList, pwszData);
	size_t nSize = _vscwprintf(pwszData, argList);
	if(sData.capacity() < (nSize + 2))
		sData.resize(nSize + 2);

	vswprintf((wchar_t*)sData.data(), pwszData, argList);
	va_end(argList);

#if defined(UNICODE) || defined(_UNICODE)
	write(sData.c_str(), LogLevel::Debug);
#else
	std::string sDataTmp = WCharToMB(sData);
	write(sDataTmp.c_str(), LogLevel::Debug);
#endif
}

void CYLogger::LogWarn(const char* pszData, ...)
{
	std::string sData;
	va_list argList;
	va_start(argList, pszData);
	size_t nSize = _vscprintf(pszData, argList);
	if(sData.capacity() < (nSize + 1))
		sData.resize(nSize + 1);

	vsprintf((char*)sData.data(), pszData, argList);
	va_end(argList);

#if defined(UNICODE) || defined(_UNICODE)		
	std::wstring sDataTmp = MBToWChar(sData);
	write(sDataTmp.c_str(), LogLevel::Warn);
#else
	write(sData.c_str(), LogLevel::Warn);
#endif
}

void CYLogger::LogWarn(const wchar_t* pwszData, ...)
{
	std::wstring sData;
	va_list argList;
	va_start(argList, pwszData);
	size_t nSize = _vscwprintf(pwszData, argList);
	if(sData.capacity() < (nSize + 2))
		sData.resize(nSize + 2);

	vswprintf((wchar_t*)sData.data(), pwszData, argList);
	va_end(argList);

#if defined(UNICODE) || defined(_UNICODE)
	write(sData.c_str(), LogLevel::Warn);
#else
	std::string sDataTmp = WCharToMB(sData);
	write(sDataTmp.c_str(), LogLevel::Warn);
#endif
}

void CYLogger::LogError(const char* pszData, ...)
{
	std::string sData;
	va_list argList;
	va_start(argList, pszData);
	size_t nSize = _vscprintf(pszData, argList);
	if(sData.capacity() < (nSize + 1))
		sData.resize(nSize + 1);

	vsprintf((char*)sData.data(), pszData, argList);
	va_end(argList);

#if defined(UNICODE) || defined(_UNICODE)		
	std::wstring sDataTmp = MBToWChar(sData);
	write(sDataTmp.c_str(), LogLevel::Error);
#else
	write(sData.c_str(), LogLevel::Error);
#endif
}

void CYLogger::LogError(const wchar_t* pwszData, ...)
{
	std::wstring sData;
	va_list argList;
	va_start(argList, pwszData);
	size_t nSize = _vscwprintf(pwszData, argList);
	if(sData.capacity() < (nSize + 2))
		sData.resize(nSize + 2);

	vswprintf((wchar_t*)sData.data(), pwszData, argList);
	va_end(argList);

#if defined(UNICODE) || defined(_UNICODE)
	write(sData.c_str(), LogLevel::Error);
#else
	std::string sDataTmp = WCharToMB(sData);
	write(sDataTmp.c_str(), LogLevel::Error);
#endif
}

void CYLogger::Log(LogLevel logLevel, const char* pszData, ...)
{
	std::string sData;
	va_list argList;
	va_start(argList, pszData);
	size_t nSize = _vscprintf(pszData, argList);
	if(sData.capacity() < (nSize + 1))
		sData.resize(nSize + 1);

	vsprintf((char*)sData.data(), pszData, argList);
	va_end(argList);

#if defined(UNICODE) || defined(_UNICODE)		
	std::wstring sDataTmp = MBToWChar(sData);
	write(sDataTmp.c_str(), logLevel);
#else
	write(sData.c_str(), logLevel);
#endif
}

void CYLogger::Log(LogLevel logLevel, const wchar_t* pwszData, ...)
{
	std::wstring sData;
	va_list argList;
	va_start(argList, pwszData);
	size_t nSize = _vscwprintf(pwszData, argList);
	if(sData.capacity() < (nSize + 2))
		sData.resize(nSize + 2);

	vswprintf((wchar_t*)sData.data(), pwszData, argList);
	va_end(argList);

#if defined(UNICODE) || defined(_UNICODE)
	write(sData.c_str(), logLevel);
#else
	std::string sDataTmp = WCharToMB(sData);
	write(sDataTmp.c_str(), logLevel);
#endif
}

void CYLogger::write(const TCHAR* pData, LogLevel logLevel)
{
	static bool bIsFirstRun = true;
	bool bIsNewDay = false;

	tstring sCurrDate = GetCurrDate(Date_Format_3);
	 bIsNewDay = m_sCurrDate.compare(sCurrDate)!=0;

	 CYCriticalSectionLock(&m_cs, true);
	if(bIsFirstRun || bIsNewDay){//delete expired log files
		DeleteExpiredOrInvalidLog();
	}

	if(bIsNewDay){ //refresh m_stream
		m_sCurrDate = sCurrDate;
		m_stream.close();
		tstring sPath;
		sPath = m_sDirectory + _T("\\") + m_sCurrDate + _T(".log");
#if defined(UNICODE) || defined(_UNICODE)		
		m_stream.open((WCharToMB(sPath)).c_str(), std::ofstream::out|std::ofstream::app|std::ios::binary);
#else
		m_stream.open(sPath, std::ofstream::out|std::ofstream::app|std::ios::binary);
#endif
		const std::locale cn_loc("chs");
		m_stream.imbue(cn_loc);
	}

	if(bIsFirstRun){ //write header
		m_stream << _T("\r\n********************************New Log*********************************") << std::endl;
		bIsFirstRun = false;
	}	

	if(m_loggableItem & static_cast<int>(DateTime)){
		m_stream<<GetCurrDateTime(Date_Format_3, true);
	}
	if(m_loggableItem & static_cast<int>(ThreadId)){
		m_stream<<_T("[")<<GetCurrentThreadId()<<_T("]");
	}
	switch (logLevel)
	{
	case Info:
		m_stream<<_T("[INF]");
		break;
	case Debug:
		m_stream<<_T("[DBG]");
		break;
	case Warn:
		m_stream<<_T("[WRN]");
		break;
	case Error:
		m_stream<<_T("[ERR]");
		break;
	default:
		m_stream<<_T("[INF]");
		break;
	}
	if(m_bAutoEndline)
		m_stream<<_T(" ")<<pData<<std::endl;
	else
		m_stream<<_T(" ")<<pData;
	m_stream.flush();
}

void CYLogger::DeleteExpiredOrInvalidLog()
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

bool CYLogger::IsFreshValidLog(tstring sFileName)
{
	tstring::size_type nPos = sFileName.find_last_of(_T('.'));
	if(nPos != tstring::npos){
		sFileName = sFileName.substr(0,nPos);
	}

	if(sFileName.length() == 6){
		if(sFileName.find_first_not_of(_T("0123456789")) == tstring::npos){
			tstring sExpireDate = GetAddedDate(0 - m_nExpireLogDays, Date_Format_3);
			if(sFileName.compare(sExpireDate) > 0)
				return true;
		}
	}
	 return false;
}