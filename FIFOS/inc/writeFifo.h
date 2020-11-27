#ifndef _WRITEFIFO_H_
#define _WRITEFIFO_H_

#include "fifo.h"
#include "../inc/exception.h"

class WriteFifo : public Fifo{
public:
	WriteFifo(const std::string name);
	~WriteFifo();

	void _open();
	ssize_t _write(const void* buffer, const ssize_t buffsize) const;
	
};

#endif
