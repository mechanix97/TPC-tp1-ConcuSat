#include "../inc/readFifo.h"

ReadFifo::ReadFifo(const std::string name) : Fifo(name){
}

ReadFifo::~ReadFifo(){
}

void ReadFifo::_open(){
	this->fd = open(this->name.c_str(), O_RDONLY);
	if(this->fd < 0){
		throw Exception("Error", "Failed to open Read FIFO");
	}
}

ssize_t ReadFifo::_read(void* buffer, const ssize_t buffsize) const{
	return read(this->fd, buffer, buffsize);
}
