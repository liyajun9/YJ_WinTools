#include "pch.h"
#include "Event.h"
#include "exceptions\SystemException.h"

YEvent::YEvent( LPSECURITY_ATTRIBUTES lpSecurityAttributes, bool bManualReset, bool initState, const tstring& sName/*  = _T("")*/)
{
	if((m_hEvent = CreateEvent(lpSecurityAttributes, bManualReset, initState, sName.c_str())) == INVALID_HANDLE_VALUE)
		throw YSystemException("Event", "YEvent");
}

YEvent::~YEvent()
{
	CloseHandle(m_hEvent);
}

HANDLE YEvent::GetEvent() const
{
	return m_hEvent;
}

DWORD YEvent::Wait() const
{
	return WaitForSingleObject(m_hEvent, INFINITE);
}
bool YEvent::Wait(DWORD timeoutMillis) const
{
	DWORD dwRes = WaitForSingleObject(m_hEvent, timeoutMillis);
	switch(dwRes){
		case WAIT_OBJECT_0:
			return true;
		case WAIT_TIMEOUT:
			return false;
		case WAIT_ABANDONED:
		case WAIT_FAILED:
		default:
			throw YSystemException("Event", "Wait");
		return false;
	}
}

bool YEvent::Set()
{
	return SetEvent(m_hEvent) > 0;
}

bool YEvent::Reset()
{
	return ResetEvent(m_hEvent) > 0;
}

bool YEvent::Pulse()
{
	return PulseEvent(m_hEvent);
}