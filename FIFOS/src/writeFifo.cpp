#include "../inc/writeFifo.h"

WriteFifo::WriteFifo(const std::string name) : Fifo(name){
}

WriteFifo::~WriteFifo(){
}

void WriteFifo::_open(){
	this->fd = open( this->name.c_str(), O_WRONLY);
}

ssize_t WriteFifo::_write(const void* buffer, const ssize_t buffsize) const{
	return write(this->fd, buffer, buffsize);
}
