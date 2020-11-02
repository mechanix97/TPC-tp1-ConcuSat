#ifndef _SIGNALEXCEPTION_H_
#define _SIGNALEXCEPTION_H_

#include "exception.h"

class SignalException : public Exception{
public:
	SignalException(std::string msg, std::string cause);
	~SignalException();
};


#endif
