#pragma once

#include "ofMain.h"

// A handy class for making clickable buttons
class Button {
	private:

		// Where the top-right corner of the button is.
		ofVec2f Position;
		// How big the button is.
		ofVec2f Size;
		// What the button should display as a label.
		string Content;

		// The primary colour of the button, eg the text and outline colour.
		ofColor Primary;
		// The secondary colour of the button, eg the background of the button.
		ofColor Secondary;
		// The font to use when calculating text offsets and rendering text.
		ofTrueTypeFont* Font;

		// How far from the top-right of the button the top-right of the text should be.
		ofVec2f textOffset;

		// This function recalculates the offset of the text from the corner, 
		// taking into account the label and font used.
		void RecalcOffset();

	public:
		// Button Constructors
		Button();
		Button(ofVec2f position, ofVec2f size, string content);
		Button(float x, float y, float w, float h, string content);

		// Sets the primary and secondary colour as well as the font, and calculates the text offset.
		void SetStyle(ofColor primary, ofColor secondary, ofTrueTypeFont* font);
		// Sets the label of the button, and calculates the text offset.
		void SetText(string content);

		// Draws the button on the canvas.
		void Draw();
		// Checks if the point (x, y) is inside the bounds of the button.
		bool CheckIntersection(float x, float y);

		// Changes the size of the button, and calculate the text offset.
		void Resize(float width, float height);
		// Changes the position of the button.
		void Move(float x, float y);
};