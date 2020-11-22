#include "../inc/signalException.h"

SignalException::SignalException(std::string msg, std::string cause) : Exception(msg, cause){
}

SignalException::~SignalException(){
}
