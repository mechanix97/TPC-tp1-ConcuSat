#include "../inc/writeFifo.h"

WriteFifo::WriteFifo(const std::string name) : Fifo(name) {}

WriteFifo::~WriteFifo() {}

void WriteFifo::_open(){
	this->fd = open( this->name.c_str(), O_WRONLY);
	if(this->fd < 0){
		throw Exception("Error", "Failed to open Write FIFO");
	}
}

ssize_t WriteFifo::_write(const void* buffer, const ssize_t buffsize) const{
	int v =	write(this->fd, buffer, buffsize);
	return v;
}
