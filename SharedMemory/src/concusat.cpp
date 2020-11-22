#include "../inc/concusat.h"

Concusat::Concusat(int cams, int n) : cams(cams), n_pixels(n), ofs ("log.txt", std::ofstream::out), logger(ofs), output(n){
	for( int i = 0; i < cams; ++i ){
		images.push_back( new Image(n_pixels) );
		sharedMemory.push_back(new SharedMemory<int>(PATH_NAME, i, images[i]->totalSize()) );
		imageAdjusters.push_back(new ImageAdjuster(n_pixels, i));
	}
}

Concusat::~Concusat(){
	for(int i=0; i<this->cams; ++i){
		delete images[i];
		delete sharedMemory[i];
		delete imageAdjusters[i];
	}

	SignalHandler::destroy();
	ofs.close();
}

void Concusat::log(){
	this->logger.turnOn();
}

int Concusat::fork(){
	for(ImageAdjuster* ia : this->imageAdjusters){
		if(!ia->start()){	
			return 0;
		}
	}
	return 1;
}

void Concusat::generate(){
	//generate images and store images
	for(int i = 0; i<this->cams; ++i){
		this->images[i]->generate();
		this->logger.logData("Genero imagen ");
		this->logger.logData(i);
		this->logger.logData(":\n");
		this->logger.logData(*this->images[i]);
		this->sharedMemory[i]->storeArray(this->images[i]->getData(), this->n_pixels*this->n_pixels);
	}
}

void Concusat::riseSignal(){
	//Rise signal in childs
	for(ImageAdjuster* ia : this->imageAdjusters){
		ia->newDataSignal();
	}
}

void Concusat::waitChilds(){
	//wait for child process
	for(int i = 0; i < cams; ++i){
		wait(nullptr);
	}
}


void Concusat::loadFromChilds(){
	for(int i =0; i<cams; ++i){
		images[i]->loadFromArray(sharedMemory[i]->load());
		logger.logData("Recibo imagen ");
		logger.logData(i);
		logger.logData(":\n");
		logger.logData(*images[i]);			
	}	
}

void Concusat::stretch(){
	//stretch images into one
	output.stretch(images);
	
	logger.logData("Resultado:\n");
	logger.logData(output);
	output.clear();	
}
