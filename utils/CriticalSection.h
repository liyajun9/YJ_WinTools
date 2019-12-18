#pragma once
#include <windows.h>
#include <exception>

class YCriticalSection
{
public:
	explicit YCriticalSection(CRITICAL_SECTION& cs)
	: m_cs(cs){
		::EnterCriticalSection(&m_cs);
	}

	~YCriticalSection(){
		::LeaveCriticalSection(&m_cs);
	}

private:
	YCriticalSection();
	YCriticalSection(const YCriticalSection&);
	YCriticalSection& operator =(const YCriticalSection&);
	CRITICAL_SECTION& m_cs;
};