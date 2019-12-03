#pragma once
#include <concrt.h>

#define THREAD_ERROR_SUCCESS 0
#define THREAD_ERROR_OTHER 1
#define THREAD_ERROR_EXCEPTION 2
//Todo... #define THREAD_ERROR_OTHERERROR

class CYThreadListener;

class CYThread{
	friend class CYThreadListener;
	typedef enum EThreadStatus{
		success = 0,
		ongoing = 1,
		paused = 2,
		canceled = 3,
		createfailed = 4,
		error = 5,
		exception = 6,
		notexsit = -1
	} E_THREAD_STATUS;
	typedef unsigned (__stdcall *PFNTHREAD)(void *pParam);	

public:
	CYThread();
	virtual ~CYThread();

	//Note: the inner thread can only create and run once
	void Create(CYThreadListener *pListener = NULL, PFNTHREAD pfnThread = NULL, void *pParam = NULL);
	void Run(); 
	void Suspend();
	void Resume();
	void Cancel(int nTimeout = -1);

	E_THREAD_STATUS GetStatus();

protected:
	HANDLE m_hThread;
	unsigned m_nThreadID;
	CYThreadListener *m_pListener;
	PFNTHREAD m_pfnThread;
	void *m_pParam;
	E_THREAD_STATUS m_Status;

private:
	CYThread(const CYThread& rhs);
	CYThread & operator =(const CYThread& thread);	
	static unsigned __stdcall ThreadFuncWrapper(void *pParam);
};




class CYThreadListener{
	friend class CYThread;

public:
	CYThreadListener():m_pThread(NULL){}
	virtual ~CYThreadListener() { 
		if(m_pThread){
			m_pThread->m_pListener = NULL;
		}
	}

	virtual void BeforeThreadRun()=0; 
	virtual void OnThreadRun()=0;        
	virtual void OnThreadSuspend()=0;      
	virtual void OnThreadResume()=0;
	virtual void OnThreadReturn()=0;				//while return 0
	virtual void OnThreadCancel()=0;                //while cancel
	virtual void OnThreadError()=0;					//while return non 0
	virtual void OnThreadException()=0;			//while exception occurred within thread function

private:
	CYThreadListener(const CYThreadListener& rhs) {}
	CYThreadListener &operator =(const CYThreadListener& rhs) {}

	void setThread(CYThread *pThread){ m_pThread = pThread; }

protected:
	CYThread *m_pThread;	//thread to which it listened to
};