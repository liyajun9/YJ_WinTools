//  Logger
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

#define LOG_INFO theLogger.LogInfo
#define LOG_DEBUG theLogger.LogDebug
#define LOG_WARN theLogger.LogWarn
#define LOG_ERROR theLogger.LogError

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
						int nExpireLogDays = 7);			// saving log for days
	~CYLogger();

	void LogInfo(const char* pszData, ...); 
	void LogInfo(const wchar_t* pwszData, ...);
	void LogDebug(const char* pszData, ...); 
	void LogDebug(const wchar_t* pwszData, ...);
	void LogWarn(const char* pszData, ...); 
	void LogWarn(const wchar_t* pwszData, ...);
	void LogError(const char* pszData, ...); 
	void LogError(const wchar_t* pwszData, ...);

	void Log(LogLevel logLevel, const char* pszData, ...);	
	void Log(LogLevel logLevel, const wchar_t* pwszData, ...);

private:
	CYLogger();
	void write(const TCHAR* pData, LogLevel logLevel);
	void DeleteExpiredOrInvalidLog();
	bool IsFreshValidLog(tstring sFileName);

private:
	CRITICAL_SECTION m_cs;
	
	bool m_bAutoEndline;
	int m_loggableItem;
	int m_nExpireLogDays;
	tstring m_sDirectory;
	tstring m_sCurrDate;

	tofstream m_stream;
};

extern CYLogger theLogger;