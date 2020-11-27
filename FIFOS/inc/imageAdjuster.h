#ifndef _IMAGE_ADJUSTER_H_
#define _IMAGE_ADJUSTER_H_

#include <iostream>

#include "../inc/image.h"
#include "../inc/signalHandler.h"
#include "../inc/gracefulQuitter.h"
#include "../inc/writeFifo.h"
#include "../inc/readFifo.h"
#include "../inc/exception.h"

class ImageAdjuster{
	Image image;
	int size;
	int childPid;
public:
	ImageAdjuster(int imageSize, int proj_id);
	~ImageAdjuster();
	int start(int id);
};

#endif
