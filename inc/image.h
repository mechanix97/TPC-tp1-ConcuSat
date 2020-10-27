#ifndef _IMAGE_H_
#define _IMAGE_H_

#include <cstdlib>
#include <ctime>
#include <unistd.h>

class Image{
	int n;
	int ** data;
public:
	Image(int n);
	~Image();
	void generate();
	void adjust();
};


#endif
