//  Logger
//	Usage:
//
// author:liyajun

#pragma once
#include "tstring.h"
#include <Windows.h>
#include <fstream>
#include <iosfwd>
#include <stdarg.h>
#include "..\Utils\YTimeUtils.h"
#include "..\Utils\YCriticalSectionLock.h"
#include "..\Utils\Yencodings.h"

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
	CYLogger(std::string sLogFileDirectory, int loggableItem = static_cast<int>(DateTime) | static_cast<int>(ThreadId), int nLogSavingDays = 3):
	m_sDirectory(sLogFileDirectory),m_loggableItem(loggableItem), m_nLogSavingDays(nLogSavingDays)
	{
		InitializeCriticalSection(&m_cs);
		m_sCurrDate = CYTimeUtils::GetCurrDate(CYTimeUtils::Date_Format_3);
		m_stream.open(m_sDirectory + "\\" + m_sCurrDate + ".log", std::ofstream::out|std::ofstream::app);
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
		write(sData.c_str(), logLevel);
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
		std::string sDataTmp = CYEncodings::WCharToMB(sData);
		write(sDataTmp.c_str(), logLevel);
	}

private:

	inline void write(const char* pData, LogLevel logLevel)
	{
		CYCriticalSectionLock(&m_cs, true);
		static bool bIsNewOpen = true;
		std::string sCurrDate = CYTimeUtils::GetCurrDate(CYTimeUtils::Date_Format_3);
		if(0 != m_sCurrDate.compare(sCurrDate)){
			m_stream.close();
			m_stream.open(m_sDirectory + "\\" + m_sCurrDate + ".log", std::ofstream::out|std::ofstream::app);
			m_stream << "********************************New Log*********************************" << std::endl;

			m_sCurrDate = sCurrDate;			
		}else{
			if(bIsNewOpen){
				std::string sExpireFileName = m_sDirectory + "\\" + CYTimeUtils::GetAddedDate(0 - m_nLogSavingDays, CYTimeUtils::Date_Format_3) + ".log";
				remove(sExpireFileName.c_str());

				m_stream << "********************************New Log*********************************" << std::endl;
				bIsNewOpen = false;
			}
		}

		if(m_loggableItem & static_cast<int>(DateTime)){
			m_stream<<CYTimeUtils::GetCurrDateTime(CYTimeUtils::Date_Format_3, true);
		}
		if(m_loggableItem & static_cast<int>(ThreadId)){
			m_stream<<"["<<GetCurrentThreadId()<<"]";
		}
		switch (logLevel)
		{
		case Info:
			m_stream<<"[INF]";
			break;
		case Debug:
			m_stream<<"[DBG]";
			break;
		case Warn:
			m_stream<<"[WRN]";
			break;
		case Error:
			m_stream<<"[ERR]";
			break;
		default:
			m_stream<<"[INF]";
			break;
		}
		m_stream<<" "<<pData<<std::endl;
	}



private:
	CRITICAL_SECTION m_cs;
	
	int m_loggableItem;
	int m_nLogSavingDays;
	std::string m_sDirectory;
	std::string m_sCurrDate;

	std::ofstream m_stream;
};
