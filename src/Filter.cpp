#include "Filter.h"

string Filter::GetNext()
{
	if (programIndex < instructions.size()) {
		string command = instructions[programIndex];
		programIndex++;
		return command;
	}
	else {
		return "ZERO";
	}
	
}

ofFloatColor Filter::GetColorAtPosition()
{
	float x = Execute();
	float y = Execute();

	return ofFloatColor(getImgColor(getImgIndex(floor(x), floor(y))));
}

int Filter::getImgWidth()
{
	return pixelData->getWidth();
}

int Filter::getImgHeight()
{
	return pixelData->getHeight();
}

ofColor Filter::getImgColor(size_t index)
{
	return pixelData->getColor(index);
}

size_t Filter::getImgIndex(int x, int y)
{
	return pixelData->getPixelIndex(x, y);
}

void Filter::debugVariables()
{
	cout << "VARIABLES" << endl;
	for (auto iterator = variables.begin(); iterator != variables.end(); ++iterator) {
		cout << iterator->first << " = " << iterator->second << endl;
	}
	cout << endl;
}

Filter::Filter()
{
}

Filter::Filter(string program)
{
	Compile(program);
}

void Filter::UseFilter(ofPixels* image)
{
	pixelData = image;

	isRunning = true;

	//cout << getImgWidth() << ", " << getImgHeight() << endl;

	programIndex = 0;

	while (instructions.size() > programIndex) {
		Execute();
	}
}

float Filter::Execute()
{
	if (!isRunning) return 0;

	try {

		//debugVariables();

		string command = GetNext();

		if (command == FilterConstants::PIXEL_RED) { return GetColorAtPosition().r; }
		if (command == FilterConstants::PIXEL_GREEN) { return GetColorAtPosition().g; }
		if (command == FilterConstants::PIXEL_BLUE) { return GetColorAtPosition().b; }



		if (command == FilterConstants::PIXEL_HUE) { return GetColorAtPosition().getHue(); }
		if (command == FilterConstants::PIXEL_SATURATION) { return GetColorAtPosition().getSaturation(); }
		if (command == FilterConstants::PIXEL_VALUE) { return GetColorAtPosition().getBrightness(); }



		if (command == FilterConstants::CONTROL_LOOP) {
			int n = (int)Execute();

			string varname = GetNext();

			int pindex = programIndex;

			for (int i = 0; i < n; i++) {
				programIndex = pindex;
				variables.insert_or_assign(varname, i);
				Execute();
			}
		}
		if (command == FilterConstants::CONTROL_IF) {
			float b = Execute();

			if (b == 1) {
				Execute();
				return 1;
			}
		}
		if (command == FilterConstants::CONTROL_SEQUENCE) {
			int n = stoi(GetNext());

			for (int i = 0; i < n; i++) {
				Execute();
			}
		}



		if (command == FilterConstants::MATH_ADD) {
			float a = Execute();
			float b = Execute();
			return a + b;
		}
		if (command == FilterConstants::MATH_SUBTRACT) {
			float a = Execute();
			float b = Execute();
			return a - b;
		}
		if (command == FilterConstants::MATH_MULTIPLY) {
			float a = Execute();
			float b = Execute();
			return a * b;
		}
		if (command == FilterConstants::MATH_DIVIDE) {
			float a = Execute();
			float b = Execute();
			return a / b;
		}



		if (command == FilterConstants::MATH_POWER) {
			float a = Execute();
			float b = Execute();
			return pow(a, b);
		}
		if (command == FilterConstants::MATH_MODULUS) {
			int a = (int)Execute();
			int b = (int)Execute();
			return (float)(a % b);
		}
		if (command == FilterConstants::MATH_SQUARE_ROOT) {
			return sqrt(Execute());
		}
		if (command == FilterConstants::MATH_LOG) {
			float a = Execute();
			float b = Execute();
			return log(b) / log(a);
		}


		if (command == FilterConstants::MATH_CLAMP) {
			float val = Execute();
			float min = Execute();
			float max = Execute();
			return ofClamp(val, min, max);

		}
		if (command == FilterConstants::MATH_LERP) {
			float a = Execute();
			float b = Execute();
			float t = Execute();
			return ofLerp(a, b, t);

		}
		if (command == FilterConstants::MATH_SIN) {	return sin(Execute()); }
		if (command == FilterConstants::MATH_ARC_SIN) { return asin(Execute()); }
		if (command == FilterConstants::MATH_COS) { return cos(Execute()); }
		if (command == FilterConstants::MATH_ARC_COS) { return acos(Execute()); }
		if (command == FilterConstants::MATH_TAN) { return tan(Execute()); }
		if (command == FilterConstants::MATH_ARC_TAN) { return atan(Execute()); }



		if (command == FilterConstants::CONST_EULER) { return exp(1.0); }
		if (command == FilterConstants::CONST_PI) { return PI; }
		if (command == FilterConstants::CONST_ONE) { return 1.0f; }
		if (command == FilterConstants::CONST_HALF) { return 0.5f; }
		if (command == FilterConstants::CONST_ZERO) { return 0.0f; }



		if (command == FilterConstants::MATH_RANDOM) {
			float min = Execute();
			float max = Execute();
			return (ofRandomuf() * (max - min)) + min;
		}
		if (command == FilterConstants::MATH_NOISE) {
			float x = Execute();
			float y = Execute();
			float z = Execute();
			return ofNoise(x, y, z);
		}



		if (command == FilterConstants::CONVERSION_FLOOR) { return floor(Execute()); }
		if (command == FilterConstants::CONVERSION_CEILING) { return ceil(Execute()); }
		if (command == FilterConstants::CONVERSION_ROUND) { return round(Execute()); }



		if (command == FilterConstants::LOGIC_NOT) {
			if (Execute() == 1) { return 1; }
			else { return 0; }
		}
		if (command == FilterConstants::LOGIC_AND) {
			float a = Execute();
			float b = Execute();
			if (a == 1 && b == 1) { return 1; }
			else { return 0; }
		}
		if (command == FilterConstants::LOGIC_OR) {
			float a = Execute();
			float b = Execute();
			if (a == 1 || b == 1) { return 1; }
			else { return 0; }
		}
		if (command == FilterConstants::LOGIC_XOR) {
			float a = Execute();
			float b = Execute();
			if ((a == 1 || b == 1) && !(a == 1 && b == 1)) { return 1; }
			else { return 0; }
		}
		if (command == FilterConstants::LOGIC_EQUALS) {
			float a = Execute();
			float b = Execute();
			if (a == b) { return 1; }
			else { return 0; }
		}
		if (command == FilterConstants::LOGIC_LESS_THAN) {
			float a = Execute();
			float b = Execute();
			if (a < b) { return 1; }
			else { return 0; }
		}
		if (command == FilterConstants::LOGIC_GREATER_THAN) {
			float a = Execute();
			float b = Execute();
			if (a > b) { return 1; }
			else { return 0; }
		}



		if (command == FilterConstants::IMAGE_WIDTH) { return (float)getImgWidth(); }
		if (command == FilterConstants::IMAGE_HEIGHT) { return (float)getImgHeight(); }



		if (command == FilterConstants::RESULT_PIXEL_RGB) {
			float x = Execute();
			float y = Execute();
			float r = Execute();
			float g = Execute();
			float b = Execute();

			pixelData->setColor(getImgIndex(x, y), ofFloatColor(r, g, b));
		}
		if (command == FilterConstants::RESULT_PIXEL_HSV) {
			float x = Execute();
			float y = Execute();
			float h = Execute();
			float s = Execute();
			float v = Execute();

			ofColor col = ofFloatColor();
			col.setHue(h);
			col.setSaturation(s);
			col.setBrightness(v);

			pixelData->setColor(getImgIndex(x, y), col);
		}



		if (command == FilterConstants::DEBUG) {
			float val = Execute();
			cout << val << endl;
			debugVariables();
			return val;
		}



		if (command == FilterConstants::VALUE) {
			return stof(GetNext());
		}
		if (command == FilterConstants::SET_VARIABLE) {
			string name = GetNext();
			variables.insert_or_assign(name, Execute());
		}
		if (command == FilterConstants::VARIABLE) {
			return variables[GetNext()];
		}

		return 1;
	}
	catch (exception e) {
		return 0;
	}
}

void Filter::Compile(string program)
{
	string token = "";

	cout << "program - " << program << endl;
	cout << "raw input - ";

	char lastChar = program[0];

	for (char c : program) {
		if (c == ' ' && lastChar != ' ') {
			instructions.push_back(token);
			token = "";
			cout << ' ';
		} 
		else if (isalnum((char)c) || (char)c == '.') {
			token += c;
			cout << c;
		}
		lastChar = c;
	}
	cout << endl << "Compiled" << endl;
	instructions.push_back(token);
}
