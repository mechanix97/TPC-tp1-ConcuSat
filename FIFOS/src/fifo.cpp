#include "../inc/fifo.h"

Fifo::Fifo(const std::string name) : name(name), fd(-1){
	unlink(this->name.c_str());
	if(mknod( this->name.c_str(), S_IFIFO | 0666, 0) == -1){
		throw Exception("Error", "Failed to create FIFO");
	}
}

Fifo::~Fifo(){
}

void Fifo::_close(){
	close(this->fd);
	this->fd = -1;
}

void Fifo::destroy() const{
	unlink(this->name.c_str());
}
