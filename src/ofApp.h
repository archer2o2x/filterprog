#pragma once

#include "ofMain.h"
#include "Filter.h"
#include "Button.h"
#include "ThreadedFilter.h"
#include "CodeEntry.h"

// Main application class
class ofApp : public ofBaseApp{

	public:
		// This destructor makes sure the application is thread safe.
		~ofApp();

		// Default functions.
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
		
		// This is the input image for the filter to use.
		ofImage inputImage;
		// This is the image outputted by the filter.
		ofImage outputImage;



		// This button is used when the user wants to make a new filter.
		Button ProgramNewButton;
		// This button is used when the user wants to open a filter from a file.
		Button ProgramOpenButton;
		// This button is used when the user wants to save a filter to a file.
		Button ProgramSaveButton;
		// This button is used when the user wants to recieve help when programming.
		Button ProgramHelpButton;



		// This button is used when the user wants to load an image to filter.
		Button FilterLoadButton;
		// This button is used when the user wants to process an image with the current filter.
		Button FilterUseButton;
		// This button is used when the user wants to save the image outputted by the filter.
		Button FilterSaveButton;
		// This button is used when the user wants to use the output image as input for the filter.
		Button FilterSwapButton;
		// This button is used to display if the filter is currently processing or not.
		Button FilterProgressButton;

		// This button is used to select the filter tab.
		Button filterButton;
		// This button is used to select the editor tab.
		Button programButton;

		// This is the primary colour of the application, eg standard text or outlines
		ofColor primaryColor = ofColor(220, 200, 200);
		// This is the secondary color of the application, eg background colours
		ofColor secondaryColour = ofColor(40, 50, 50);

		// This is the font the program is using.
		ofTrueTypeFont programFont;

		// This is the text editor component of the editor tab.
		CodeEntry programEntry;

		// This is the filter component with threaded capabilities.
		ThreadedFilter threadedFilter;

		// This indicates whether the filter is currently processing.
		bool currentlyRunningFilter = false;

		// This indicates whether we are in the editor tab or not.
		bool isProgramming = true;

		// This switches the current tab to the editor.
		void NavigateProgram();
		// This switches the current tab to the filter.
		void NavigateFilter();
};
