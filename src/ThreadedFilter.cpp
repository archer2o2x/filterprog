#pragma once
#include "ThreadedFilter.h"

/*ThreadedFilter::ThreadedFilter()
{
}*/

void ThreadedFilter::setup(string program, ofImage image)
{
	f = Filter(program);
	result = image;
}

void ThreadedFilter::threadedFunction() {

	f.UseFilter(&result.getPixels());

	result.update();

}

ofImage ThreadedFilter::getResult()
{
	return result;
}
