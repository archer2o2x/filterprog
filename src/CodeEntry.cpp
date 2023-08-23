#pragma once

#include "CodeEntry.h"

CodeEntry::CodeEntry()
{

}

CodeEntry::CodeEntry(ofVec2f position, ofVec2f size, ofTrueTypeFont* font)
{
	Position = position;
	Font = font;

	resize(size.x, size.y);

	Lines = vector<string>();
	Lines.push_back("");
}

CodeEntry::CodeEntry(float x, float y, float w, float h, ofTrueTypeFont * font)
{
	Position = ofVec2f(x, y);
	Font = font;

	resize(w, h);

	Lines = vector<string>();
	Lines.push_back("");
}

void CodeEntry::keyPressed(int key)
{
	if (key == ofKey::OF_KEY_RETURN) {
		Enter();
	}
	if (key == ofKey::OF_KEY_BACKSPACE) {
		Backspace();
	}
	if (key == ofKey::OF_KEY_DEL) {
		Delete();
	}
	if (key == ofKey::OF_KEY_TAB) {
		Type(' ');
		Type(' ');
	}
	if (1 < key && key < 255) {
		if (isalnum(key) || (char)key == '.') {
			Type((char)key);
		}
	}
	if (key == ' ') {
		Type(' ');
	}

	if (key == ofKey::OF_KEY_UP) {
		Up();
	}
	if (key == ofKey::OF_KEY_DOWN) {
		Down();
	}
	if (key == ofKey::OF_KEY_LEFT) {
		Left();
	}
	if (key == ofKey::OF_KEY_RIGHT) {
		Right();
	}
}

void CodeEntry::draw()
{
	ofSetColor(Secondary);

	ofDrawRectangle(Position, Size.x, Size.y);



	ofSetColor(Primary);

	for (int i = OffsetY; i < min(OffsetY + MaxLines, (int)Lines.size()); i++) {

		Font->drawString(addSpacing(to_string(i + 1), 4) + Lines[i], Position.x + 10, Position.y + Font->getLineHeight() * (i - OffsetY + 1));

	}

	if (ofGetFrameNum() % 60 < 40) {

		float x = Position.x + Font->stringWidth(addSpacing(to_string(CursorY + 1), 4) + Lines[CursorY].substr(0, CursorX)) + 10;

		float y1 = Position.y + Font->getLineHeight() * (CursorY - OffsetY + 1) - Font->getDescenderHeight();
		float y2 = Position.y + Font->getLineHeight() * (CursorY - OffsetY + 1) - Font->getAscenderHeight();

		ofDrawLine(x, y1, x, y2);
	}
}

void CodeEntry::resize(float width, float height)
{
	Size = ofVec2f(width, height);

	MaxLines = floor(height / Font->getLineHeight());
	MaxCharaters = floor(width / Font->stringWidth(" "));

	cout << MaxLines << ", " << height << ", " << Font->getLineHeight() << endl;

	Fit();
}

void CodeEntry::clear()
{
	Lines = vector<string>();
	Lines.push_back("");

	CursorX = 0;
	CursorY = 0;

	OffsetY = 0;

	Fit();
}

string CodeEntry::addSpacing(string input, int length)
{
	int spacing = length - input.size();

	while (spacing > 0) {
		input.append(" ");
		spacing--;
	}

	return input;
}

void CodeEntry::setContent(vector<string> inputLines)
{
	Lines = inputLines;

	CursorY = Lines.size() - 1;
	CursorX = Lines[CursorY].size();

	Fit();
}

vector<string> CodeEntry::getContent()
{
	return Lines;
}

void CodeEntry::Type(char c)
{
	Lines[CursorY].insert(CursorX, 1, c);
	CursorX++;
	Fit();
}

void CodeEntry::Backspace()
{
	if (CursorX > 0) {
		Lines[CursorY].erase(CursorX - 1, 1);
		CursorX--;
	}
	else {
		if (CursorY > 0) {
			CursorX = Lines[CursorY - 1].size();
			Lines[CursorY - 1] = Lines[CursorY - 1] + Lines[CursorY];
			Lines.erase(Lines.begin() + CursorY);
			CursorY--;
		}
	}
	Fit();
}

void CodeEntry::Delete()
{
	if (CursorX < Lines[CursorY].size()) {
		Lines[CursorY].erase(CursorX, 1);
	}
	else {
		if (CursorY < Lines.size() - 1) {
			//CursorX = Lines[CursorY - 1].size();
			Lines[CursorY] = Lines[CursorY] + Lines[CursorY + 1];
			Lines.erase(Lines.begin() + CursorY + 1);
		}
	}
	Fit();
}

void CodeEntry::Enter()
{
	string carry = "";

	if (CursorX < Lines[CursorY].size() - 1) {
		carry = Lines[CursorY].substr(CursorX);
		Lines[CursorY].erase(CursorX);
	}

	CursorY++;
	CursorX = 0;

	if (CursorY >= Lines.size()) {
		Lines.push_back(carry);
	}
	else {
		Lines.insert(Lines.begin() + CursorY, carry);
	}
	Fit();
}


void CodeEntry::Up()
{
	if (CursorY > 0) {
		CursorY--;
		CursorX = min(CursorX, (int) Lines[CursorY].size());

		
	}
	Fit();
}

void CodeEntry::Down()
{
	if (CursorY < Lines.size() - 1) {
		CursorY++;
		CursorX = min(CursorX, (int)Lines[CursorY].size());
	}
	Fit();
}

void CodeEntry::Left()
{
	if (CursorX > 0) {
		CursorX--;
	}
	Fit();
}

void CodeEntry::Right()
{
	if (CursorX < Lines[CursorY].size()) {
		CursorX++;
	}
	Fit();
}

void CodeEntry::Fit()
{
	//StartY = 0;
	//EndY = Lines.size();

	if (CursorY <= OffsetY) {
		OffsetY = CursorY;
	}
	if (CursorY >= MaxLines + OffsetY) {
		OffsetY = CursorY - MaxLines + 1;
	}
}
