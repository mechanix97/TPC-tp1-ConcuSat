#ifndef _FIFO_H_
#define _FIFO_H_

#include <string>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#include "../inc/exception.h"

class Fifo{
public:
	Fifo(const std::string name);
	virtual ~Fifo();
	virtual void _open() = 0;
	void _close();
	void destroy() const;
protected:
	std::string name;
	int fd;
};

#endif
