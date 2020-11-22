#include <iostream>
#include <stdexcept>
#include <vector>
#include <fstream>

#include "../inc/signalHandler.h"
#include "../inc/gracefulQuitter.h"
#include "../inc/concusat.h"

static bool parse_args(int argc, char const *argv[], int* c, int* n, bool* log ){
	if(argc != 3 && argc != 4){
		return false;
	}
	try{
		*c = std::stoi(argv[1]);
		*n = std::stoi(argv[2]);
		if(argc == 4){
			if(strcmp(argv[3],"-d") == 0){
				*log = true;
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
	bool log = false;

	if((parse_args(argc, argv, &cams, &n_pixels, &log)) != true){
		std::cout<<"Usage: ./concusat.out <N° cams> <N° pixels> -d\n";
		return 0;
	}

	Concusat concusat(cams, n_pixels);

	if(log){
		concusat.log();
	}

	GracefulQuitter quit;
	SignalHandler::getInstance()->registerHandler(SIGTSTP, &quit);

	while(quit.alive()){
		if(!concusat.fork()){
			return 0;
		}
		concusat.generate();
		concusat.riseSignal();
		concusat.waitChilds();
		concusat.loadFromChilds();
		concusat.stretch();
	}

	return 0;
}