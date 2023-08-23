#pragma once

#include <string>

using namespace std;

// This class stores the string used to classify FILTERPROG commands. 
// As such, comments will dictate the result of the command it represents.

// [NAME] represents the string which NAME is currently set to.
// <NAME> represents a constant, eg "5".
// {NAME} represents a variable name, eg "x"
// No brackets represent another command.

class FilterConstants
{
public:

	// Gets the red amount of the pixel at position (x, y)
	// FORMAT: [PIXEL_RED] x y
	const static string PIXEL_RED;

	// Gets the green amount of the pixel at position(x, y)
	// FORMAT: [PIXEL_GREEN] x y
	const static string PIXEL_GREEN;

	// Gets the blue amount of the pixel at position (x, y)
	// FORMAT: [PIXEL_BLUE] x y
	const static string PIXEL_BLUE;



	// Gets the hue amount of the pixel at position (x, y)
	// FORMAT: [PIXEL_HUE] x y
	const static string PIXEL_HUE;

	// Gets the saturation amount of the pixel at position (x, y)
	// FORMAT: [PIXEL_SATURATION] x y
	const static string PIXEL_SATURATION;

	// Gets the value amount of the pixel at position (x, y)
	// FORMAT: [PIXEL_VALUE] x y
	const static string PIXEL_VALUE;



	// Returns the next instruction as a number
	// FORMAT: [VALUE] <number>
	const static string VALUE;

	// Sets the variable name to have the value a
	// FORMAT: [SET_VARIABLE] {variableName} a
	const static string SET_VARIABLE;

	// Returns the value of the variable name
	// FORMAT: [VARIABLE] {variableName}
	const static string VARIABLE;



	// Executes the command n times
	// FORMAT: [CONTROL_LOOP] number {indexVariable} command
	const static string CONTROL_LOOP;

	// Executes the command if condition is 1
	// FORMAT: [CONTROL_IF] condition command
	const static string CONTROL_IF;

	// Executes the next n instructions as children
	// FORMAT: [CONTROL_SEQUENCE] <N> command1, command2, ... , commandN
	const static string CONTROL_SEQUENCE;



	// Adds a and b together and returns the result
	// FORMAT: [MATH_ADD] a b
	const static string MATH_ADD;

	// Subtracts b from a and returns the result
	// FORMAT: [MATH_SUBTRACT] a b
	const static string MATH_SUBTRACT;

	// Multiplies a and b and returns the result
	// FORMAT: [MATH_MULTIPLY] a b
	const static string MATH_MULTIPLY;

	// Divides b from a and returns the result
	// FORMAT: [MATH_DIVIDE] a b
	const static string MATH_DIVIDE;



	// Raises a to the power b and returns the result
	// FORMAT: [MATH_POWER] a b
	const static string MATH_POWER;

	// Returns a modulo b
	// FORMAT: [MATH_MODULUS] a b
	const static string MATH_MODULUS;

	// Returns the square root of a
	// FORMAT: [MATH_SQUARE_ROOT] a
	const static string MATH_SQUARE_ROOT;

	// Returns the log of b with base a
	// FORMAT: [MATH_LOG] a b
	const static string MATH_LOG;



	// Returns val clamped between min and max
	// FORMAT: [MATH_CLAMP] val min max
	const static string MATH_CLAMP;

	// Returns a value lerped between a and b, controlled by t in the range 0 - 1
	// FORMAT: [MATH_LERP] a b t
	const static string MATH_LERP;



	// Returns the sin of a
	// FORMAT: [MATH_SIN] a
	const static string MATH_SIN;

	// Returns the cos of a
	// FORMAT: [MATH_COS] a
	const static string MATH_COS;

	// Returns the tan of a
	// FORMAT: [MATH_TAN] a
	const static string MATH_TAN;



	// Returns the arcsin of a
	// FORMAT: [MATH_ARC_SIN] a
	const static string MATH_ARC_SIN;

	// Returns the arccos of a
	// FORMAT: [MATH_ARC_COS] a
	const static string MATH_ARC_COS;

	// Returns the arctan of a
	// FORMAT: [MATH_ARC_TAN] a
	const static string MATH_ARC_TAN;



	// Returns a random number between a and b
	// FORMAT: [MATH_RANDOM] a b
	const static string MATH_RANDOM;

	// Returns the noise value at the point (x, y, z)
	// FORMAT: [MATH_NOISE] x y z
	const static string MATH_NOISE;



	// Returns eulers constant
	// FORMAT: [CONST_EULER]
	const static string CONST_EULER;

	// Returns pi
	// FORMAT: [CONST_PI]
	const static string CONST_PI;

	// Returns 1
	// FORMAT: [CONST_ONE]
	const static string CONST_ONE;

	// RETURNS 0.5
	// FORMAT: [CONST_HALF]
	const static string CONST_HALF;

	// RETURNS 0
	// FORMAT: [CONST_ZERO]
	const static string CONST_ZERO;



	// Rounds a down to the nearest integer value
	// FORMAT: [CONVERSION_FLOOR] a
	const static string CONVERSION_FLOOR;

	// Rounds a up to the nearest integer value
	// FORMAT: [CONVERSION_CEILING] a
	const static string CONVERSION_CEILING;

	// Rounds a to the nearest integer value
	// FORMAT: [CONVERSION_ROUND] a
	const static string CONVERSION_ROUND;



	// If a is 0, returns 1, and if a is 1 returns 0
	// FORMAT: [LOGIC_NOT] a
	const static string LOGIC_NOT;

	// If a and b is 1, returns 1 else it returns 0
	// FORMAT: [LOGIC_AND] a b
	const static string LOGIC_AND;

	// If a or b is 1, returns 1 else it returns 0
	// FORMAT: [LOGIC_OR] a b
	const static string LOGIC_OR;

	// If either a or b is 1 but not both, returns 1 else it returns 0
	// FORMAT: [LOGIC_XOR] a b
	const static string LOGIC_XOR;

	// If a and b are equal, returns 1 else it returns 0
	// FORMAT: [LOGIC_EQUALS] a b
	const static string LOGIC_EQUALS;

	// If a is less than b, returns 1 else it returns 0
	// FORMAT: [LOGIC_LESS_THAN] a b
	const static string LOGIC_LESS_THAN;

	// If a is greater than b, returns 1 else it returns 0
	// FORMAT: [LOGIC_GREATER_THAN] a b
	const static string LOGIC_GREATER_THAN;



	// Gets the width of the image in pixels
	// FORMAT: [IMAGE_WIDTH]
	const static string IMAGE_WIDTH;

	// Gets the height of the image in pixels
	// FORMAT: [IMAGE_HEIGHT]
	const static string IMAGE_HEIGHT;



	// Sets the colour of the current pixel using RGB colour scheme
	// FORMAT: [RESULT_PIXEL_RGB] x y red green blue
	const static string RESULT_PIXEL_RGB;

	// Sets the colour of the current pixel using HSV / HSB colour scheme
	// FORMAT: [RESULT_PIXEL_HSV] x y hue saturation value
	const static string RESULT_PIXEL_HSV;

	// Serves as a debug tool. Has no use except to a developer
	// Prints the value to the output, and returns the value
	// FORMAT: [DEBUG] a
	const static string DEBUG;
};

