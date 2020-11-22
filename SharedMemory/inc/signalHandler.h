#ifndef _SIGNALHADNLER_H_
#define _SIGNALHADNLER_H_

#include <signal.h>
#include <memory.h>
#include <string>
#include <errno.h>

#include "eventHandler.h"
#include "signalException.h"

class SignalHandler{
private:
	static SignalHandler* instance;
	static EventHandler* signal_handlers[NSIG];

	SignalHandler(void);
	static void dispatcher(int signum);
public:
		static SignalHandler* getInstance();
		static void destroy();
		EventHandler* registerHandler(int signum, EventHandler* eh);
		int removeHandler( int signum);
};

#endif
