#include "../inc/imageAdjuster.h"


ImageAdjuster::ImageAdjuster(int imageSize, int proj_id) : image(imageSize), size(imageSize),
	sm(PATH_NAME, proj_id, image.totalSize()){
}


ImageAdjuster::~ImageAdjuster(){
}

int ImageAdjuster::start(){
	int pid = fork();
	if(pid == 0){
		GracefulQuitter newData;
		SignalHandler::getInstance()->registerHandler(SIGUSR1, &newData);

		//wait for signal
		while(newData.alive()){	}

		this->image.loadFromArray(this->sm.load());
		this->image.filter();
		this->sm.storeArray(this->image.getData(), this->size*this->size);

		return pid;
	}
	this->childPid = pid;
	return pid;
}

void ImageAdjuster::newDataSignal(){
	kill(this->childPid, SIGUSR1);
}
