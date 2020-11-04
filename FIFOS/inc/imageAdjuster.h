#ifndef _IMAGE_ADJUSTER_H_
#define _IMAGE_ADJUSTER_H_

#include "image.h"
#include "signalHandler.h"
#include "gracefulQuitter.h"
#include "../inc/writeFifo.h"
#include "../inc/readFifo.h"

class ImageAdjuster{
	Image image;
	int size;
	int childPid;
public:
	ImageAdjuster(int imageSize, int proj_id);
	~ImageAdjuster();
	int start(int id);
	void stopChild() const;
};

#endif
