#include "../inc/readFifo.h"

ReadFifo::ReadFifo(const std::string name) : Fifo(name){
}

ReadFifo::~ReadFifo(){
}

void ReadFifo::_open(){
	this->fd = open(this->name.c_str(), O_RDONLY);
}

ssize_t ReadFifo::_read(void* buffer, const ssize_t buffsize) const{
	return read(this->fd, buffer, buffsize);
}
