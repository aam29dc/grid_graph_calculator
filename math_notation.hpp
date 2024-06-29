#ifndef MATH_NOTATION
#define MATH_NOTATION

#include "app.hpp"

/* 
	These functions prevent invalid input as user clicks buttons.
		Assumes that last expr is correct,
			checks if a button press will still lead to an correct expression,
				if not do nothing
				or correct input [ expr = "2" then users hits '(', app will correct it to '2*(' ]

	Equations should be explicit, no missing '*', this happens with paras and the 'x' variable.
		We correct this before the user hits '=',
*/

void leftParaPressEvent(const Button& button);
void rightParaPressEvent(const Button& button);
void xPressEvent(const Button& button);
void zeroPressEvent(const Button& button);
void decimalPressEvent(const Button& button);
void operatorPressEvent(const Button& button);
void equalPressEvent(const Button& button);
void numberPressEvent(const Button& button);
void equalPressEvent(const Button& button);
void CEPressEvent(const Button& button);
void clearPressEvent(const Button& button);
void backPressEvent(const Button& button);
void negatePressEvent(const Button& button);

#endif