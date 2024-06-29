#include "math_notation.hpp"

void leftParaPressEvent(const Button& button) {
	std::string expr = App::getApp()->getTextInput();

	if (!expr.empty() && expr.back() == '.') return;
	else if (!expr.empty() && (isNumber(expr.back()) || expr.back() == 'x' || expr.back() == ')')) {
		expr += '*';
	}
	App::getApp()->setTextInput(expr + '(');
}

void rightParaPressEvent(const Button& button) {
	std::string expr = App::getApp()->getTextInput();
	int leftParas = 0;
	int rightParas = 1;

	if (!expr.empty()) {
		for (size_t i = 0; i < expr.length(); i++) {
			if (expr.at(i) == '(') {
				leftParas++;
			}
			else if (expr.at(i) == ')') {
				rightParas++;
			}
		}

		if (expr.length() > 1 && expr.back() == '.' && expr.at(expr.length() - 2) == '(') {	// "(.)"
			return;
		}

		if (expr.back() != '(' && leftParas >= rightParas) { // "()"
			App::getApp()->setTextInput(expr + ')');
		}
	}
}

void xPressEvent(const Button& button) {
	std::string expr = App::getApp()->getTextInput();

	if (!expr.empty() && expr.back() == '.') return;	// if to the left of the . there is a number, we could insert a * on the right . (123.*x)
	else if (!expr.empty() && (isNumber(expr.back()) || expr.back() == ')' || expr.back() == 'x')) {
		expr += '*';
	}

	App::getApp()->setTextInput(expr + 'x');
}

//0+000000
void zeroPressEvent(const Button& button) {
	std::string expr = App::getApp()->getTextInput();
	unsigned num = 0;
	size_t i = expr.length();

	// ? missing x*0

	if (!expr.empty()) {				//get num, the number that is furthest right in expr
		while (i > 0) {
			i--;
			if (isNumber(expr.at(i))) {
				num *= 10;
				num += unsigned(expr.at(i) - '0');
			}
			else break;
		}
	}

	// i: is at a pos of encountering the first non-number

	if (expr.empty()					// allow "0"
		|| num != 0						// dont allow "00"
		|| expr.back() == '.'			// allow ".0"
		|| expr.at(i) == '.'			// allow "123.10"
		|| isOperator(expr.at(i))		// allow "1+1230"
		|| expr.at(i) == '(') {			// allow "123+(0)"
		App::getApp()->setTextInput(expr + '0');
	}
}

void numberPressEvent(const Button& button) {
	std::string expr = App::getApp()->getTextInput();
	size_t i = expr.length();
	unsigned num = 0;

	if (!expr.empty() && expr.back() == 'x') {
		expr += '*';
	}
	else if (!expr.empty() && expr.back() == '0') {			// get number on right, if it's '0' (without a decimal), then replace the zero
		while (i > 0) {
			i--;
			if (isNumber(expr.at(i))) {						// i is at a pos of encountering the first non-number
				num *= 10;
				num += unsigned(expr.at(i) - '0');
			}
			else break;
		}
	}
	else if (!expr.empty() && num == 0) {
		expr.erase(i, 1);
	}

	App::getApp()->setTextInput(expr + button.getText());
}

// doesn't allow "(5).5" which could be converted to "(5)*.5"
void decimalPressEvent(const Button& button) {
	std::string expr = App::getApp()->getTextInput();

	if (!expr.empty() && ((expr.back() == '.' || expr.back() == ')') || expr.back() == 'x')) {
		return;
	}

	//check if number furthest right already has a decimal
	if (!expr.empty()) {
		size_t i = expr.length();
		while (i > 0) {
			i--;
			if (expr.at(i) == '.') return;
			else if (!isNumber(expr.at(i))) break;	// if it hits a non-number, its the end of the number
		}
	}

	App::getApp()->setTextInput(expr + '.');
}

void operatorPressEvent(const Button& button) {
	std::string expr = App::getApp()->getTextInput();

	if (expr.empty()													// "+" without a number on the left is illegal. (but "-" is legal notation so far)
		|| (expr.back() == '.' && expr.length() == 1)					// ".+" decimal then operator without a number on the left is illegal
		|| (expr.back() == '(' && button.getText().front() != '-')) {	// "-(+" is illegal (but "-(-" is legal so far)
		return;
	}
	else if (!expr.empty() && isOperator(expr.back())) {				//overwrite last operator
		expr.erase(expr.length() - 1, 1);
	}

	App::getApp()->setTextInput(expr + button.getText());
}

void equalPressEvent(const Button& button) {
	std::string expr = App::getApp()->getTextInput();

	if (expr.find('x') != std::string::npos) {	// if equation has a x variable, graph it
		App::getApp()->getGrid()->drawFunction(App::getApp()->renderer, expr);
	}
	else {										// if no x then just evaluate expression
		App::getApp()->setTextInput( removeTrailingDigits( std::to_string( evaluatePostfix( infixToPostfix(	App::getApp()->getTextInput())))));
	}
}

void CEPressEvent(const Button& button) {
	App::getApp()->setTextInput("");
}

void clearPressEvent(const Button& button) {
	App::getApp()->setTextInput("");
}

void backPressEvent(const Button& button) {
	std::string expr = App::getApp()->getTextInput();

	if (!expr.empty()) {
		expr = expr.erase(expr.length() - 1);
		App::getApp()->setTextInput(expr);
	}
}

//solution is to use another operator for negate: '~'
//error: 123.2 then - get number in from of . and insert -
//error: expr = '0.000' input = '~' output = 0-.000
void negatePressEvent(const Button& button) {
	std::string expr = App::getApp()->getTextInput();
	unsigned num = 0;

	if (!expr.empty()) {
		size_t i = expr.length();
		while (i > 0) {
			i--;
			if (isOperator(expr.at(i))) break;		//find closest operator
		}

		if ((i > 1 && expr.at(i) == '-') &&
			((isOperator(expr.at(i - 1)) && expr.at(i - 1) != '-') || (expr.at(i-1) == '('))) {	//last operator is negative, 2nd last isnt negative
			expr.erase(i, 1);
		}
		else if (i > 0 && expr.at(i) == '-') {		//last operator is negative
			expr.at(i) = '+';
		}
		else if (i > 0 && expr.at(i) == '+') {		//last operator is postive
			expr.at(i) = '-';
		}
		else if (i == 0 && expr.at(i) == '-') {		//first operator is negative
			expr.erase(0, 1);
		}
		else if (!expr.empty() && expr.back() == '.') {
			i = expr.length() - 1;
			while (i > 0) {
				i--;
				if(isOperator(expr.at(i))) break;
				num *= 10;
				num += unsigned(expr.at(i) - '0');
			}
			expr.insert(i, 1, '-');
		}
		else expr.insert(i + 1, 1, '-');

		App::getApp()->setTextInput(expr);
	}
}