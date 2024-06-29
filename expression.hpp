#ifndef EXPRESSION_H
#define EXPRESSION_H

#include <iostream>
#include <string>
#include <stack>
#include <math.h>

int parity(const float & num);

unsigned int preced(const char & ch);

bool isOperator(const char & ch);

bool isNumber(const char& ch);

std::string infixToPostfix(const std::string expr);

float evaluatePostfix(const std::string expr);

std::string removeTrailingDigits(std::string fnum, const char & ch = '0');

std::string substitute(std::string expr, const char & var, const float & val);

#endif