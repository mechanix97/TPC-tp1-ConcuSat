#ifndef _EXCEPTION_H_
#define _EXCEPTION_H_

#include <string>

class Exception{
	std::string msg;
	std::string cause;
public:
	Exception(std::string msg, std::string cause);
	virtual ~Exception();
	const std::string& getMsg() const;
	const std::string& getCause() const;
	virtual std::string what() const;
	
};


#endif
