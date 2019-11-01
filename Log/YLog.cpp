#include "stdafx.h"
#include "YLog.h"

using namespace NS_Yutils;

//Creat a global instance
CYLogger theLogger(_T(""), false,  static_cast<int>(CYLogger::LogItem::DateTime) | static_cast<int>(CYLogger::LogItem::ThreadId), 3);

CYLogger::CYLogger(tstring sLogFileDirectory, bool bAutoEndline ,int loggableItem, int nLogSavingDays):
m_sDirectory(sLogFileDirectory),m_bAutoEndline(bAutoEndline),m_loggableItem(loggableItem), m_nLogSavingDays(nLogSavingDays)
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

void CYLogger::Log(const char* pszData, ...)
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

void CYLogger::Log(const wchar_t* pwszData, ...)
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
	CYCriticalSectionLock(&m_cs, true);
	static bool bIsNewOpen = true;
	tstring sCurrDate = GetCurrDate(Date_Format_3);
	if(0 != m_sCurrDate.compare(sCurrDate)){
		m_stream.close();
		tstring sPath;
		sPath = m_sDirectory + _T("\\") + m_sCurrDate + _T(".log");
#if defined(UNICODE) || defined(_UNICODE)		
		m_stream.open((WCharToMB(sPath)).c_str(), std::ofstream::out|std::ofstream::app|std::ios::binary);
#else
		m_stream.open(sPath, std::ofstream::out|std::ofstream::app|std::ios::binary);
#endif
		m_stream << _T("\r\n********************************New Log*********************************") << std::endl;

		m_sCurrDate = sCurrDate;			
	}else{
		if(bIsNewOpen){
			tstring sExpireFileName = m_sDirectory + _T("\\") + GetAddedDate(0 - m_nLogSavingDays, Date_Format_3) + _T(".log");
			_tremove(sExpireFileName.c_str());

			const std::locale cn_loc("chs");
			m_stream.imbue(cn_loc);

			m_stream << _T("\r\n********************************New Log*********************************") << std::endl;
			bIsNewOpen = false;	
		}
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