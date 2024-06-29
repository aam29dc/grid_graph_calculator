#include "expression.hpp"

int parity(const float & num) {
	if (num < 0) return -1;
	else if (num > 0) return 1;
	else return 0;
}

std::string removeTrailingDigits(std::string fnum, const char & ch) {
	//fnum is a float, 1.123001000 has 3 trailing 0's
	unsigned int chars = 0;
	size_t pos = 0;
	bool first = true;

	for (size_t i = 0; i < fnum.length(); i++) {
		if (fnum.at(i) == ch) {
			if (first == true) {
				pos = i;
			}
			chars++;
			first = false;
		}
		else {
			chars = 0;
			first = true;
		}
	}

	fnum.erase(pos, pos + chars);
	if (fnum.back() == '.') fnum.erase(fnum.length() - 1);

	return fnum;
}

std::string substitute(std::string expr, const char & var, const float & val) {
	std::string val_str = removeTrailingDigits(std::to_string(val), '0');

	//remove the . from 123. when no number is after.
	if (!val_str.empty() && val_str.back() == '.') val_str.erase(val_str.length() - 1);

	for (size_t i = 0; i < expr.length(); i++) {
		if (expr.at(i) == var) {
			expr.erase(i, 1);
			expr.insert(i, val_str);
		}
	}
	return expr;
}

unsigned int preced(const char & ch) {
	switch (ch) {
	case '^':
		return 3;
	case '*':case '/':
		return 2;
	case '-':case '+':
		return 1;
	default:
		break;
	}
	return 0;
}

bool isNumber(const char& ch) {
	return (ch >= '0' && ch <= '9');
}

bool isOperator(const char & ch) {
	switch (ch) {
	case '-':case '+':case '*':case '/':case '^':case '%':
		return true;
	default:
		break;
	}
	return false;
}

std::string infixToPostfix(const std::string expr) {
	std::stack<char> ops;
	std::string postfix;

	for (size_t i = 0; i < expr.length(); i++) {
		//if scan number then add to expr
		if (isNumber(expr.at(i))) {
			while ((i < expr.length()) && (isNumber(expr.at(i)) || expr.at(i) == '.')) {
				postfix += expr.at(i);
				i++;
			}
			i--;			//after leaving this if block, we'll be at a non-number,
							//then the for block will increment i again, so we decrement.
			postfix += ' ';	//add a space after each number
		}
		//if scan operator & stack is empty, then push to stack
		//if scan operator, and scanned operator is higher precedence than top of stack
		else if ( (isOperator(expr.at(i)) && ops.empty()) || (!ops.empty() && isOperator(expr.at(i)) && (preced(expr.at(i)) > preced(ops.top()))) ) {
			// then push scanned operator on top of stack
			ops.push(expr.at(i));
		}
		//if scan operator, and scanned operator is lower or equal precedence than top of stack
		else if (!ops.empty() && isOperator(expr.at(i)) && (preced(expr.at(i)) < preced(ops.top()))) {
			// then pop operator to expr, and push scanned operator to top of stack
			postfix += ops.top();
			ops.pop();
			ops.push(expr.at(i));
		}
		//if scan is left parenthesis, push to stack
		else if (expr.at(i) == '(') {
			ops.push(expr.at(i));
		}
		//if scan is right parenthesis, pop and append to postfix until left parenthesis
		else if (expr.at(i) == ')') {
			while (ops.top() != '(') {
				postfix += ops.top();
				ops.pop();
			}
			ops.pop();	// pop off the final (
		}
		//if scan is a space go to next char
		//if scan is anything else: invalid input
	}

	while (!ops.empty()) {
		postfix += ops.top();
		ops.pop();
	}

	return postfix;
}

float evaluatePostfix(const std::string expr) {
	std::stack<float> nums;
	float num = 0.0f;
	float dec = 0.0f;
	size_t decPos = 0;

	float left = 0.0f, right = 0.0f;

	for (size_t i = 0; i < expr.length(); i++) {
		//if number: push to stack
		if (isNumber(expr.at(i)) || expr.at(i) == '.') {
			while ((i < expr.length()) && isNumber(expr.at(i))) {
				num *= 10.0f;
				num += (expr.at(i) - '0');
				i++;
			}
			if (expr.at(i) == '.') { //convert numbers after '.' to fractions then add
				decPos = i;
				i++;
				while ((i < expr.length()) && isNumber(expr.at(i))) {
					dec = float(expr.at(i) - '0');
					for (size_t j = decPos; j < i; j++) {
						dec /= 10.0f;
					}
					num += dec;
					i++;
				}
			}

			nums.push(num);
			num = 0;
		}
		//if operator: pop two off stack, evaluate, then push back on stack
		else if (isOperator(expr.at(i))) {
			right = nums.top();
			nums.pop();
			left = nums.top();
			nums.pop();

			
			switch (expr.at(i)) {
			case '+':
				nums.push(left + right);
				break;
			case '-':
				nums.push(left - right);
				break;
			case '*':
				nums.push(left * right);
				break;
			case '/':
				nums.push(left / right);
				break;
			case '^':
				nums.push(powf(left, right));
				break;
			default:
				break;
			}
		}
	}
	//at end, the stack should contain one number: the result
	return nums.top();
}