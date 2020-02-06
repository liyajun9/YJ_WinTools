#pragma once
#include <concrt.h>

class YAbstractThread{
public:
	enum class EState{
		logicError = -5,		
		exception = -4,	
		canceled = -3,	
		failed = -2, //create thread failed
		initial = -1,
		returned = 0,
		running = 1,
		paused = 2			
	};
	static constexpr int THREAD_SUCCESS = 0;
	static constexpr int THREAD_LOGIC_ERROR = 1;
	static constexpr int THREAD_EXCEPTION = 2;

public:
	YAbstractThread();
	virtual ~YAbstractThread();

	void start(); 	
	int join();
	bool wait(DWORD milliseconds = INFINITE);
	int cancel(DWORD milliseconds = 0);
	void suspend();
	void resume();
	
	int getReturned() const;
	EState getState() const;
	HANDLE getHandle() const;
	unsigned getThreadId() const;

protected:
	HANDLE hThread;
	unsigned nThreadID;
	EState eState;
	int nReturned;

private:
	virtual int Run() = 0; //your async task		

	virtual void OnStart(); 
	virtual void OnRun(); 
	virtual void OnJoin();
	virtual void OnWait();
	virtual void OnCancel();
	virtual void OnSuspend();      
	virtual void OnResume();
	virtual void OnReturn();			
	virtual void OnLogicError();		//Run return THREAD_LOGIC_ERROR
	virtual void OnException();			//Run return THREAD_EXCEPTION

	static unsigned __stdcall threadEntry(void* pParam);
};