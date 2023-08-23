#pragma once

#include "ofMain.h"

#include "FilterConstants.h"

// This class processes FILTERPROG instructions to filter images.
class Filter
{
	private:

		// The index of the current instruction.
		int programIndex = 0;

		// The pixel data of the image we want to filter.
		ofPixels* pixelData;

		// The instructions to follow, stored as space seperated values.
		vector<string> instructions;

		// The variables the program can use.
		map<string, float> variables;

		// Returns the next instruction from the list.
		string GetNext();

		// Returns the colour at the current position, base for the PIXEL_ instructions.
		ofFloatColor GetColorAtPosition();

		// Returns the width of the image in pixels.
		int getImgWidth();
		// Returns the height of the image in pixels.
		int getImgHeight();
		// Returns the colour at the specified pixel index.
		ofColor getImgColor(size_t index);
		// Returns the pixel index of the (x, y) position.
		size_t getImgIndex(int x, int y);

		// Prints all variables to the output, for debugging purposes.
		void debugVariables();

		// Stores whether the filter should be running or not. Doesn't work now, as its on a different thread.
		bool isRunning;

	public:

		// Filter Constructors
		Filter();
		Filter(string program);

		// Processes the provided image with the filter that's currently loaded.
		void UseFilter(ofPixels* image);

		// Executes the next step of the program, recursively.
		float Execute();
		// Compiles the program string into the vector instructions.
		void Compile(string program);

};

