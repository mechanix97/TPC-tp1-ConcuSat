#ifndef _EVENTHANDLER_H_
#define _EVENTHANDLER_H_

class EventHandler{
public:
	virtual int handleSignal (int signum) = 0;
	virtual ~EventHandler() {};
	
};



#endif
