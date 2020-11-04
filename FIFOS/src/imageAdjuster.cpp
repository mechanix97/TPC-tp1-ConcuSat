#include "../inc/imageAdjuster.h"


ImageAdjuster::ImageAdjuster(int imageSize, int proj_id) : image(imageSize), size(imageSize){
}


ImageAdjuster::~ImageAdjuster(){
}

int ImageAdjuster::start(int id){
	int pid = fork();
	if(pid == 0){
		ReadFifo readChannel(std::string('W'+std::to_string(id)).c_str());

		
		//readChannel._open();

		int* buffer;
		buffer = new int[this->size*this->size];


			readChannel._read(&buffer, 4);
			std::cout<<"entro\n";
			this->image.loadFromArray(buffer);
			std::cout<<"leo\n";
			std::cout<<this->image;
			this->image.filter();

			WriteFifo writeChannel(std::string('R'+std::to_string(id)).c_str());
			writeChannel._open();
			writeChannel._write(this->image.getData(), 4);
		
		delete buffer;
		writeChannel._close();
		readChannel._close();
		std::cout<<"stoped buffer\n";
		return pid;
	}
	this->childPid = pid;
	return pid;
}


void ImageAdjuster::stopChild() const{
	kill(this->childPid, SIGTSTP);
}