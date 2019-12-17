#pragma once
#include <concrt.h>

//thread function return values
#define THREAD_ERROR_SUCCESS 0
#define THREAD_ERROR_OTHER 1
#define THREAD_ERROR_EXCEPTION 2
//Todo... #define THREAD_ERROR_OTHERERROR

class YThread{
	typedef enum EThreadState{
		RETURN_ERROR = -5,
		EXCEPTION = -4,	
		CANCELED = -3,	
		CREATE_FAIL = -2,
		INITIAL = -1,
		RETURNED = 0,
		RUNNING = 1,
		PAUSED = 2			
	} E_STATE;

public:
	YThread();
	virtual ~YThread();

	virtual int Run() = 0; //invoked in thread function

	void Start(); 	
	void Suspend();
	void Resume();
	void Cancel(int nTimeout = -1);

	E_STATE GetState() const;
	const HANDLE GetThreadHandle() const;
	unsigned GetThreadId() const;

protected:
	HANDLE m_hThread;
	unsigned m_nThreadID;
	E_STATE m_eState;

private:
	YThread(const YThread& rhs);
	YThread & operator =(const YThread& thread);	
	static unsigned __stdcall threadEntry(void *pParam);

	virtual void BeforeThreadRun(); 
	virtual void OnThreadRun();        
	virtual void OnThreadSuspend();      
	virtual void OnThreadResume();
	virtual void OnThreadReturn();				//return 0
	virtual void OnThreadCancel();               //canceled
	virtual void OnThreadError();					//return value != 0
	virtual void OnThreadException();			//exception
};