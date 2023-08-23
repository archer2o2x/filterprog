#pragma once

#include "ofMain.h"

// A class which handles complex text input, and is used as the main program editing tool.
class CodeEntry {
	private:

		// Sets the position of the top-right corner of the code entry.
		ofVec2f Position;
		// Sets the size of the code entry.
		ofVec2f Size;

		// Stores the index of the top line to be displayed. Used when the text entered is bigger than the entry is.
		int OffsetY = 0;

		// Stores how many lines can fit vertically inside the code entry.
		int MaxLines = 0;
		// Stores how many characters can fit horizontally inside the code entry.
		int MaxCharaters = 0;

		// The font which we use to determine sizes and to render to the screen.
		ofTrueTypeFont* Font;
		// A line by line representation of the text currently inside the code entry.
		vector<string> Lines;

		// The Y position of the cursor, measured in lines from the top.
		int CursorX = 0;
		// The X position of the cursor, measured in characters from the left of the code entry, minus the 4 characters for line numbers.
		int CursorY = 0;

		// Stores the primary colour of the code entry, eg the text.
		ofColor Primary = ofColor(255);
		// Stores the secondary colour of the code entry, eg the background.
		ofColor Secondary = ofColor(0);

	public:
		// Code entry constructors.
		CodeEntry();
		CodeEntry(ofVec2f position, ofVec2f size, ofTrueTypeFont* font);
		CodeEntry(float x, float y, float w, float h, ofTrueTypeFont* font);

		// This function handles keypresses from the user.
		void keyPressed(int key);
		// This function draws the code entry to the canvas.
		void draw();
		// This function resizes the code entry, and recalculates MaxLines and MaxCharacters.
		void resize(float width, float height);
		// This function clears the code entry of all text.
		void clear();
		// This function pads out the input to the length specifies.
		string addSpacing(string input, int length);

		// This function sets the content of the code entry from the inputLines vector.
		void setContent(vector<string> inputLines);
		// This function gets the content of the code entry, and returns it.
		vector<string> getContent();

		// This function types the char c into the code entry.
		void Type(char c);
		// This function deletes the character before the cursor.
		void Backspace();
		// This function deletes the character after the cursor.
		void Delete();
		// This function creates a new line, and add the content to the right of it to the new line.
		void Enter();

		// This function moves the cursor up one line.
		void Up();
		// This function moves the cursor down one line.
		void Down();
		// This function moves the cursor left one character.
		void Left();
		// This function moves the cursor right one character.
		void Right();

		// This function fits the code entry, so that the cursor is always on screen.
		void Fit();
};