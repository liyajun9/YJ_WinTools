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

class CYCriticalSectionLock
{
public:
	explicit CYCriticalSectionLock(CRITICAL_SECTION* pCS, bool bInitialLock = false){
		if(pCS == NULL)
			throw std::exception("Critical Section is null");
		m_pCS = pCS;
		if(bInitialLock)
			Lock();
	}

	~CYCriticalSectionLock(){
		Unlock();
	}

public:
	inline bool Lock(){
		return TryEnterCriticalSection(m_pCS) > 0 ? TRUE : FALSE;
	}
	inline void Unlock(){
		LeaveCriticalSection(m_pCS);
	}

private:
	CRITICAL_SECTION* m_pCS;
};