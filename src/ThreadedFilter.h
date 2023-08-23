#pragma once

#include "Filter.h"
#include "ofMain.h"

// A container for the filter class, to make threading easier for me to wrap my head around. 
// Probably not a great idea, so i'll try to take it out in the future.
class ThreadedFilter : public ofThread
{
	private:
		// The filter to use when processing an image.
		Filter f;
		// The image to process using the filter, and when finished, the output image.
		ofImage result;

	public:
		// Sets the thread up to run a filter on an image.
		void setup(string program, ofImage image);
		// Implements the threaded behaviour, which in this case, is running the filter.
		void threadedFunction();
		// Returns the image when the processing is finished.
		ofImage getResult();
};

