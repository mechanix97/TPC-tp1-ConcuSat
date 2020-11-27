#ifndef _CONCUSAT_H_
#define _CONCUSAT_H_

#include <vector>
#include <fstream>
#include <iostream>

#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

#include "../inc/image.h"
#include "../inc/imageAdjuster.h"
#include "../inc/writeFifo.h"
#include "../inc/readFifo.h"
#include "../inc/logger.h"
#include "../inc/exception.h"

class Concusat{
	int cams;
	int n_pixels;
	int* buffer;
	std::ofstream ofs;
	Logger logger;
	std::vector<Image*> images;
	std::vector<ReadFifo*> readFifos;
	std::vector<WriteFifo*> writeFifos;
	std::vector<ImageAdjuster*> imageAdjusters;
	Image output;
public:
	explicit Concusat(int cams, int n);
	~Concusat();
	void log();
	int fork();
	void generate();
	void filter();
	void stretch();
	void destroyFifos();
};

#endif

