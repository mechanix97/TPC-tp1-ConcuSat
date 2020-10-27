#include <iostream>
#include <stdexcept>
#include <vector>

#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

#include "../inc/image.h"

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
		std::cout<<"Usage: ./concusat <N° cams> <N° pixels>\n";
		return 0;
	}

	std::vector<Image*> images;

	for( int i = 0; i < cams; ++i ){
		images.push_back( new Image(n_pixels) );
	}

	for( Image* i : images){
		(*i).generate();
	}

	for( Image* i : images){
		int pid = fork();
		if( pid == 0){
			(*i).adjust();
			exit(0);
		}		
	}

	for(int i = 0; i < cams; ++i){
		wait(nullptr);
	}

	return 0;
}