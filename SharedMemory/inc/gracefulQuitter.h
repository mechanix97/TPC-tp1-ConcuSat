#ifndef _GRACEFULQUITTER_H_
#define _GRACEFULQUITTER_H_

#include <signal.h>
#include <assert.h>

#include "eventHandler.h"

class GracefulQuitter : public EventHandler{
private:
	sig_atomic_t gracefullQuit;
public:
	GracefulQuitter() : gracefullQuit(0) {}
	~GracefulQuitter() {}

	virtual int handleSignal(int signum){
		this->gracefullQuit = 1;
		return 0;
	}

	sig_atomic_t alive () const{
		return this->gracefullQuit == 0;
	}
	
};


#endif
