#include "ofApp.h"

ofApp::~ofApp()
{
	ofSetWindowTitle("Shutting Down...");

	threadedFilter.waitForThread();

	ofBackground(ofColor::black);
	ofApp::draw();
}

//--------------------------------------------------------------
void ofApp::setup(){

	ofSetWindowTitle("Filter Programming Tool");

	programFont.load("monospace", 24);

	

	programButton = Button(5, 5, ofGetWidth() / 2 - 10, 40, "EDITOR");
	programButton.SetStyle(primaryColor, secondaryColour, &programFont);

	filterButton = Button(ofGetWidth() / 2 + 5, 5, ofGetWidth() / 2 - 10, 40, "FILTER");
	filterButton.SetStyle(primaryColor, secondaryColour, &programFont);

	// PROGRAMMING WINDOW
	ProgramNewButton = Button(5, 55, 90, 40, "NEW");
	ProgramNewButton.SetStyle(primaryColor, secondaryColour, &programFont);

	ProgramOpenButton = Button(105, 55, 90, 40, "OPEN");
	ProgramOpenButton.SetStyle(primaryColor, secondaryColour, &programFont);

	ProgramSaveButton = Button(205, 55, 90, 40, "SAVE");
	ProgramSaveButton.SetStyle(primaryColor, secondaryColour, &programFont);

	ProgramHelpButton = Button(305, 55, 90, 40, "HELP");
	ProgramHelpButton.SetStyle(primaryColor, secondaryColour, &programFont);

	programEntry = CodeEntry(0, 100, ofGetWidth(), ofGetHeight() - 100, &programFont);

	// FILTER WINDOW
	FilterLoadButton = Button(5, 55, 90, 40, "LOAD");
	FilterLoadButton.SetStyle(primaryColor, secondaryColour, &programFont);

	FilterUseButton = Button(105, 55, 90, 40, "RUN");
	FilterUseButton.SetStyle(primaryColor, secondaryColour, &programFont);

	FilterSaveButton = Button(205, 55, 90, 40, "SAVE");
	FilterSaveButton.SetStyle(primaryColor, secondaryColour, &programFont);

	FilterSwapButton = Button(305, 55, 90, 40, "SWAP");
	FilterSwapButton.SetStyle(primaryColor, secondaryColour, &programFont);

	FilterProgressButton = Button(405, 55, 200, 40, "IDLE");
	FilterProgressButton.SetStyle(secondaryColour, primaryColor, &programFont);
}

//--------------------------------------------------------------
void ofApp::update(){

	if (currentlyRunningFilter) {

		string content = "";

		int frame = ceil((ofGetFrameNum() % 16) / 8);

		switch (frame) {
			case 0: 
				content = "RUNNING X";
				break;
			case 1: 
				content = "RUNNING O";
				break;
		}

		FilterProgressButton.SetText(content);

	}

	if (!threadedFilter.isThreadRunning() && currentlyRunningFilter) {

		cout << "Finished running" << endl;

		FilterProgressButton.SetText("IDLE");

		outputImage = threadedFilter.getResult();

		outputImage.update();

		currentlyRunningFilter = false;

		threadedFilter.stopThread();
	}

}

//--------------------------------------------------------------
void ofApp::draw(){
	ofBackground(18, 18, 18);

	// Drawn irrespective of current window
	filterButton.Draw();
	programButton.Draw();

	if (isProgramming) {

		ProgramNewButton.Draw();
		ProgramOpenButton.Draw();
		ProgramSaveButton.Draw();
		ProgramHelpButton.Draw();


		programEntry.draw();
	}
	else {

		FilterLoadButton.Draw();
		FilterUseButton.Draw();
		FilterSaveButton.Draw();
		FilterSwapButton.Draw();
		FilterProgressButton.Draw();

		ofSetColor(ofColor::white);

		if (inputImage.isAllocated()) {
			float width = (ofGetWidth() / 2) - 10;

			inputImage.draw(5, 105, width, (width / inputImage.getWidth()) * inputImage.getHeight());
		}

		if (outputImage.isAllocated()) {
			float width = (ofGetWidth() / 2) - 10;

			outputImage.draw(width + 15, 105, width, (width / outputImage.getWidth()) * outputImage.getHeight());
		}

	}

	//img.draw(ofGetWidth() / 2, 100, (ofGetHeight() - 100) * (img.getHeight() / img.getWidth()), ofGetHeight() - 100);
	//img.draw(375, 5, 90, 90);

	

	//newButton.Draw();
	//openButton.Draw();
	
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	if (isProgramming) {
		programEntry.keyPressed(key);
	}
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
	if (programButton.CheckIntersection(x, y)) {
		NavigateProgram();
	}
	if (filterButton.CheckIntersection(x, y)) {
		NavigateFilter();
	}

	if (isProgramming) {

		if (ProgramNewButton.CheckIntersection(x, y)) {
			programEntry.clear();
		}

		if (ProgramOpenButton.CheckIntersection(x, y)) {
			ofFileDialogResult result = ofSystemLoadDialog("Load Program", false, ofFilePath::getUserHomeDir() + "/Documents/");

			if (result.bSuccess) {

				ifstream file;
				string line;
				vector<string> lines;

				file.open(result.getPath());

				if (file.is_open()) {

					while (getline(file, line)) {
						lines.push_back(line);
					}

					file.close();

					programEntry.setContent(lines);

					ofSetWindowTitle("Filter Programming Tool - " + result.getName());

				}
			}
		}

		if (ProgramSaveButton.CheckIntersection(x, y)) {
			ofFileDialogResult result = ofSystemSaveDialog("program.fltr", "Save new filter as");

			if (result.bSuccess) {

				ofstream file;
				string line;
				vector<string> lines;

				file.open(result.getPath());

				if (file.is_open()) {

					lines = programEntry.getContent();

					for (int i = 0; i < lines.size(); i++) {

						file << lines[i] << endl;

					}

					file.close();

					ofSetWindowTitle("Filter Programming Tool - " + result.getName());
				}
			}
		}

		if (ProgramHelpButton.CheckIntersection(x, y)) {

			string path = ofToDataPath("", true);

			replace(path.begin(), path.end(), '\\', '/');

			//path.replace(0, 1, "C");

			cout << path << endl;

			ofSystem("start " + path + "/help.html");

		}

	}
	else {

		if (FilterLoadButton.CheckIntersection(x, y)) {
			ofFileDialogResult result = ofSystemLoadDialog("Load Image", false, ofFilePath::getUserHomeDir() + "/Pictures/");

			if (result.bSuccess) {

				inputImage.load(result.getPath());

			}
		}

		if (FilterUseButton.CheckIntersection(x, y)) {

			vector<string> lines = programEntry.getContent();
			string content;

			for (string l : lines) {
				cout << l << "<->" << endl;
				content += l + ' ';
			}

			threadedFilter.setup(content, inputImage);

			threadedFilter.startThread(false);

			currentlyRunningFilter = true;

			

		}

		if (FilterSaveButton.CheckIntersection(x, y)) {
			ofFileDialogResult result = ofSystemSaveDialog("result.png", "Save new filter as");

			if (result.bSuccess) {

				outputImage.save(result.getPath());

			}
		}

		if (FilterSwapButton.CheckIntersection(x, y)) {
			inputImage = outputImage;
		}

	}
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){
	programEntry.resize(w, h - 100);

	programButton.Resize(w / 2 - 10, 40);
	filterButton.Resize(w / 2 - 10, 40);

	filterButton.Move(w / 2 + 5, 5);
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

void ofApp::NavigateProgram()
{
	if (!isProgramming) {
		isProgramming = true;
	}
}

void ofApp::NavigateFilter()
{
	if (isProgramming) {
		isProgramming = false;
	}
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
