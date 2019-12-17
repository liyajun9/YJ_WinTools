//  Logger
//Note: character encodings of log files is GB2312
// author:liyajun

#pragma once
#include "tstring.h"
#include <Windows.h>
#include <fstream>
#include <iosfwd>
#include <stdarg.h>
#include "..\Utils\TimeUtils.h"
#include "..\Utils\CriticalSection.h"
#include "..\Utils\CharEncodings.h"
#include <direct.h>
#include <xlocale>
#include <wchar.h>

#if(defined DEBUG || defined _DEBUG)
#define LOG_LEVEL		LOG_LEVEL_DEBUG
#else
#define LOG_LEVEL		LOG_LEVEL_WARN
#endif

#define LOG_LEVEL_FATAL			ELogType::Fatal
#define LOG_LEVEL_ERROR		(LOG_LEVEL_FATAL|ELogType::Error)
#define LOG_LEVEL_WARN		(LOG_LEVEL_ERROR|ELogType::Warn)
#define LOG_LEVEL_INFO			(LOG_LEVEL_WARN|ELogType::Info)
#define LOG_LEVEL_DEBUG		(LOG_LEVEL_INFO|ELogType::Debug)
#define LOG_LEVEL_ALL				0xff
#define LOG_LEVEL_NONE		0x00

#define LOG_DEBUG yLog.LogDebug
#define LOG_INFO yLog.LogInfo
#define LOG_WARN yLog.LogWarn
#define LOG_ERROR yLog.LogError
#define LOG_FATAL yLog.LogFatal

class YLog{
public:
	enum ELogType
	{
		Fatal = 0x01,
		Error = 0x02,
		Warn = 0x04,
		Info = 0x08,
		Debug = 0x10
	};

	enum ELogItem
	{
		DATETIME	= 0x01,
		THREADID	= 0x02
	};

public:
	explicit YLog(tstring sLogFileDirectory,		// log directory. support only one sub-directory. empty indicates current path.
						bool bAutoEndline = false,	// whether auto add end of line
						int loggableItem = static_cast<int>(DATETIME) | static_cast<int>(THREADID), //prefix of each line includings
						int nExpireLogDays = 7);			// saving log for days
	~YLog();

	void LogDebug(const char* pszData, ...); 
	void LogDebug(const wchar_t* pwszData, ...);
	void LogInfo(const char* pszData, ...); 
	void LogInfo(const wchar_t* pwszData, ...);
	void LogWarn(const char* pszData, ...); 
	void LogWarn(const wchar_t* pwszData, ...);
	void LogError(const char* pszData, ...); 
	void LogError(const wchar_t* pwszData, ...);
	void LogFatal(const char* pszData, ...); 
	void LogFatal(const wchar_t* pwszData, ...);

	void Log(ELogType logType, const char* pszData, ...);	
	void Log(ELogType logType, const wchar_t* pwszData, ...);

private:
	YLog();
	YLog(const YLog& rhs);
	YLog& operator =(const YLog& rhs);

	void write(const TCHAR* pData, ELogType logLevel);
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

extern YLog yLog;