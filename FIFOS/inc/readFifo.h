#ifndef _READFIFO_H_
#define _READFIFO_H_

#include "fifo.h"
#include "../inc/exception.h"

class ReadFifo : public Fifo{
public:
	ReadFifo(const std::string name);
	~ReadFifo();

	void _open();
	ssize_t _read(void* buffer, const ssize_t buffsize) const;
	
};

#endif
