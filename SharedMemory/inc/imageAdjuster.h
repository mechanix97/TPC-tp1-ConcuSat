#ifndef _IMAGE_ADJUSTER_H_
#define _IMAGE_ADJUSTER_H_

#include "sharedMemory.h"
#include "image.h"
#include "signalHandler.h"
#include "gracefulQuitter.h"

#define PATH_NAME "/bin/bash"

class ImageAdjuster{
	Image image;
	int size;
	SharedMemory<int> sm;
	int childPid;
public:
	ImageAdjuster(int imageSize, int proj_id);
	~ImageAdjuster();
	int start();
	void newDataSignal();
};


#endif
