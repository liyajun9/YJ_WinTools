#include "pch.h"
#include "AbstractThread.h"
#include "exceptions\SystemException.h"
#include "exceptions\Exception.h"
#include <process.h>
#include <handleapi.h>

#pragma warning(disable:4482)

YAbstractThread::YAbstractThread() 
	: hThread(INVALID_HANDLE_VALUE),
	nThreadID(0),
	eState(EState::initial),
	nReturned(THREAD_SUCCESS)
{
}

YAbstractThread::~YAbstractThread()
{
	if(INVALID_HANDLE_VALUE != hThread){
		if(eState == EState::running || eState == EState::paused){
			//LOG_INFO("Note: CYThread destructor: will cancel the thread");
			cancel();  //Note: won't call OnThreadCancel of subclass since subclass isn't exist anymore here
		}
		CloseHandle(hThread);
	}
}

YAbstractThread::EState YAbstractThread::getState() const
{
	return eState;
}

HANDLE YAbstractThread::getHandle() const
{
	return hThread;
}

unsigned YAbstractThread::getThreadId() const
{
	return nThreadID;
}

int YAbstractThread::getReturned() const
{
	return nReturned;
}

void YAbstractThread::start()
{
	if(eState == EState::running || eState == EState::paused)	return;
	OnStart();
	nReturned = THREAD_SUCCESS;

	try{
		hThread = (HANDLE)_beginthreadex(NULL, 0, threadEntry, reinterpret_cast<void*>(this), 0, &nThreadID);
		if(INVALID_HANDLE_VALUE == hThread){
			throw YSystemException("YAbstractThread", "Start");
		}
	}catch(YSystemException& e){
		eState = EState::failed;
		//LOG_ERROR(e.what());
	}
}

void YAbstractThread::suspend()
{
	if (INVALID_HANDLE_VALUE == hThread)
		return;
	if (eState != EState::running)
		return;

	try {
		if (-1 == SuspendThread(hThread))
			throw YSystemException("YAbstractThread", "suspend");

		eState = EState::paused;
		OnSuspend();
	}
	catch (YSystemException & e) {
		//LOG_ERROR(e.what());
	}
}

void YAbstractThread::resume()
{
	if (INVALID_HANDLE_VALUE == hThread)
		return;
	if (eState != EState::paused)
		return;

	try {
		if (-1 == ResumeThread(hThread))
			throw YSystemException("YAbstractThread", "resume");

		eState = EState::running;
		OnResume();
	}
	catch (YSystemException & e) {
		//LOG_ERROR(e.what());
	}
}

int YAbstractThread::join()
{
	int nRet = THREAD_SUCCESS;
	if (INVALID_HANDLE_VALUE == hThread)
		return nRet;
	if (eState != EState::running && eState != EState::paused)
		return nRet;

	OnJoin();
	WaitForSingleObject(hThread, INFINITE);
	return nReturned;
}

bool YAbstractThread::wait(DWORD milliseconds /*= INFINITE*/)
{
	if (INVALID_HANDLE_VALUE == hThread)
		return false;
	if (eState != EState::running && eState != EState::paused)
		return false;

	OnWait();
	return WAIT_OBJECT_0 == WaitForSingleObject(hThread, milliseconds);
}

int YAbstractThread::cancel(DWORD milliseconds /*= 0*/)
{
	int nRet = THREAD_SUCCESS;
	if (INVALID_HANDLE_VALUE == hThread)
		return nRet;
	if (eState != EState::running && eState != EState::paused)
		return nRet;

	if (milliseconds > 0 && WaitForSingleObject(hThread, milliseconds))
	{
		nRet = nReturned;
	}
	else {
		OnCancel();
		TerminateThread(hThread, THREAD_SUCCESS);
		eState = EState::canceled;
	}
	return nRet;
}

unsigned __stdcall YAbstractThread::threadEntry(void *pParam)
{
	YAbstractThread *pThread = reinterpret_cast<YAbstractThread *>(pParam);

	try{
		pThread->OnRun();
		pThread->eState = EState::running;
		pThread->nReturned = pThread->Run();

		switch (pThread->nReturned)
		{
		case THREAD_SUCCESS:
			pThread->OnReturn();
			pThread->eState = EState::returned;
			break;
		default:
			pThread->OnLogicError();
			pThread->eState = EState::logicError;
			throw YException("thread returned error", "YThread", "threadEntry");
			break;
		}
	}
	catch(std::exception& e){
		pThread->OnException();
		pThread->nReturned = THREAD_EXCEPTION;
		pThread->eState = EState::exception;
		//LOG_FATAL(_T("exception in YThread threadEntry - %s"), e.what());
	}
	catch (...) {
		pThread->OnException();
		pThread->nReturned = THREAD_EXCEPTION;
		pThread->eState = EState::exception;
	}
	return pThread->nReturned;
}

void YAbstractThread::OnStart()
{
	//LOG_INFO(_T("OnStart"));
}

void YAbstractThread::OnRun()
{
	//LOG_INFO(_T("OnRun"));
}

void YAbstractThread::OnSuspend()
{
	//LOG_INFO(_T("OnSuspend"));
}

void YAbstractThread::OnResume()
{
	//LOG_INFO(_T("OnThreadResume"));
}

void YAbstractThread::OnJoin()
{
	//LOG_INFO(_T("OnJoin"));
}

void YAbstractThread::OnWait()
{
	//LOG_INFO(_T("OnWait"));
}

void YAbstractThread::OnLogicError()
{
	//LOG_INFO(_T("OnLogicError"));
}
void YAbstractThread::OnException()
{
	//LOG_INFO(_T("OnException"));
}

void YAbstractThread::OnCancel()
{
	//LOG_INFO(_T("OnCancel"));
}

void YAbstractThread::OnReturn()
{
	//LOG_INFO(_T("OnReturn"));
}