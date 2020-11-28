#include "../inc/fifo.h"

Fifo::Fifo(const std::string name) : name(name), fd(-1){
	
	mknod( this->name.c_str(), S_IFIFO | 0777, 0);
		
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
