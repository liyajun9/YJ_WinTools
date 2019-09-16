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

#define LOG_OUT theLogger.Log

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
	CYLogger(tstring sLogFileDirectory,		// log directory. support only one sub-directory. empty indicates current path.
						bool bAutoEndline = false,	// whether auto add end of line
						int loggableItem = static_cast<int>(DateTime) | static_cast<int>(ThreadId), //prefix of each line includings
						int nLogSavingDays = 3);			// saving log for days
	~CYLogger();

	void Log( const char* pszData, ...); //loglevel is info by default
	void Log(LogLevel logLevel, const char* pszData, ...);	

	void Log(const wchar_t* pwszData, ...);
	void Log(LogLevel logLevel, const wchar_t* pwszData, ...);

private:
	CYLogger();
	inline void write(const TCHAR* pData, LogLevel logLevel);

private:
	CRITICAL_SECTION m_cs;
	
	bool m_bAutoEndline;
	int m_loggableItem;
	int m_nLogSavingDays;
	tstring m_sDirectory;
	tstring m_sCurrDate;

	tofstream m_stream;
};

extern CYLogger theLogger;