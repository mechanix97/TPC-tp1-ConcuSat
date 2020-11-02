#ifndef _IMAGE_H_
#define _IMAGE_H_

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <unistd.h>
#include <vector>

class Image{
	int n;
	int* data;
public:
	Image();
	Image(int n);
	~Image();
	int* getData() const;
	int totalSize() const;
	void generate();
	void loadFromArray(int* a);
	void filter();
	void stretch(const std::vector<Image *>& v);
	void clear();
	friend std::ostream& operator<<(std::ostream& os, const Image& image);
};


#endif
