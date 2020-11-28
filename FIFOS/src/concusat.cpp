#include "../inc/concusat.h"

Concusat::Concusat(int cams, int n) : cams(cams), n_pixels(n), ofs("log.txt", std::ofstream::out), logger(ofs), output(n){
	//initialize

	this->buffer = new int[this->n_pixels*this->n_pixels];

	for( int i = 0; i < cams; ++i ){
		this->images.push_back( new Image(this->n_pixels) );
		this->imageAdjusters.push_back(new ImageAdjuster(this->n_pixels, i));
		this->writeFifos.push_back(new WriteFifo(std::string("W"+std::to_string(i)).c_str()) );
		this->readFifos.push_back( new ReadFifo(std::string("R"+std::to_string(i)).c_str()) );
	}
}

Concusat::~Concusat(){
	delete []buffer;

	for(int i=0; i<this->cams; ++i){
		delete this->images[i];
		delete this->imageAdjusters[i];	
		this->writeFifos[i]->_close();
		this->readFifos[i]->_close();
		delete this->writeFifos[i];
		delete this->readFifos[i];
	}

	SignalHandler::destroy();

	this->ofs.close();
}

void Concusat::log(){
	this->logger.turnOn();
}

int Concusat::fork(){
	for( int j = 0; j < cams; ++j ){
		if(!this->imageAdjusters[j]->start(j)){
			return 0;
		}
	}
	return 1;
}

void Concusat::generate(){
	//generate images 
	for(int i = 0; i<this->cams; ++i){
		this->images[i]->generate();
		this->logger.logData("Genero imagen ");
		this->logger.logData(i);
		this->logger.logData(":\n");
		this->logger.logData(*this->images[i]);
		this->writeFifos[i]->_open();
		int total = this->images[i]->totalSize();
		while(total){
			total -= this->writeFifos[i]->_write(static_cast < void *>(this->images[i]->getData()), total);	
		}
		this->writeFifos[i]->_close();
	}

}

void Concusat::filter(){
	//filter images
	for(int i =0; i<this->cams; ++i){
		this->readFifos[i]->_open();	
		int total = this->images[i]->totalSize();
		while(total){
			total-= this->readFifos[i]->_read(buffer, total);

		}
		this->readFifos[i]->_close();
		this->images[i]->loadFromArray(this->buffer);
		this->logger.logData("Recibo imagen ");
		this->logger.logData(i);
		this->logger.logData(":\n");
		this->logger.logData(*this->images[i]);	
	}
}


void Concusat::stretch(){
	//stretch images into one
	this->output.stretch(this->images);
	this->logger.logData("Resultado:\n");
	this->logger.logData(this->output);
	this->output.clear();	
}

void Concusat::destroyFifos(){
	for(int i=0; i<cams; ++i){
		this->writeFifos[i]->destroy();
		this->readFifos[i]->destroy();
	}
}