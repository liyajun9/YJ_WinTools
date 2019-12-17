#include "stdafx.h"
#include "YThread.h"
#include <winbase.h>
#include "..\exceptions\Win32Exception.h"
#include "..\exceptions\ExceptionBase.h"
#include "..\Log\YLog.h"

#pragma warning(disable:4482)

CYThread::CYThread() 
	: m_hThread(INVALID_HANDLE_VALUE),
	m_nThreadID(0),
	m_eState(E_STATE::INITIAL)
{
}

CYThread::~CYThread()
{
	if(INVALID_HANDLE_VALUE != m_hThread){
		if(m_eState == E_STATE::RUNNING || m_eState == E_STATE::PAUSED){
			//LOG_INFO("Note: CYThread destructor: will cancel the thread");
			Cancel();  //Note: won't call 	OnThreadCancel of subclass since subclass isn't exist anymore here
		}
		CloseHandle(m_hThread);
	}
}

CYThread::E_STATE CYThread::GetState() const
{
	return m_eState;
}

void CYThread::Start()
{
	if(m_eState != E_STATE::INITIAL)
		return;

	BeforeThreadRun();

	try{
		m_hThread = (HANDLE)_beginthreadex(NULL, 0, threadEntry, reinterpret_cast<void*>(this), 0, &m_nThreadID);
		if(INVALID_HANDLE_VALUE == m_hThread){
			throw CWin32Exception("YThread", "Start");
		}
	}catch(CWin32Exception& e){
		m_eState = E_STATE::CREATE_FAIL;
		LOG_ERROR(e.what());
	}
}

void CYThread::Suspend()
{
	if(INVALID_HANDLE_VALUE == m_hThread)
		return;
	if(m_eState != E_STATE::RUNNING)
		return;

	try{
		if(-1 == SuspendThread(m_hThread))
			throw CWin32Exception("YThread", "Suspend");

		m_eState = E_STATE::PAUSED;
		OnThreadSuspend();
	}catch(CWin32Exception& e){
		LOG_ERROR(e.what());
	}
}

void CYThread::Resume()
{
	if(INVALID_HANDLE_VALUE == m_hThread)
		return;
	if(m_eState != E_STATE::PAUSED)
		return;

	try{
		if(-1 == ResumeThread(m_hThread))
			throw CWin32Exception("YThread", "Resume");

		m_eState = E_STATE::RUNNING;
		OnThreadResume();
	}catch(CWin32Exception& e){
		LOG_ERROR(e.what());
	}
}

void CYThread::Cancel(int nTimeout)
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

unsigned __stdcall CYThread::threadEntry(void *pParam)
{
	CYThread *pThread = reinterpret_cast<CYThread *>(pParam);
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
			throw CExceptionBase("thread returned with error", "YThread", "threadEntry");
			break;
		}
	}catch(CExceptionBase& e){
		LOG_ERROR(e.what());
		pThread->OnThreadError();
	}catch(...){
		nRet = THREAD_ERROR_EXCEPTION;
		pThread->m_eState = E_STATE::EXCEPTION;
		CExceptionBase e("thread returned because exception occurred within tread function", "YThread", "threadEntry");
		LOG_ERROR(e.what());
		pThread->OnThreadException();
	}
	return nRet;
}

const HANDLE CYThread::GetThreadHandle() const
{
	return m_hThread;
}

unsigned CYThread::GetThreadId() const
{
	return m_nThreadID;
}

void CYThread::BeforeThreadRun()
{
	LOG_INFO(_T("BeforeThreadRun"));
}

void CYThread::OnThreadRun()
{
	LOG_INFO(_T("OnThreadRun"));
}

void CYThread::OnThreadSuspend()
{
	LOG_INFO(_T("OnThreadSuspend"));
}

void CYThread::OnThreadResume()
{
	LOG_INFO(_T("OnThreadResume"));
}

void CYThread::OnThreadReturn()
{
	LOG_INFO(_T("OnThreadReturn"));
}

void CYThread::OnThreadCancel()
{
	LOG_INFO(_T("OnThreadCancel"));
}

void CYThread::OnThreadError()
{
	LOG_INFO(_T("OnThreadError"));
}
void CYThread::OnThreadException()
{
	LOG_INFO(_T("OnThreadException"));
}