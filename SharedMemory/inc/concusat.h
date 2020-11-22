#ifndef _CONCUSAT_H_
#define _CONCUSAT_H_

#include <fstream>

#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

#include "../inc/image.h"
#include "../inc/sharedMemory.h"
#include "../inc/imageAdjuster.h"
#include "../inc/logger.h"

#define PATH_NAME "bin/bash"

class Concusat{
	int cams;
	int n_pixels;
	std::ofstream ofs;
	Logger logger;
	std::vector<Image*> images;
	std::vector<SharedMemory<int>*> sharedMemory;
	std::vector<ImageAdjuster*> imageAdjusters;
	Image output;
public:
	explicit Concusat(int cams, int n);
	~Concusat();
	void log();
	int fork();
	void generate();
	void riseSignal();
	void waitChilds();
	void loadFromChilds();
	void stretch();
};


#endif
