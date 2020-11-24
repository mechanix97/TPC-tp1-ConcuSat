#include "../inc/logger.h"


Logger::Logger(std::ostream& os): log(false), os(os){
}

Logger::~Logger(){
}

void Logger::turnOn(){
	this->log = true;
}
