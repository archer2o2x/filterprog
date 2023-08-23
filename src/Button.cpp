#pragma once 

#include "Button.h"



Button::Button() {
	Position = ofVec2f(0, 0);
	Size = ofVec2f(120, 50);
	Content = "";
}

Button::Button(ofVec2f position, ofVec2f size, string content)
{
	Position = position;
	Size = size;
	Content = content;
}

Button::Button(float x, float y, float w, float h, string content)
{
	Position = ofVec2f(x, y);
	Size = ofVec2f(w, h);
	Content = content;
}

void Button::SetStyle(ofColor primary, ofColor secondary, ofTrueTypeFont* font)
{
	Primary = primary;
	Secondary = secondary;
	Font = font;

	RecalcOffset();
}

void Button::SetText(string content)
{
	Content = content;

	RecalcOffset();
}

void Button::RecalcOffset()
{
	float x = (Size.x - Font->stringWidth(Content)) / 2;
	float y = (Size.y + Font->stringHeight(Content)) / 2;

	textOffset = ofVec2f(x, y);
}

void Button::Draw()
{
	ofSetColor(Secondary);

	ofFill();
	ofDrawRectangle(Position, Size.x, Size.y);

	ofSetColor(Primary);

	ofNoFill();
	ofSetLineWidth(2);

	ofDrawRectangle(Position, Size.x, Size.y);

	ofFill();

	Font->drawString(Content, Position.x + textOffset.x, Position.y + textOffset.y);
}

bool Button::CheckIntersection(float x, float y)
{
	float minx = Position.x;
	float miny = Position.y;
	float maxx = minx + Size.x;
	float maxy = miny + Size.y;
	return minx < x && x < maxx && miny < y && y < maxy;
}

void Button::Resize(float width, float height)
{
	Size = ofVec2f(width, height);

	RecalcOffset();
}

void Button::Move(float x, float y)
{
	Position = ofVec2f(x, y);
}
