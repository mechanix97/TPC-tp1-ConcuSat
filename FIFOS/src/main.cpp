#include <iostream>
#include <stdexcept>
#include <vector>

#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

#include "../inc/image.h"
#include "../inc/imageAdjuster.h"
#include "../inc/signalHandler.h"
#include "../inc/gracefulQuitter.h"
#include "../inc/writeFifo.h"
#include "../inc/readFifo.h"

#define PATH_NAME "bin/bash"

static bool parse_args(int argc, char const *argv[], int* c, int* n){
	if(argc != 3){
		return false;
	}
	try{
		*c = std::stoi(argv[1]);
		*n = std::stoi(argv[2]);
	} catch(...){
		return false;
	}
	return true;
}

int main(int argc, char const *argv[]){
	int cams = 0;
	int n_pixels = 0;

	if((parse_args(argc, argv, &cams, &n_pixels)) != true){
		std::cout<<"Usage: ./concusat.out <N° cams> <N° pixels>\n";
		return 0;
	}

	std::vector<Image*> images;
	std::vector<ImageAdjuster*> imageAdjusters;
	std::vector<ReadFifo*> readFifos;
	std::vector<WriteFifo*> writeFifos;
	Image output(n_pixels);

	ReadFifo readChannel(std::string('W'+std::to_string(1)).c_str());

	std::cout<<"antes\n";	
	readChannel._open();
	std::cout<<"despues\n";
	

	//GracefulQuitter quit;
	//SignalHandler::getInstance()->registerHandler(SIGTSTP, &quit);

/*
	//initialize
	for( int i = 0; i < cams; ++i ){
		images.push_back( new Image(n_pixels) );
		imageAdjusters.push_back(new ImageAdjuster(n_pixels, i));
	}

	for( int i = 0; i < cams; ++i ){
		writeFifos.push_back(new WriteFifo(std::string('W'+std::to_string(i)).c_str()) );
		readFifos.push_back( new ReadFifo(std::string('R'+std::to_string(i)).c_str()) );
	}

	for( int i = 0; i< cams; ++i){
		
		
	}

	int* buffer;
	buffer = new int[n_pixels*n_pixels];

	//while(quit.alive()){
	for(int k=0; k<1; ++k){
		//generate images 
		for(int i = 0; i<cams; ++i){
			images[i]->generate();
			std::cout<<*images[i];
			writeFifos[i]->_open();
			writeFifos[i]->_write(images[i]->getData(), 4);			
			writeFifos[i]->_close();
		}

		for( int j = 0; j < cams; ++j ){
			if(!imageAdjusters[j]->start(j)){
				goto salida;
			}
		}

		for(int i =0; i<cams; ++i){
			readFifos[i]->_open();
			readFifos[i]->_read(&buffer, 4);
			readFifos[i]->_close();
			images[i]->loadFromArray(buffer);
			std::cout<<images[i];
		}

		//stretch images into one
		output.stretch(images);
		std::cout << output;
		output.clear();	
	}

	std::cout<<"me voy\n";

salida:
	delete buffer;

	for(int i=0; i<cams; ++i){
		delete images[i];
		imageAdjusters[i]->stopChild();
		delete imageAdjusters[i];	
	}

	SignalHandler::destroy();
*/
	return 0;
}