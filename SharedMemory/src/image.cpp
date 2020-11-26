#include "../inc/image.h"

Image::Image() : n(0){
}

Image::Image(int n) : n(n)  {
	this->data = new int[n*n];
	for(int i =0; i < n; ++i){
		for (int j = 0; j < n; ++j)	{
			this->data[i*n+j]=0;
		}
	}
	std::srand(std::time(0));
}

Image::~Image(){
	delete [] this->data;
}

int* Image::getData() const{
	return this->data;
}

int Image::totalSize() const{
	return this->n*this->n*sizeof(int);
}

void Image::generate(){
	for(int i = 0; i < this->n; ++i){
		for(int j = 0; j< this->n; ++j){
			this->data[(i*this->n)+j] = std::rand();
		}
	}
}

void Image::loadFromArray(int* a){
	for(int i = 0; i < this->n; ++i){
		for(int j = 0; j< this->n; ++j){
			this->data[(i*this->n)+j] = a[(i*this->n)+j];
		}
	}	
}

void Image::filter(){
	for(int i = 0; i < this->n; ++i){
		for(int j = 0; j< this->n; ++j){
			//this->data[i][j]++;
		}
	}	
	sleep(5); //hard-work
}

void Image::stretch(const std::vector<Image *>& v){
	for(int i = 0; i < this->n; ++i){
		for(int j = 0; j< this->n; ++j){
			for(Image* im : v){
				this->data[(i*this->n)+j] += im->data[(i*this->n)+j];	
			}
		}
	}
}

void Image::clear(){
	for(int i = 0; i < this->n; ++i){
		for(int j = 0; j< this->n; ++j){		
			this->data[(i*this->n)+j] = 0;	
		}
	}
}

std::ostream& operator<<(std::ostream& os, const Image& image){
	for(int i = 0; i< image.n; ++i){
		for(int j = 0; j< image.n; ++j){
			os << image.data[(i*image.n)+j] << " ";
		}
		os << std::endl;
	}
	return os;
}
