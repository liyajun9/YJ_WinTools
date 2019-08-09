// trace
// Example: 
//		YTRACE(_T("debug output variable value = %d"), var);
//
//      will output:
//			2018-07-01 11:33:20 debug output variable value = 5
// author:liyajun
#pragma once

#ifdef _DEBUG
#define YTRACE CYtrace::_trace
#else
#define YTRACE(x)
#endif

#define TRACE_BUFFER_LEN 1024
#define DATETIME_LEN 20

class CYTrace{
public:
	static void CYTrace::_trace(const char *format, ...)
	{
		char buffer[TRACE_BUFFER_LEN];
		memset(buffer, 0, TRACE_BUFFER_LEN);

		time_t t = time(NULL);
		struct tm tmCur;
		localtime_s(&tmCur, &t); 
		sprintf_s(buffer,TRACE_BUFFER_LEN, "%04d-%02d-%02d %02d:%02d:%02d ", 
			tmCur.tm_year + 1900, 
			tmCur.tm_mon + 1,
			tmCur.tm_mday,
			tmCur.tm_hour,
			tmCur.tm_min,
			tmCur.tm_sec);

		va_list argptr;
		va_start(argptr, format);
		wvsprintfA(buffer + DATETIME_LEN, format, argptr);
		va_end(argptr);			

		OutputDebugStringA(buffer);
		OutputDebugStringA("\r\n");
	}

	static void CYTrace::_trace(const wchar_t *format, ...)
	{
		wchar_t buffer[TRACE_BUFFER_LEN];
		memset(buffer, 0, TRACE_BUFFER_LEN);

		time_t t = time(NULL);
		struct tm tmCur;
		localtime_s(&tmCur, &t); 
		wsprintf(buffer, _T("%04d-%02d-%02d %02d:%02d:%02d "), 
			tmCur.tm_year + 1900, 
			tmCur.tm_mon + 1,
			tmCur.tm_mday,
			tmCur.tm_hour,
			tmCur.tm_min,
			tmCur.tm_sec);

		va_list argptr;
		va_start(argptr, format);
		wvsprintfW(buffer + DATETIME_LEN, format, argptr);
		va_end(argptr);

		OutputDebugStringW(buffer);
		OutputDebugStringW(_T("\r\n"));
	}

private:
	CYTrace::CTrace(){}
	CYTrace::~CTrace(){}
};

