//  Logger
//	Usage:
//		CYLogger logger(_T(".\\ABC"),true);
//		logger.Log(CYLogger::Info, "abcde:附件里的撒娇了健康减肥的卡我");

//Note: character encodings of log files is GB2312
// author:liyajun

#pragma once
#include "tstring.h"
#include <Windows.h>
#include <fstream>
#include <iosfwd>
#include <stdarg.h>
#include "..\Utils\YTimeUtils.h"
#include "..\Utils\YCriticalSectionLock.h"
#include "..\Utils\YCharEncodings.h"
#include <direct.h>
#include <xlocale>
#include <wchar.h>
#include <system_error>

class CYLogger{
public:
	enum LogLevel
	{
		Info,
		Debug,
		Warn,
		Error
	};

	enum LogItem
	{
		DateTime	= 0x1,
		ThreadId	= 0x2
	};

public:
	CYLogger(tstring sLogFileDirectory, bool bAutoEndline = false,int loggableItem = static_cast<int>(DateTime) | static_cast<int>(ThreadId), int nLogSavingDays = 3):
	m_sDirectory(sLogFileDirectory),m_bAutoEndline(bAutoEndline),m_loggableItem(loggableItem), m_nLogSavingDays(nLogSavingDays)
	{
		InitializeCriticalSection(&m_cs);
		m_sCurrDate = CYTimeUtils::GetCurrDate(CYTimeUtils::Date_Format_3);
		_tmkdir(sLogFileDirectory.c_str());
		m_stream.open(m_sDirectory + _T("\\") + m_sCurrDate + _T(".log"), std::ofstream::out|std::ofstream::app|std::ios::binary);
	}

	~CYLogger()
	{
		m_stream.close();
		DeleteCriticalSection(&m_cs);
	}

	void Log(LogLevel logLevel, const char* pszData, ...)
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
		std::wstring sDataTmp = CYCharEncodings::MBToWChar(sData);
		write(sDataTmp.c_str(), logLevel);
#else
		write(sData.c_str(), logLevel);
#endif
	}

	void Log(LogLevel logLevel, const wchar_t* pwszData, ...)
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
		std::string sDataTmp = CYCharEncodings::WCharToMB(sData);
		write(sDataTmp.c_str(), logLevel);
#endif
	}

private:

	inline void write(const TCHAR* pData, LogLevel logLevel)
	{
		CYCriticalSectionLock(&m_cs, true);
		static bool bIsNewOpen = true;
		tstring sCurrDate = CYTimeUtils::GetCurrDate(CYTimeUtils::Date_Format_3);
		if(0 != m_sCurrDate.compare(sCurrDate)){
			m_stream.close();
			m_stream.open(m_sDirectory + _T("\\") + m_sCurrDate + _T(".log"), std::ofstream::out|std::ofstream::app|std::ios::binary);
			m_stream << _T("********************************New Log*********************************") << std::endl;

			m_sCurrDate = sCurrDate;			
		}else{
			if(bIsNewOpen){
				tstring sExpireFileName = m_sDirectory + _T("\\") + CYTimeUtils::GetAddedDate(0 - m_nLogSavingDays, CYTimeUtils::Date_Format_3) + _T(".log");
				_tremove(sExpireFileName.c_str());

				const std::locale cn_loc("chs");
				m_stream.imbue(cn_loc);

				m_stream << _T("********************************New Log*********************************") << std::endl;
				bIsNewOpen = false;	
			}
		}

		if(m_loggableItem & static_cast<int>(DateTime)){
			m_stream<<CYTimeUtils::GetCurrDateTime(CYTimeUtils::Date_Format_3, true);
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



private:
	CRITICAL_SECTION m_cs;
	
	bool m_bAutoEndline;
	int m_loggableItem;
	int m_nLogSavingDays;
	tstring m_sDirectory;
	tstring m_sCurrDate;

	tofstream m_stream;
};
