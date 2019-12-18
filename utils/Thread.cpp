#include "stdafx.h"
#include "Thread.h"
#include <winbase.h>
#include "..\exceptions\Win32Exception.h"
#include "..\exceptions\Exception.h"
#include "..\Log\Log.h"
#include <process.h>

#pragma warning(disable:4482)

YThread::YThread() 
	: m_hThread(INVALID_HANDLE_VALUE),
	m_nThreadID(0),
	m_eState(E_STATE::INITIAL)
{
}

YThread::~YThread()
{
	if(INVALID_HANDLE_VALUE != m_hThread){
		if(m_eState == E_STATE::RUNNING || m_eState == E_STATE::PAUSED){
			LOG_INFO("Note: CYThread destructor: will cancel the thread");
			Cancel();  //Note: won't call 	OnThreadCancel of subclass since subclass isn't exist anymore here
		}
		CloseHandle(m_hThread);
	}
}

YThread::E_STATE YThread::GetState() const
{
	return m_eState;
}

void YThread::Start()
{
	if(m_eState != E_STATE::INITIAL)
		return;

	BeforeThreadRun();

	try{
		m_hThread = (HANDLE)_beginthreadex(NULL, 0, threadEntry, reinterpret_cast<void*>(this), 0, &m_nThreadID);
		if(INVALID_HANDLE_VALUE == m_hThread){
			throw YWin32Exception("YThread", "Start");
		}
	}catch(YWin32Exception& e){
		m_eState = E_STATE::CREATE_FAIL;
		LOG_ERROR(e.what());
	}
}

void YThread::Suspend()
{
	if(INVALID_HANDLE_VALUE == m_hThread)
		return;
	if(m_eState != E_STATE::RUNNING)
		return;

	try{
		if(-1 == SuspendThread(m_hThread))
			throw YWin32Exception("YThread", "Suspend");

		m_eState = E_STATE::PAUSED;
		OnThreadSuspend();
	}catch(YWin32Exception& e){
		LOG_ERROR(e.what());
	}
}

void YThread::Resume()
{
	if(INVALID_HANDLE_VALUE == m_hThread)
		return;
	if(m_eState != E_STATE::PAUSED)
		return;

	try{
		if(-1 == ResumeThread(m_hThread))
			throw YWin32Exception("YThread", "Resume");

		m_eState = E_STATE::RUNNING;
		OnThreadResume();
	}catch(YWin32Exception& e){
		LOG_ERROR(e.what());
	}
}

void YThread::Cancel(int nTimeout)
{
	if(INVALID_HANDLE_VALUE == m_hThread)
		return;
	if(m_eState != E_STATE::RUNNING && m_eState != E_STATE::PAUSED)
		return;

	if(nTimeout > 0 &&WaitForSingleObject(m_hThread, nTimeout))
	{
		m_eState = E_STATE::RETURNED;
		OnThreadReturn();
	}else{
		m_eState = E_STATE::CANCELED;
		TerminateThread(m_hThread, m_eState);
		OnThreadCancel();
	}
}

unsigned __stdcall YThread::threadEntry(void *pParam)
{
	YThread *pThread = reinterpret_cast<YThread *>(pParam);
	unsigned nRet = THREAD_ERROR_SUCCESS;

	try{
		pThread->m_eState = E_STATE::RUNNING;
		pThread->OnThreadRun();
		nRet = pThread->Run();

		switch (nRet)
		{
		case THREAD_ERROR_SUCCESS:
			pThread->m_eState = E_STATE::RETURNED;
			pThread->OnThreadReturn();
			break;
		default:
			pThread->m_eState = E_STATE::RETURN_ERROR;
			throw YException("thread returned with error", "YThread", "threadEntry");
			break;
		}
	}catch(YException& e){
		LOG_ERROR(e.what());
		pThread->OnThreadError();
	}catch(std::exception& e){
		nRet = THREAD_ERROR_EXCEPTION;
		pThread->m_eState = E_STATE::EXCEPTION;
		LOG_FATAL(_T("exception in YThread threadEntry - %s"), e.what());
		pThread->OnThreadException();
	}
	return nRet;
}

const HANDLE YThread::GetThreadHandle() const
{
	return m_hThread;
}

unsigned YThread::GetThreadId() const
{
	return m_nThreadID;
}

void YThread::BeforeThreadRun()
{
	LOG_INFO(_T("BeforeThreadRun"));
}

void YThread::OnThreadRun()
{
	LOG_INFO(_T("OnThreadRun"));
}

void YThread::OnThreadSuspend()
{
	LOG_INFO(_T("OnThreadSuspend"));
}

void YThread::OnThreadResume()
{
	LOG_INFO(_T("OnThreadResume"));
}

void YThread::OnThreadReturn()
{
	LOG_INFO(_T("OnThreadReturn"));
}

void YThread::OnThreadCancel()
{
	LOG_INFO(_T("OnThreadCancel"));
}

void YThread::OnThreadError()
{
	LOG_INFO(_T("OnThreadError"));
}
void YThread::OnThreadException()
{
	LOG_INFO(_T("OnThreadException"));
}