#include "alcthreading.h"

//Constructor.
AlCThread::AlCThread(AlCLogger *vLogger)
{
	logger = vLogger;

	threadId = NULL;
	threadHandle = NULL;

	started = false;
	completed = false;

	stackSize = 0;
}

//Destructor.
AlCThread::~AlCThread()
{
	completed = true;
	if (threadHandle && threadId)
	{
		swprintf_s(tbuffer, L"Destroying active thread id: %i\n", threadId);
		if (logger) logger->debug(tbuffer);
		CloseHandle(threadHandle);

		threadId = NULL;
		threadHandle = NULL;
	}

}

//The thread proc initiator.
DWORD threadProc(LPVOID param)
{
	AlCThread *a = (AlCThread *) param;
	if (a)
	{
		a->setStarted(true);
		a->setCompleted(false);
		return a->run();
	}

	return 0;
}

//Starts this thread.
bool AlCThread::start()
{
	 if (!CreateThread(NULL, stackSize, (LPTHREAD_START_ROUTINE) &threadProc, (LPVOID) this, 0, &threadId))
	 {
		 if (logger) logger->debug("Create Thread Failed.\n");
		 return false;
	 }

	 return true;
}

//THis will get invoked once the thread starts, 
//by a new thread, and not the current thread tha invoked start.
DWORD AlCThread::run()
{
	//This is meant to be implemented by a calling application.
	return 0;
}


/**
	Thread safe way to set completed for thread.
**/
void AlCThread::setCompleted(bool newval)
{
	std::lock_guard<std::mutex> tmut(threadMutex);					// Wait, and lock access to thread.
	completed = newval;
}


/**
	Thread safe way to retrieve completed for thread.
**/
bool AlCThread::getCompleted()
{
	std::lock_guard<std::mutex> tmut(threadMutex);					// Wait, and lock access to thread.
	bool value = completed;
	return value;
}

/**
	Thread safe way to set started for thread.
**/
void AlCThread::setStarted(bool newval)
{
	std::lock_guard<std::mutex> tmut(threadMutex);					// Wait, and lock access to thread.
	started = newval;

}

/**
	Thread safe way to retrieve started for thread.
**/
bool AlCThread::getStarted()
{
	std::lock_guard<std::mutex> tmut(threadMutex);					// Wait, and lock access to thread.
	bool value = started;
	return value;
}
