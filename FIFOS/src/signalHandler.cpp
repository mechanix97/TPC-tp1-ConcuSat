#include "../inc/signalHandler.h"

SignalHandler* SignalHandler::instance = NULL;
EventHandler* SignalHandler::signal_handlers[NSIG];

SignalHandler::SignalHandler(){
}

SignalHandler* SignalHandler::getInstance(){
	if(instance == NULL){
		instance = new SignalHandler();
	}
	return instance;
}

void SignalHandler::destroy(){
	if( instance != NULL){
		delete instance;
		instance = NULL;
	}
}

EventHandler* SignalHandler::registerHandler(int signum, EventHandler* eh){
	EventHandler* old_eh = SignalHandler::signal_handlers[signum];
	SignalHandler::signal_handlers[signum] = eh;

	struct sigaction sa;
	memset(&sa, 0, sizeof(sa));
	sa.sa_handler = SignalHandler::dispatcher;
	sigemptyset(&sa.sa_mask);
	int result = sigaddset(&sa.sa_mask, signum);
	if(result == -1){
		throw SignalException("No se pudo establecer el handler", strerror(errno));
	}	
	result = sigaction(signum, &sa, 0);
	if(result == -1){
		throw SignalException("No se pudo establecer el handler", strerror(errno));
	}
	return old_eh;
}

void SignalHandler::dispatcher(int signum){
	if( SignalHandler::signal_handlers[signum] != 0){
		SignalHandler::signal_handlers[signum] -> handleSignal(signum);
	}
}

int SignalHandler::removeHandler(int signum){
	SignalHandler::signal_handlers[signum] = NULL;
	return 0;
}
