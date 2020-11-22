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

	

	GracefulQuitter quit;
	SignalHandler::getInstance()->registerHandler(SIGTSTP, &quit);


	//initialize
	for( int i = 0; i < cams; ++i ){
		images.push_back( new Image(n_pixels) );
		imageAdjusters.push_back(new ImageAdjuster(n_pixels, i));
	}

	for( int i = 0; i < cams; ++i ){
		writeFifos.push_back(new WriteFifo(std::string("/W"+std::to_string(i)).c_str()) );
		readFifos.push_back( new ReadFifo(std::string("/R"+std::to_string(i)).c_str()) );
	}

	int* buffer;
	buffer = new int[n_pixels*n_pixels];

	while(quit.alive()){
		for( int j = 0; j < cams; ++j ){
			if(!imageAdjusters[j]->start(j)){
				delete []buffer;

				for(int i=0; i<cams; ++i){
					delete images[i];
					delete imageAdjusters[i];	
					delete writeFifos[i];
					delete readFifos[i];
				}

				SignalHandler::destroy();

				return 0;
			}
		}

		//generate images 
		for(int i = 0; i<cams; ++i){
			images[i]->generate();
			writeFifos[i]->_open();
			int total = images[i]->totalSize();
			while(total){
				total -= writeFifos[i]->_write(static_cast < void *>(images[i]->getData()), total);	
			}
			writeFifos[i]->_close();
		}

		
		//filter images
		for(int i =0; i<cams; ++i){
			readFifos[i]->_open();
			int total = images[i]->totalSize();
			while(total){
				total-=readFifos[i]->_read(buffer, total);
			}
			readFifos[i]->_close();
			images[i]->loadFromArray(buffer);
		}

		//stretch images into one
		output.stretch(images);
		std::cout << output;
		output.clear();	
	}

	delete []buffer;

	for(int i=0; i<cams; ++i){
		delete images[i];
		delete imageAdjusters[i];	
		writeFifos[i]->destroy();
		readFifos[i]->destroy();
		delete writeFifos[i];
		delete readFifos[i];
	}

	SignalHandler::destroy();

	return 0;
}