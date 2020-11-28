#include "../inc/imageAdjuster.h"

ImageAdjuster::ImageAdjuster(int imageSize, int proj_id) : image(imageSize), size(imageSize){
}


ImageAdjuster::~ImageAdjuster(){
}

int ImageAdjuster::start(int id){
	int pid = fork();
	if(pid == 0){		
		try{
			ReadFifo readChannel(std::string("W"+std::to_string(id)).c_str());			
			readChannel._open();


			int* buff;
			buff = new int[this->size*this->size];

			int total = this->image.totalSize();
			while(total){
				total-=readChannel._read(buff, total);
			}

			this->image.loadFromArray(buff);
			this->image.filter();

			WriteFifo writeChannel(std::string("R"+std::to_string(id)).c_str());
			writeChannel._open();

			total = this->image.totalSize();
			while(total){
				total-=writeChannel._write(static_cast < void *>(this->image.getData()), total);
			}
			
			delete []buff;
			writeChannel._close();
			readChannel._close();
			return pid;
		} catch(Exception& e){
			std::cout << e.what() << std::endl;
			exit(1);
		}
	}
	this->childPid = pid;
	return pid;
}
