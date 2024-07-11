#ifndef EXPRESSION_H
#define EXPRESSION_H

#include <iostream>
#include <string>
#include <stack>
#include <math.h>

bool isValidEquation(const std::string& expr);

int parity(const float& num);

int preced(const char& ch);

bool isOperator(const char& ch);

bool isNumber(const char& ch);

std::string infixToPostfix(const std::string& expr);

float evaluatePostfix(const std::string& expr, const float& val = 0.0f);

std::string removeTrailingDigits(std::string fnum, const char & ch = '0');

std::string substitute(std::string expr, const char & var, const float & val);

std::string convertUnaryToBinary(const std::string& expr);

#endif