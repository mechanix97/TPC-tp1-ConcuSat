#ifndef _LOGGER_H_
#define _LOGGER_H_

#include <iostream>
#include <ostream>

class Logger{
	bool log;
	std::ostream& os;
public:
	Logger(std::ostream& os);
	~Logger();
	void turnOn();
	template<typename T>
	void logData(const T& d);
	
};

template<typename T>
void Logger::logData(const T& d){
	if(this->log){
		os << d;
		os.flush();
	}
}

#endif
