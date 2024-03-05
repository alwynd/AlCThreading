#pragma once
//The main header for this implementation.
/**
	Implements multi threading.
*/
#include <Windows.h>
#include <tchar.h>

#include "alCLogger_64.h"
#pragma comment(lib, "AlCLogger_64.lib")

#include <mutex>


//The thread proc initiator.
DWORD threadProc(LPVOID param);

//The main threadd class.
class DLLEXPORT AlCThread
{
public:
	AlCThread(AlCLogger *vLogger);
	virtual ~AlCThread();

	//Starts this thread.
	bool start();

	//THis will get invoked once the thread starts, 
	//by a new thread, and not the current thread tha invoked start.
	virtual DWORD run();

	//Logging.
	AlCLogger *logger;

	//Thread id.
	DWORD threadId;
	HANDLE threadHandle;

	int stackSize;
	void setCompleted(bool newval);			// Thread safe way to set completed for thread.
	bool getCompleted();					// Thread safe way to retrieve completed for thread.

	void setStarted(bool newval);			// Thread safe way to set started for thread.
	bool getStarted();						// Thread safe way to retrieve started for thread.

	bool completed;

	//Character buffer for output.
	wchar_t tbuffer[2048];

	std::mutex threadMutex;					// Mutex to protect this thread.


	//Bool flags, for thread control.
	bool started;


};
