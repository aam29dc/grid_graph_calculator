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

void leftParaPressEvent(const char& ch);
void rightParaPressEvent(const char& ch);
void xPressEvent(const char& ch);
void zeroPressEvent(const char& ch);
void decimalPressEvent(const char& ch);
void operatorPressEvent(const char& ch); 	// instead of access to the whole button, we just need the char it stores,
void equalPressEvent(const char& ch);		// if we dont pass a parameter, then we need a function for every number
void numberPressEvent(const char& ch);
void equalPressEvent(const char& ch);
void CEPressEvent(const char& ch);
void clearPressEvent(const char& ch);
void backPressEvent(const char& ch);
void negatePressEvent(const char& ch);

#endif