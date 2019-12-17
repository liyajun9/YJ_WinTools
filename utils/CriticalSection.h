//  Convinient way to use Critical Section
//	Usage:
//	AnyFunc()
//	{
//		CYCriticalSectionLock(&cs, TRUE);
//		//other codes
//	}
// author:liyajun
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

public:
	inline void Lock(){
		::EnterCriticalSection(&m_cs);
	}

	inline bool TryLock(){
		return TryEnterCriticalSection(&m_cs) > 0 ? TRUE : FALSE;
	}

	inline void Unlock(){
		::LeaveCriticalSection(&m_cs);
	}

private:
	YCriticalSection();
	YCriticalSection(const YCriticalSection&);
	YCriticalSection& operator =(const YCriticalSection&);
	CRITICAL_SECTION& m_cs;
};