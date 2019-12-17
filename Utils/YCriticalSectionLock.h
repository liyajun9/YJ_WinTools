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

class CYCriticalSection
{
public:
	explicit CYCriticalSection(CRITICAL_SECTION& cs)
	: m_cs(cs){
		::EnterCriticalSection(&m_cs);
	}

	~CYCriticalSection(){
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
	CYCriticalSection();
	CYCriticalSection(const CYCriticalSection&);
	CYCriticalSection& operator =(const CYCriticalSection&);
	CRITICAL_SECTION& m_cs;
};