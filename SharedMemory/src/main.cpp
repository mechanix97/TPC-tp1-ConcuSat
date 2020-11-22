#include <iostream>
#include <stdexcept>
#include <vector>

#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

#include "../inc/image.h"
#include "../inc/sharedMemory.h"
#include "../inc/imageAdjuster.h"
#include "../inc/signalHandler.h"
#include "../inc/gracefulQuitter.h"
#include "../inc/logger.h"

#define PATH_NAME "bin/bash"

static bool parse_args(int argc, char const *argv[], int* c, int* n,Logger& logger ){
	if(argc != 3 && argc != 4){
		return false;
	}
	try{
		*c = std::stoi(argv[1]);
		*n = std::stoi(argv[2]);
		if(argc == 4){
			if(strcmp(argv[3],"-d") == 0){
				logger.turnOn(); 
			}
			else{
				return false;
			}
		}
	} catch(...){
		return false;
	}
	return true;
}

int main(int argc, char const *argv[]){
	int cams = 0;
	int n_pixels = 0;
	Logger logger(std::cout);

	if((parse_args(argc, argv, &cams, &n_pixels, logger)) != true){
		std::cout<<"Usage: ./concusat.out <N° cams> <N° pixels> -d\n";
		return 0;
	}

	std::vector<Image*> images;
	std::vector<SharedMemory<int>*> sharedMemory;
	std::vector<ImageAdjuster*> imageAdjusters;
	Image output(n_pixels);

	GracefulQuitter quit;
	SignalHandler::getInstance()->registerHandler(SIGTSTP, &quit);

	//initialize
	for( int i = 0; i < cams; ++i ){
		images.push_back( new Image(n_pixels) );
		sharedMemory.push_back(new SharedMemory<int>(PATH_NAME, i, images[i]->totalSize()) );
		imageAdjusters.push_back(new ImageAdjuster(n_pixels, i));
	}

	while(quit.alive()){
		for(ImageAdjuster* ia : imageAdjusters){
			if(!ia->start()){
				for(int i=0; i<cams; ++i){
					delete images[i];
					delete sharedMemory[i];
					delete imageAdjusters[i];
				}

				SignalHandler::destroy();

				return 0;
			}
		}

		//generate images and store images
		for(int i = 0; i<cams; ++i){
			images[i]->generate();
			sharedMemory[i]->storeArray(images[i]->getData(), n_pixels*n_pixels);
		}

		//Raise signal in childs
		for(ImageAdjuster* ia : imageAdjusters){
			ia->newDataSignal();
		}

		//wait for child process
		for(int i = 0; i < cams; ++i){
			wait(nullptr);
		}

		for(int i =0; i<cams; ++i){
			images[i]->loadFromArray(sharedMemory[i]->load());
		}

		//stretch images into one
		output.stretch(images);
		
		logger.logData("Resultado\n");
		logger.logData(output);
		//std::cout<<output;
		output.clear();	
	}

	std::cout << "GracefulQuitter!\n";

	for(int i=0; i<cams; ++i){
		delete images[i];
		delete sharedMemory[i];
		delete imageAdjusters[i];
	}

	SignalHandler::destroy();

	return 0;
}