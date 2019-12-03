#include "stdafx.h"
#include "YThread.h"
#include <winbase.h>
#include "..\exceptions\Win32Exception.h"
#include "..\exceptions\ExceptionBase.h"
#include "..\Log\YLog.h"

#pragma warning(disable:4482)

CYThread::CYThread() : m_pListener(NULL),
	m_hThread(INVALID_HANDLE_VALUE),
	m_pfnThread(NULL),
	m_pParam(NULL),
	m_nThreadID(0),
	m_Status(E_THREAD_STATUS::notexsit)
{
}

CYThread::~CYThread()
{
	LOG_INFO("Note: Thread instance destructing: will cancel the thread");
	if(INVALID_HANDLE_VALUE != m_hThread){
		Cancel();
		CloseHandle(m_hThread);
	}
}

CYThread::E_THREAD_STATUS CYThread::GetStatus()
{
	return m_Status;
}

void CYThread::Create(CYThreadListener *pListener, PFNTHREAD pfnThread, void *pParam)
{
	if(m_Status != E_THREAD_STATUS::notexsit)
		return;

	try{
		if(pListener){
			m_pListener = pListener;
			m_pListener->setThread(this);
		}

		if(pfnThread)
			m_pfnThread = pfnThread;

		if(pParam)
			m_pParam = pParam;

		m_hThread = (HANDLE)_beginthreadex(NULL, 0, ThreadFuncWrapper, this, CREATE_SUSPENDED, &m_nThreadID);
		if(INVALID_HANDLE_VALUE == m_hThread){
			throw CWin32Exception("YThread", "Create");
		}
		m_Status = E_THREAD_STATUS::paused;

	}catch(CWin32Exception& e){
		m_Status = E_THREAD_STATUS::createfailed;
		LOG_ERROR(e.what());
	}
}

void CYThread::Run()
{
	if(INVALID_HANDLE_VALUE == m_hThread)
		return;
	if(m_Status != E_THREAD_STATUS::paused)
		return;

	if(m_pListener)
		m_pListener->BeforeThreadRun();

	try{
		if(-1 == ResumeThread(m_hThread))
			throw CWin32Exception("YThread", "Resume");
		m_Status = E_THREAD_STATUS::ongoing;
	}catch(CWin32Exception& e){
		LOG_ERROR(e.what());
	}
}

void CYThread::Suspend()
{
	if(INVALID_HANDLE_VALUE == m_hThread)
		return;
	if(m_Status != E_THREAD_STATUS::ongoing)
		return;

	try{
		if(-1 == SuspendThread(m_hThread))
			throw CWin32Exception("YThread", "Suspend");
		m_Status = E_THREAD_STATUS::paused;

		if(m_pListener)
			m_pListener->OnThreadSuspend();
	}catch(CWin32Exception& e){
		LOG_ERROR(e.what());
	}
}

void CYThread::Resume()
{
	if(INVALID_HANDLE_VALUE == m_hThread)
		return;
	if(m_Status != E_THREAD_STATUS::paused)
		return;

	try{
		if(-1 == ResumeThread(m_hThread))
			throw CWin32Exception("YThread", "Resume");
		m_Status = E_THREAD_STATUS::ongoing;

		if(m_pListener)
			m_pListener->OnThreadResume();
	}catch(CWin32Exception& e){
		LOG_ERROR(e.what());
	}
}

void CYThread::Cancel(int nTimeout)
{
	if(INVALID_HANDLE_VALUE == m_hThread)
		return;
	if(m_Status != E_THREAD_STATUS::ongoing)
		return;

	if(nTimeout == -1 || 
		nTimeout > 0 &&WaitForSingleObject(m_hThread, nTimeout))
	{
		m_Status = E_THREAD_STATUS::canceled;
		TerminateThread(m_hThread, m_Status);
		if(m_pListener)
			m_pListener->OnThreadCancel();
	}else{
		m_Status = E_THREAD_STATUS::success;
		if(m_pListener)
			m_pListener->OnThreadReturn();
	}
}

unsigned __stdcall CYThread::ThreadFuncWrapper(void *pParam)
{
	CYThread *pThreadWarpper = reinterpret_cast<CYThread *>(pParam);
	if(pThreadWarpper->m_pListener)
		pThreadWarpper->m_pListener->OnThreadRun();

	pThreadWarpper->m_Status = E_THREAD_STATUS::ongoing;
	unsigned nRet = THREAD_ERROR_SUCCESS;

	try{
		if(pThreadWarpper->m_pfnThread)
			nRet = pThreadWarpper->m_pfnThread(pThreadWarpper->m_pParam);

		switch (nRet)
		{
		case THREAD_ERROR_SUCCESS:
			pThreadWarpper->m_Status = E_THREAD_STATUS::success;
			if(pThreadWarpper->m_pListener)
				pThreadWarpper->m_pListener->OnThreadReturn();
			break;
		default:
			pThreadWarpper->m_Status = E_THREAD_STATUS::error;
			throw CExceptionBase("thread returned with error", "YThread", "ThreadFuncWrapper");
			break;
		}
	}catch(CExceptionBase& e){
		LOG_ERROR(e.what());
		if(pThreadWarpper->m_pListener)
			pThreadWarpper->m_pListener->OnThreadError();
	}catch(...){
		nRet = THREAD_ERROR_EXCEPTION;
		pThreadWarpper->m_Status = E_THREAD_STATUS::exception;
		CExceptionBase e("thread returned because exception occurred within tread function", "YThread", "ThreadFuncWrapper");
		LOG_ERROR(e.what());
		if(pThreadWarpper->m_pListener)
			pThreadWarpper->m_pListener->OnThreadException();
	}
	return nRet;
}