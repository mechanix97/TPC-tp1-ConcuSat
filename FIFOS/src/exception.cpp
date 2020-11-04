#include "../inc/exception.h"

Exception::Exception(std::string msg, std::string cause) : msg(msg), cause(cause) {
}

Exception::~Exception(){
}

const std::string& Exception::getMsg() const{
	return this->msg;
}

const std::string& Exception::getCause() const{
	return this->cause;
}

std::string Exception::what() const{
	return this->msg + ": " + this->cause;
}
