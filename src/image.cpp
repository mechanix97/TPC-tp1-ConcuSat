#include "../inc/image.h"

#include <iostream>

Image::Image(int n) : n(n)  {
	this->data = new int*[n];
	for( int i = 0; i < n; ++i ){
		this->data[i] = new int[n];
	}
	std::srand(std::time(0));
}

Image::~Image(){
	for( int i = 0; i < this->n; ++i ){
		delete [] this->data[i];
	}
	delete [] this->data;

}

void Image::generate(){
	for(int i = 0; i < this->n; ++i){
		for(int j = 0; j< this->n; ++j){
			this->data[i][j] = std::rand();
		}
	}
}

void Image::adjust(){
	for(int i = 0; i < this->n; ++i){
		for(int j = 0; j< this->n; ++j){
			this->data[i][j]++;
		}
	}	
	sleep(5); //hard-work
}